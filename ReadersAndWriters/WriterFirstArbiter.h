#pragma once

#include <Windows.h>
#include "Arbiter.h"


class WriterFirstArbiter : public Arbiter
{
private:
	HANDLE _readersCounterSemaphore; //Semafor synchronizujący dostęp do licznika pracujacych czytelników
	HANDLE _writersCounterSemaphore; // Semafor synchronizujący dostęp do licznika pracujących pisarzy
	HANDLE _accessSemaphore; //Semafor synchronizujący dostęp do zasobu
	HANDLE _newReadersAllowedSemaphore; //Semafor dopuszczający nowych czytelników do semafora _accessSemaphore
	int _readers; //Liczniki pracujących czytelników i pisarzy
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

	//Protokoły wstępne czytelnika
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

	//Protokoły końcowe czytelnika
	virtual void endRead()
	{
		WaitForSingleObject(_readersCounterSemaphore, INFINITE);
		--_readers;

		if (_readers == 0) {
			ReleaseSemaphore(_accessSemaphore, 1, NULL);
		}
		ReleaseSemaphore(_readersCounterSemaphore, 1, NULL);
	}

	//Protokoło wstępne pisarza
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

	//Protokoły końcowe pisarza
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




