#pragma once

#include "Arbiter.h"

#include <windows.h>

class SimpleArbiter : public Arbiter
{
private:
	HANDLE _readSemaphore;
	HANDLE _writeSemaphore;
	volatile int _readers;

public:
	SimpleArbiter()
	{
		_readSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
		_writeSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
		_readers = 0;
	}

	virtual void startRead()
	{
		WaitForSingleObject(_readSemaphore, INFINITE);
		if (_readers == 0) {
			WaitForSingleObject(_writeSemaphore, INFINITE);
		}
		++_readers;
		ReleaseSemaphore(_readSemaphore, 1, NULL);
	}

	virtual void endRead()
	{
		WaitForSingleObject(_readSemaphore, INFINITE);
		--_readers;
		if (_readers == 0) {
			ReleaseSemaphore(_writeSemaphore, 1, NULL);
		}
		ReleaseSemaphore(_readSemaphore, 1, NULL);
	}

	virtual void startWrite()
	{
		WaitForSingleObject(_writeSemaphore, INFINITE);
	}

	virtual void endWrite()
	{
		ReleaseSemaphore(_writeSemaphore, 1, NULL);
	}

	~SimpleArbiter()
	{
		CloseHandle(_writeSemaphore);
		CloseHandle(_readSemaphore);
	}
};

