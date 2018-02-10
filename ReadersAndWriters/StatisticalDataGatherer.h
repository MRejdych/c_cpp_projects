#pragma once

#include <windows.h>
#include <math.h>
#include <mutex>
#include <fstream>

/*Klasa odpowiada za gromadzenie i przetwarzanie danych statystycznych dotycz�cych czas�w odczytu i zapisu*/

class StatisticalDataGatherer {
private:
    int _writersAmount;
    int _readersAmount;
    volatile int _savedWritersTimes; //Liczby zapisanych czas�w pracy czytelnik�w i pisarzy
    volatile int _savedReadersTimes;
    float *writersWorkTimesData; //Tablice z wynikami czasu pracy czytelnik�w i pisarzy
    float *readersWorkTimesData;
    std::mutex *_adjuvantMutex; //Pomocniczy mutex dbaj�cy o zachwowanie atomowo�ci wykonywanych operacji

    std::fstream file; // Obiekt klasy fstream wykorzystywany do zapisywania wynik�w do pliku

public:
    StatisticalDataGatherer(int writers, int readers) {
        _writersAmount = writers;
        _readersAmount = readers;
        writersWorkTimesData = new float[_writersAmount];
        readersWorkTimesData = new float[_readersAmount];
        _adjuvantMutex = new std::mutex();
        _savedWritersTimes = 0;
        _savedReadersTimes = 0;
    }

    void addWritingTime(float writingTime) //Dodaje czas pracy pisarza do tablicy
    {
        _adjuvantMutex->lock();
        if (_savedWritersTimes < _writersAmount) {
            writersWorkTimesData[_savedWritersTimes] = writingTime;
            _savedWritersTimes++;
        }
        _adjuvantMutex->unlock();
    }

    void addReadingTime(float readingTime) //Dodaje czas pracy czytelnika do tablicy
    {
        _adjuvantMutex->lock();
        if (_savedReadersTimes < _readersAmount) {
            readersWorkTimesData[_savedReadersTimes] = readingTime;
            _savedReadersTimes++;
        }
        _adjuvantMutex->unlock();
    }

    float getMaximalWritingTime() // Zwraca maksymalny czas zapisu
    {
        float maxWritingTime = 0.0;
        for (int i = 0; i < _writersAmount; i++) {
            if (writersWorkTimesData[i] > maxWritingTime) {
                maxWritingTime = writersWorkTimesData[i];
            }
        }
        return maxWritingTime;
    }

    float getMinimalWritingTime() // Zwraca minimalny czas zapisu
    {
        float minWritingTime = writersWorkTimesData[0];
        for (int i = 1; i < _writersAmount; i++) {
            if (writersWorkTimesData[i] < minWritingTime) {
                minWritingTime = readersWorkTimesData[i];
            }
        }
        return minWritingTime;
    }

    float getAverageWritingTime() // Oblicza �redni czas zapisu
    {
        float avg
                = 0;
        for (int i = 0; i < _writersAmount; i++) {
            avg += writersWorkTimesData[i];
        }
        avg = avg / _writersAmount;
        return avg;
    }

    float getWritingTimeStandardDeviation() // Oblicza odchylenie standardowe od �redniego czasu zapisu
    {
        float writingAverageTime = getAverageWritingTime();
        float standardDeviation = 0;
        for (int i = 0; i < _writersAmount; i++) {
            standardDeviation += pow((writersWorkTimesData[i] - writingAverageTime), 2);
        }
        standardDeviation = sqrt(standardDeviation / (_writersAmount - 1));

        return standardDeviation;
    }

    float getMaximalReadingTime() // Zwraca maxymalny czas odczytu
    {
        float maxReadingTime = 0.0;
        for (int i = 0; i < _readersAmount; i++) {
            if (readersWorkTimesData[i] > maxReadingTime) {
                maxReadingTime = readersWorkTimesData[i];
            }
        }
        return maxReadingTime;
    }

    float getMinimalReadingTime() // Zwraca minimalny czas odczytu
    {
        float minReadingTime = readersWorkTimesData[0];
        for (int i = 1; i < _readersAmount; i++) {
            if (readersWorkTimesData[i] < minReadingTime) {
                minReadingTime = readersWorkTimesData[i];
            }
        }
        return minReadingTime;
    }

    float getAverageReadingTime() // Oblicza �redni czas odczytu
    {
        float avg = 0;
        for (int i = 0; i < _readersAmount; i++) {
            avg += readersWorkTimesData[i];
        }
        avg = avg / _readersAmount;
        return avg;
    }

    float getReadingTimeStandardDeviation() // Oblicza odchylenie standardowe od �redniego czasu odczytu
    {
        float readingAverageTime = getAverageReadingTime();
        float standardDeviation = 0;
        for (int i = 0; i < _readersAmount; i++) {
            standardDeviation += pow((readersWorkTimesData[i] - readingAverageTime), 2);
        }
        standardDeviation = sqrt(standardDeviation / (_readersAmount - 1));

        return standardDeviation;
    }

    void
    saveToFile() {        //Zapisuje do pliku Srednie czas pracy, odchylenia standardowe, czasy maksymalne i minimalne.
        file.open("outputWriters.txt", std::ios::out);

        file << "Sredni czas pracy pisarza " << getAverageWritingTime() << " ms." << std::endl;
        file << "Odchylenie std pisarza " << getWritingTimeStandardDeviation() << " ms." << std::endl;
        file << "Minimalny czas pracy pisarza " << getMinimalWritingTime() << " ms." << std::endl;
        file << "Maksymalny czas pracy pisarza " << getMaximalWritingTime() << " ms." << std::endl;

        file.close();
        file.clear();

        file.open("outputReaders.txt", std::ios::out);
        file << "Sredni czas pracy czytelnika " << getAverageReadingTime() << " ms." << std::endl;
        file << "Odchylenie std czytelnika " << getReadingTimeStandardDeviation() << " ms." << std::endl;
        file << "Minimalny czas pracy czytelnika " << getMinimalReadingTime() << " ms." << std::endl;
        file << "Maksymalny czas pracy czytelnika " << getMaximalReadingTime() << " ms." << std::endl;
        file.close();
        file.clear();

    }


    ~StatisticalDataGatherer() {
        delete _adjuvantMutex;
        delete[]writersWorkTimesData;
        delete[]readersWorkTimesData;
    }
};


