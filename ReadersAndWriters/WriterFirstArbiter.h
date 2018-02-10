#pragma once

#include <Windows.h>
#include "Arbiter.h"


class WriterFirstArbiter : public Arbiter {
private:
    HANDLE _readersCounterSemaphore; //Semafor synchronizuj�cy dost�p do licznika pracujacych czytelnik�w
    HANDLE _writersCounterSemaphore; // Semafor synchronizuj�cy dost�p do licznika pracuj�cych pisarzy
    HANDLE _accessSemaphore; //Semafor synchronizuj�cy dost�p do zasobu
    HANDLE _newReadersAllowedSemaphore; //Semafor dopuszczaj�cy nowych czytelnik�w do semafora _accessSemaphore
    int _readers; //Liczniki pracuj�cych czytelnik�w i pisarzy
    int _writers;

public:
    WriterFirstArbiter() {
        _readersCounterSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
        _writersCounterSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
        _accessSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
        _newReadersAllowedSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
        _readers = 0;
        _writers = 0;
    }

    //Protoko�y wst�pne czytelnika
    virtual void startRead() {
        WaitForSingleObject(_newReadersAllowedSemaphore, INFINITE);
        ReleaseSemaphore(_newReadersAllowedSemaphore, 1, NULL);

        WaitForSingleObject(_readersCounterSemaphore, INFINITE);
        if (_readers == 0) {
            WaitForSingleObject(_accessSemaphore, INFINITE);
        }
        ++_readers;
        ReleaseSemaphore(_readersCounterSemaphore, 1, NULL);
    }

    //Protoko�y ko�cowe czytelnika
    virtual void endRead() {
        WaitForSingleObject(_readersCounterSemaphore, INFINITE);
        --_readers;

        if (_readers == 0) {
            ReleaseSemaphore(_accessSemaphore, 1, NULL);
        }
        ReleaseSemaphore(_readersCounterSemaphore, 1, NULL);
    }

    //Protoko�o wst�pne pisarza
    virtual void startWrite() {
        WaitForSingleObject(_writersCounterSemaphore, INFINITE);
        if (_writers == 0) {
            WaitForSingleObject(_newReadersAllowedSemaphore, INFINITE);
        }
        ++_writers;
        ReleaseSemaphore(_writersCounterSemaphore, 1, NULL);

        WaitForSingleObject(_accessSemaphore, INFINITE);
    }

    //Protoko�y ko�cowe pisarza
    virtual void endWrite() {
        ReleaseSemaphore(_accessSemaphore, 1, NULL);

        WaitForSingleObject(_writersCounterSemaphore, INFINITE);
        --_writers;
        if (_writers == 0) {
            ReleaseSemaphore(_newReadersAllowedSemaphore, 1, NULL);
        }
        ReleaseSemaphore(_writersCounterSemaphore, 1, NULL);
    }

    ~WriterFirstArbiter() {
        CloseHandle(_newReadersAllowedSemaphore);
        CloseHandle(_accessSemaphore);
        CloseHandle(_writersCounterSemaphore);
        CloseHandle(_readersCounterSemaphore);
    }
};




