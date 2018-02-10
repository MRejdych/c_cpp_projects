#pragma once

#include <Windows.h>
#include "Arbiter.h"


class WriterFirstArbiter : public Arbiter
{
private:
	HANDLE _readersCounterSemaphore; //Semafor synchronizuj¹cy dostêp do licznika pracujacych czytelników
	HANDLE _writersCounterSemaphore; // Semafor synchronizuj¹cy dostêp do licznika pracuj¹cych pisarzy
	HANDLE _accessSemaphore; //Semafor synchronizuj¹cy dostêp do zasobu
	HANDLE _newReadersAllowedSemaphore; //Semafor dopuszczaj¹cy nowych czytelników do semafora _accessSemaphore
	int _readers; //Liczniki pracuj¹cych czytelników i pisarzy
	int _writers;

public:
	WriterFirstArbiter()
	{
		_readersCounterSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
		_writersCounterSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
		_accessSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
		_newReadersAllowedSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
		_readers = 0;
		_writers = 0;
	}

	//Protoko³y wstêpne czytelnika
	virtual void startRead()
	{
		WaitForSingleObject(_newReadersAllowedSemaphore, INFINITE);
		ReleaseSemaphore(_newReadersAllowedSemaphore, 1, NULL);

		WaitForSingleObject(_readersCounterSemaphore, INFINITE);
		if (_readers == 0) {
			WaitForSingleObject(_accessSemaphore, INFINITE);
		}
		++_readers;
		ReleaseSemaphore(_readersCounterSemaphore, 1, NULL);
	}

	//Protoko³y koñcowe czytelnika
	virtual void endRead()
	{
		WaitForSingleObject(_readersCounterSemaphore, INFINITE);
		--_readers;

		if (_readers == 0) {
			ReleaseSemaphore(_accessSemaphore, 1, NULL);
		}
		ReleaseSemaphore(_readersCounterSemaphore, 1, NULL);
	}

	//Protoko³o wstêpne pisarza
	virtual void startWrite()
	{
		WaitForSingleObject(_writersCounterSemaphore, INFINITE);
		if (_writers == 0) {
			WaitForSingleObject(_newReadersAllowedSemaphore, INFINITE);
		}
		++_writers;
		ReleaseSemaphore(_writersCounterSemaphore, 1, NULL);

		WaitForSingleObject(_accessSemaphore, INFINITE);
	}

	//Protoko³y koñcowe pisarza
	virtual void endWrite()
	{
		ReleaseSemaphore(_accessSemaphore, 1, NULL);

		WaitForSingleObject(_writersCounterSemaphore, INFINITE);
		--_writers;
		if (_writers == 0) {
			ReleaseSemaphore(_newReadersAllowedSemaphore, 1, NULL);
		}
		ReleaseSemaphore(_writersCounterSemaphore, 1, NULL);
	}

	~WriterFirstArbiter()
	{
		CloseHandle(_newReadersAllowedSemaphore);
		CloseHandle(_accessSemaphore);
		CloseHandle(_writersCounterSemaphore);
		CloseHandle(_readersCounterSemaphore);
	}
};




