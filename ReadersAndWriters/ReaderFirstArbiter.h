#pragma once

#include <windows.h>
#include "Arbiter.h"

// Klasa implementuj�ca algorytm faworyzuj�cy czytelnik�w, dziedzicz�ca po klasie Arbiter. Czytelnia ma nieograniczon� pojemno��
class ReaderFirstArbiter : public Arbiter {
private:
    HANDLE _readSemaphore; //Semafor bitowy (mutex)
    HANDLE _writeSemaphore; // Semafor bitowy (mutex)
    int _readers; // Licznik pracuj�cych czytelnik�w
    bool _anyWaitingReader; //Flaga informuj�ca, czy jakikolwiek czytelnik czeka na dost�p

public:
    ReaderFirstArbiter() {
        _readSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
        _writeSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
        _readers = 0;
        _anyWaitingReader = false;
    }

    virtual void startRead() //Protoko�y wst�pne czytelnika
    {
        //Blokuje _readSemaphore i czeka na dost�p do _writeSemaphore je�eli �aden czytelnik nie jest aktualnie w czytelni
        WaitForSingleObject(_readSemaphore, INFINITE);
        if (_readers == 0) {
            _anyWaitingReader = true;
            WaitForSingleObject(_writeSemaphore, INFINITE);
            _anyWaitingReader = false;
        }
        ++_readers;
        ReleaseSemaphore(_readSemaphore, 1, NULL); //Zwalnia _readSemaphore
    }

    virtual void endRead() {
        WaitForSingleObject(_readSemaphore, INFINITE);
        --_readers;
        //Je�eli po wyj�ciu czytelnika czytelnia pozosta�a pusta, zwalnia _writeSemaphore
        if (_readers == 0) {
            ReleaseSemaphore(_writeSemaphore, 1, NULL);
        }
        ReleaseSemaphore(_readSemaphore, 1, NULL);
    }

    virtual void startWrite() {
        //Pisarz blokuje _writeSemaphore w przypadku, gdy �aden czytelnik nie czeka na dost�p
        do {
            WaitForSingleObject(_writeSemaphore, INFINITE);
            if (_anyWaitingReader) {
                ReleaseSemaphore(_writeSemaphore, 1, NULL);
            } else {
                break;
            }
        } while (true);

    }

    virtual void endWrite() {
        ReleaseSemaphore(_writeSemaphore, 1, NULL);
    }

    ~ReaderFirstArbiter() {
        CloseHandle(_writeSemaphore);
        CloseHandle(_readSemaphore);
    }
};


