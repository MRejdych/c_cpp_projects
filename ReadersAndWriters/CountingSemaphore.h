#pragma once

#include <mutex>

class CountingSemaphore
{
private:
	volatile int _maxResources; //maksymalna pojemnosc czytelni
	volatile int _freeResources; // dostepna pojemnosc czytelni
	bool _writerJustLeftReadingRoom; // Flaga informujaca o tym, ze pisarz wyszedl z czytelni i algorytm ma wpuscic wszystkich aktualnie oczekujacych czytelnikow
	volatile int _writersWaitingCounter, _readersWaitingCounter; // Liczniki oczekujacych pisarzy i czytelnikow
	std::mutex* _adjuvantMutex; //Pomocniczy mutex dbajacy o zachwowanie atomowosci wykonywanych operacji

public:
	CountingSemaphore(int maxCounter)
	{
		_maxResources = maxCounter;
		_freeResources = maxCounter;
		_writersWaitingCounter = _readersWaitingCounter = 0;
		_adjuvantMutex = new std::mutex();
		_writerJustLeftReadingRoom = FALSE;
	}

	void grantResourceForWriter()
	{
		_adjuvantMutex->lock();
		_writersWaitingCounter++;
		_adjuvantMutex->unlock();
		while (TRUE)
		{
			_adjuvantMutex->lock();
			//Warunek przyznania dostêpu pisarzowi: Czytelnia jest pusta oraz nie mamy do czynienia z sytuacja, w ktorej inny pisarz wlasnie opucil czytelnie
			//(drugi warunek jest pomijany, jezeli zaden czytelnik nie oczekuje na dostep)
			if ((_freeResources == _maxResources) && (_writerJustLeftReadingRoom != TRUE || _readersWaitingCounter == 0))
			{
				_writersWaitingCounter--;
				_freeResources = 0; //Przyznanie dostpu wylcznego do zasobu
				_adjuvantMutex->unlock();
				break;
			}
			_adjuvantMutex->unlock();
			Sleep(1);
		}
	}
	
	void grantResourceForReader()
	{
		_adjuvantMutex->lock();
		_readersWaitingCounter++;
		_adjuvantMutex->unlock();
		while (TRUE)
		{
			_adjuvantMutex->lock();
			//Warunek przyznania dostepu czytelnikowi: W czytelni znajduje siê miejsce dla czytelnika, nie ma w niej obecnie pisarza oraz pisarz nie czaka w kolejce
			//(ostatni warunek jest pomijany, je¿eli flaga _writerJustLeftReadingRoom ma wartoœæ TRUE)
			if ((_freeResources > 0) && (_writersWaitingCounter == 0 || _writerJustLeftReadingRoom))
			{
				_readersWaitingCounter--;
				if (_readersWaitingCounter == 0)
					_writerJustLeftReadingRoom = FALSE;
				_freeResources--; //Przyznanie dostepu
				_adjuvantMutex->unlock();
				break;
			}
			_adjuvantMutex->unlock();
			Sleep(1);
		}
	}

	void releaseResourceTakenByReader() //Protokol koncowy czytelnika
	{
		_adjuvantMutex->lock();
		_freeResources ++;
		_adjuvantMutex->unlock();
	}

	void releaseResourceTakenByWriter() // Protokol koncowy pisarza
	{
		_adjuvantMutex->lock();
		_freeResources=_maxResources;
		_writerJustLeftReadingRoom = TRUE;
		_adjuvantMutex->unlock();
	}

	~CountingSemaphore()
	{
		delete _adjuvantMutex;
	}
};
