#pragma once

#include "Arbiter.h"
#include "Generator.h"
#include <Windows.h>
#include <string>

class File
{
private:
	bool _printDebugInfo; // Okreœla, czy na ekranie zostan¹ wypisane dane dotycz¹ce treœci odczytów i zapisów oraz ich czasów
	std::string _content;
	Arbiter* _arbiter; //Obiekt reprezentuj¹cy wybrany algorytm synchronizuj¹cy
	

	std::string part1[7] = { "Tomek ", "Ala ", "Maciek ", "Andrzej ", "Kot ", "Pies ", "Mikolaj " };
	std::string part2[7] = { "niszczy ", "kupuje ", "przewozi ", "sprzata ", "pisze ", "przenosi ", "widzi " };
	std::string part3[7] = { "projekt.", "kota.", "psa.", "pokoj.", "ksiazke.", "samochod.", "telewizor." };

	void stringCreator() { //Zastêpuje poprzedni¹ zawartoœæ _content now¹ w kilku krokach. Operacja nie jest atomowa.
		_content = part1[Generator::generateRandom() % 6];
		_content += part2[Generator::generateRandom() % 6];
		_content += part3[Generator::generateRandom() % 6];  
	}

public:
	File(Arbiter* arbiter, bool printDebugInfo)
		: _content("Poczatkowa zawartosc pliku"), _arbiter(arbiter), _printDebugInfo(printDebugInfo)
	{
	}

	void read() {
		_arbiter->startRead(); //Wywo³anie protoko³ów wstêpnych czytelnika
		Sleep(2);
		if (_printDebugInfo) {
			printf("[%d] Read: %s\n", GetCurrentThreadId(), _content.c_str()); //Odczyt
		}
		_arbiter->endRead(); //Wywo³anie protoko³ów koñcowych czytelnika
	}

	void write()
	{
		_arbiter->startWrite(); //Wywo³anie protoko³ów wstepnych pisarza.
		Sleep(2);
		stringCreator(); //Zapis
		if (_printDebugInfo == TRUE) {
			printf("[%d] Written: %s\n", GetCurrentThreadId(), _content.c_str());
		}
		_arbiter->endWrite(); //Wywo³anie protoko³ów koñcowych pisarza.
	}

	~File() {
		delete _arbiter;
	}
};
