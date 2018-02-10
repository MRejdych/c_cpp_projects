#include <iostream>

#include "File.h"
#include "StatisticalDataGatherer.h"
#include "Writer.h"
#include "Reader.h"
#include "SimpleArbiter.h"
#include "MutexArbiter.h"
#include "CountingSemaphoreArbiter.h"
#include "ReaderFirstArbiter.h"
#include "WriterFirstArbiter.h"
using namespace std;

//Z racji tego, ¿e metoda WaitForMultipleObjects moze czekac na maksymalnie 64 watki, jest wywo³ywana kilkukrotnie w zaleznosci od liczby watkow
void waitForThreads(DWORD nCount, const HANDLE *lpHandles, BOOL bWaitAll, DWORD dwMILIseconds);

int main(int argc, char** argv)
{
	int _writers = 0; // Liczba czytelnikow i pisarzy
	int _readers = 0;
	int _experimentRepeat = 10;

	char arbiterType = '0'; //Wybor algorytmu

	char debugInfo = '0'; //Czy komunikaty informujace o czasie zapisu i odczytu maj¹ byc wyswietlone na ekranie
	bool printDebugInfo = FALSE;

	File* _myFile = NULL;


	cout << "Podaj liczbe czytelnikow." << endl;
	cin >> _readers;

	cout << "Podaj liczbe pisarzy." << endl;
	cin >> _writers;

	cout << "Wybierz, w jaki sposob program ma synchronizowac watki:" << endl		
		<< "Mutex: wpisz 1." << endl
		<< "Semafor zliczajacy: wpisz 2." << endl
		<< "ReaderFirstArbiter: wpisz 3." << endl
		<< "WriterFirstArbiter: wpisz 4." << endl;
	cin >> arbiterType;

	cout << endl << "Wybierz typ komunikatow" << endl
		<< "Brak komunikatow: wpisz 0" << endl
		<< "Tresc odczytow, zapisow: wpisz 1." << endl;
	cin >> debugInfo;
	if (debugInfo == '1'){
		printDebugInfo = TRUE;
	}

	StatisticalDataGatherer* _statisticalData = new StatisticalDataGatherer((_writers*_experimentRepeat), (_readers*_experimentRepeat)); //Obiekt przechowujacy i przetwarzajacy dane statystyczne


	HANDLE* handlers = new HANDLE[_writers + _readers];		// Tablica uchwytow do tworzonych watkow
	Reader** readersThreadsPointers = new Reader*[_readers]; //Tablice referencji do watkow pisarzy i czytelnikow
	Writer** writersThreadsPointers = new Writer*[_writers];

	switch (arbiterType){ //Wybór algorytmu
	case '1':
		_myFile = new File(new MutexArbiter(), printDebugInfo);
		break;
	case '2':
		_myFile = new File(new CountingSemaphoreArbiter(100), printDebugInfo);
		break;
	case '3':
		_myFile = new File(new ReaderFirstArbiter(), printDebugInfo);
		break;
	case '4':
		_myFile = new File(new WriterFirstArbiter(), printDebugInfo);
		break;
	}

	// Petla wywolujaca eksperyment (symulacje z wybranym algorytmem i podana liczba czytelnikow i pisarzy) dana ilosc razy
	for (int e = 1; e <= _experimentRepeat; e++){
		for (int i = 0; i < _writers; ++i){ //Uruchomienie watkow pisarzy
			Writer* writer = new Writer(i, _myFile, printDebugInfo);
			handlers[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread::runThread, writer, 0, NULL);
			writersThreadsPointers[i] = writer; //Zapis wskaznika do watku
		}

		for (int j = 0; j < _readers; ++j){ //Uruchomienie watkow czytelnikow
			Reader* reader = new Reader(j, _myFile, printDebugInfo);
			handlers[_writers + j] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread::runThread, reader, 0, NULL);
			readersThreadsPointers[j] = reader; //Zapis wskaznika do watku
		}

		//Oczekiwanie na zakonczenie pracy wszystkich watkow bioracych udzial w pojedynczym eksperymencie
		waitForThreads(_writers + _readers, handlers, TRUE, INFINITE); 

		// Zapisanie czasow pracy pisarzy i czytelnikow bioracych udzial w danym eksperymencie do obiektu klasy StatisticalDataGatherer
		for (int i = 0; i < _writers; i++){
			_statisticalData->addWritingTime(writersThreadsPointers[i]->getWorkTime());
		}

		for (int j = 0; j < _readers; j++){							
			_statisticalData->addReadingTime(readersThreadsPointers[j]->getWorkTime());
		}
	}


	 // Wyswietlanie statystyk na ekranie
		cout.precision(5);
		float avgReadingTime = _statisticalData->getAverageReadingTime();
		float ReadingTimeStandardDeviation = _statisticalData->getReadingTimeStandardDeviation();
		float minReadingTime = _statisticalData->getMinimalReadingTime();
		float maxReadingTime = _statisticalData->getMaximalReadingTime();

		float avgWritingTime = _statisticalData->getAverageWritingTime();
		float WritingTimeStandardDeviation = _statisticalData->getWritingTimeStandardDeviation();
		float minWritingTime = _statisticalData->getMinimalWritingTime();
		float maxWritingTime = _statisticalData->getMaximalWritingTime();

		cout << endl << "Sredni czas, ktory watek musial przeznaczyc na odczyt: " << avgReadingTime << " milisekund(y). " << endl
			<< "Odchylenie standardowe: " << ReadingTimeStandardDeviation << " milisekund(y)." << endl
			<< "Maksymalny czas odczytu: " << maxReadingTime << " milisekund(y)." << endl
			<< "Minimalny czas odczytu: " << minReadingTime << " milisekund(y)." << endl << endl;
		cout << "Sredni czas, ktory watek musial przeznaczyc na zapis: " << avgWritingTime << " milisekund(y)." << endl
			<< "Odchylenie standardowe: " << WritingTimeStandardDeviation << " milisekund(y)." << endl
			<< "Maksymalny czas zapisu: " << maxWritingTime << " milisekund(y)." << endl
			<< "Minimalny czas zapisu: " << minWritingTime << " milisekund(y)." << endl;
	
	cout << endl << "Wcisnij dowolny klawisz i zatwierdz wciskajac Enter." << endl;

	_statisticalData->saveToFile(); // Zapis do pliku statystyk przechowywanych przez obiekt klasy StatisticalDataGatherer o nazwie _statisticalData

	char exit;				//Oczekiwanie na potwierdzenie zakonczenia dzialania programu											
	std::cin >> exit;
	return 0;
}



void waitForThreads(DWORD nCount, const HANDLE *lpHandles, BOOL bWaitAll, DWORD dwMILIseconds) {
	int fullRounds = nCount / 64;
	int nCountInLastRound = nCount % 64;
	int i = 0;
	while (i < fullRounds) {
		WaitForMultipleObjects(64, lpHandles + (64 * i), bWaitAll, dwMILIseconds); //limit 64 w¹tków
		i++;
	}

	if (nCountInLastRound > 0) {
		WaitForMultipleObjects(nCountInLastRound, lpHandles + (64 * i), bWaitAll, dwMILIseconds);
	}
}