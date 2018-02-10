#pragma once

#include <windows.h>
#include "Arbiter.h"
// Klasa implementuj¹ca algorytm faworyzuj¹cy czytelników, dziedzicz¹ca po klasie Arbiter. Czytelnia ma nieograniczon¹ pojemnoœæ
class ReaderFirstArbiter : public Arbiter
{
private:
	HANDLE _readSemaphore; //Semafor bitowy (mutex)
	HANDLE _writeSemaphore; // Semafor bitowy (mutex)
	int _readers; // Licznik pracuj¹cych czytelników
	bool _anyWaitingReader; //Flaga informuj¹ca, czy jakikolwiek czytelnik czeka na dostêp

public:
	ReaderFirstArbiter()
	{
		_readSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
		_writeSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
		_readers = 0;
		_anyWaitingReader = false;
	}

	virtual void startRead() //Protoko³y wstêpne czytelnika
	{
		//Blokuje _readSemaphore i czeka na dostêp do _writeSemaphore je¿eli ¿aden czytelnik nie jest aktualnie w czytelni
		WaitForSingleObject(_readSemaphore, INFINITE);
		if (_readers == 0) {
			_anyWaitingReader = true;
			WaitForSingleObject(_writeSemaphore, INFINITE);
			_anyWaitingReader = false;
		}
		++_readers;
		ReleaseSemaphore(_readSemaphore, 1, NULL); //Zwalnia _readSemaphore
	}

	virtual void endRead()
	{
		WaitForSingleObject(_readSemaphore, INFINITE);
		--_readers;
		//Je¿eli po wyjœciu czytelnika czytelnia pozosta³a pusta, zwalnia _writeSemaphore
		if (_readers == 0) {
			ReleaseSemaphore(_writeSemaphore, 1, NULL);
		}
		ReleaseSemaphore(_readSemaphore, 1, NULL);
	}

	virtual void startWrite()
	{
		//Pisarz blokuje _writeSemaphore w przypadku, gdy ¿aden czytelnik nie czeka na dostêp
		do {
			WaitForSingleObject(_writeSemaphore, INFINITE);
			if (_anyWaitingReader) {
				ReleaseSemaphore(_writeSemaphore, 1, NULL);
			}
			else {
				break;
			}
		} while (true);

	}

	virtual void endWrite()
	{
		ReleaseSemaphore(_writeSemaphore, 1, NULL);
	}

	~ReaderFirstArbiter()
	{
		CloseHandle(_writeSemaphore);
		CloseHandle(_readSemaphore);
	}
};


