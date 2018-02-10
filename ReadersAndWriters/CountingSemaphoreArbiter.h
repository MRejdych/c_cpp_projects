#pragma once

#include "Arbiter.h"
#include "CountingSemaphore.h"

/*Arbiter nie faworyzujacy zadnej z grup procesow.
Pisarz czeka, jezeli w czytelni znajduje siê czytelnik lub inny pisarz.
Pisarz po skonczonej pracy wybudza wszystkich czytelnikow, jezeli aktualnie oczekuja na dostep. W przeciwnym wypadku wpuszczany jest kolejny pisarz.

Czytelnik czeka, je¿eli w czytelni znajduje siê pisarz lub pisarz oczekuje na dostep.
Po skonczonej pracy czytelnik wpuszcza oczekujacego pisarza (pod warunkiem, ze czytelnik jest ostatnim wychodzacym z czytelni).

Naprzemienne wybudzanie siê czytelnikow i pisarzy minimalizuje ryzyko zaglodzenia.
*/

class CountingSemaphoreArbiter : public Arbiter
{
private:
	CountingSemaphore* _semaphore;
	int _readingRoomCapacity;

public:
	CountingSemaphoreArbiter(int readingRoomCapacity)
	{
		_readingRoomCapacity = readingRoomCapacity; //100
		_semaphore = new CountingSemaphore(readingRoomCapacity);
	}

	virtual void startRead()  //Protokol wstepny czytelnika
	{
		_semaphore->grantResourceForReader(); //Przyznanie dostepu
	}

	virtual void endRead() //Protokol koncowy czytelnika
	{
		_semaphore->releaseResourceTakenByReader(); // Zwolnienie zasobu
	}

	virtual void startWrite() // Protokol wstepny pisarza
	{
		_semaphore->grantResourceForWriter(); //Przyznanie dostepu wylacznego do zasobu
	}

	virtual void endWrite() //Protokol koncowy pisarza
	{
		_semaphore->releaseResourceTakenByWriter(); // Zwolnienie zasobu
	}

	~CountingSemaphoreArbiter()
	{
		delete _semaphore;
	}
};


