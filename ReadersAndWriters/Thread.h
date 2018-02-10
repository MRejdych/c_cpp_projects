#pragma once

#include <Windows.h>

//Klasa Thread to klasa w�tku, po kt�rej dziedzicz� klasy w�tk�w-czytelnik�w oraz w�tk�w-pisarzy
class Thread {
public:
    virtual void run() = 0;

    //Metoda statyczna uruchamiaj�ca w�tek
    static DWORD WINAPI
    runThread(LPVOID
    args)
    {
        Thread *thread = (Thread *) args;
        thread->run();
        return 0;
    }

};
