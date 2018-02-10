#pragma once

#include "Arbiter.h"
#include "Generator.h"
#include <Windows.h>
#include <string>

class File {
private:
    bool _printDebugInfo; // Okre�la, czy na ekranie zostan� wypisane dane dotycz�ce tre�ci odczyt�w i zapis�w oraz ich czas�w
    std::string _content;
    Arbiter *_arbiter; //Obiekt reprezentuj�cy wybrany algorytm synchronizuj�cy


    std::string part1[7] = {"Tomek ", "Ala ", "Maciek ", "Andrzej ", "Kot ", "Pies ", "Mikolaj "};
    std::string part2[7] = {"niszczy ", "kupuje ", "przewozi ", "sprzata ", "pisze ", "przenosi ", "widzi "};
    std::string part3[7] = {"projekt.", "kota.", "psa.", "pokoj.", "ksiazke.", "samochod.", "telewizor."};

    void stringCreator() { //Zast�puje poprzedni� zawarto�� _content now� w kilku krokach. Operacja nie jest atomowa.
        _content = part1[Generator::generateRandom() % 6];
        _content += part2[Generator::generateRandom() % 6];
        _content += part3[Generator::generateRandom() % 6];
    }

public:
    File(Arbiter *arbiter, bool printDebugInfo)
            : _content("Poczatkowa zawartosc pliku"), _arbiter(arbiter), _printDebugInfo(printDebugInfo) {
    }

    void read() {
        _arbiter->startRead(); //Wywo�anie protoko��w wst�pnych czytelnika
        Sleep(2);
        if (_printDebugInfo) {
            printf("[%d] Read: %s\n", GetCurrentThreadId(), _content.c_str()); //Odczyt
        }
        _arbiter->endRead(); //Wywo�anie protoko��w ko�cowych czytelnika
    }

    void write() {
        _arbiter->startWrite(); //Wywo�anie protoko��w wstepnych pisarza.
        Sleep(2);
        stringCreator(); //Zapis
        if (_printDebugInfo == TRUE) {
            printf("[%d] Written: %s\n", GetCurrentThreadId(), _content.c_str());
        }
        _arbiter->endWrite(); //Wywo�anie protoko��w ko�cowych pisarza.
    }

    ~File() {
        delete _arbiter;
    }
};
