#pragma once

#include <time.h>
#include "Thread.h"
#include "File.h"

class Writer : public Thread {
private:
    clock_t _startTime;
    clock_t _endTime;
    float _workTime;  // _endTime - _startTime
    int _id;
    File *_file;
    bool _printTimeInfo;

public:
    Writer(int id, File *file, bool printTimeInfo)
            : _id(id), _file(file), _printTimeInfo(printTimeInfo) {
    }

    virtual void run() {
        Sleep(Generator::generateRandom() % 500);
        _startTime = clock(); //Liczba cykli zegara od uruchomienia programu do rozpocz�cia pracy w�tku
        _file->write();
        _endTime = clock(); //Liczba cykli zegara od uruchomienia programu do zaczko�czenia pracy w�tku
        _workTime = ((float) ((_endTime - _startTime)) / CLOCKS_PER_SEC) *
                    1000;//Czas pracy w�tku uzyskany dzi�ki obliczeniu
        // r�nicy mi�dzy pocz�tkiem pracy w�tku i podzieleniu jej
        // przez sta�� CLOCKS_PER_SEC oznaczaj�c� liczb� cykli na sekund�
        if (_printTimeInfo) {
            printf("Writer [%d] - Zapis trwal: %f milisekund(y).\n", GetCurrentThreadId(), _workTime);
        }
    }

    float getWorkTime() //Zwraca czas pracy w�tku
    {
        return _workTime;
    }

    ~Writer() {
    }
};
