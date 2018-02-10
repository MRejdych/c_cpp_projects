// Wyszukiwanie Binarne.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
using namespace std;

int tablica[10] = { 1,5,9,11,13,17,19,21,24,28 };

int BinarySearch(int tab[], int p, int n, int x);



int main()
{
	int x;
	cout << "Podaj szukana liczbe." << endl;
	cin >> x;
	int indeks = BinarySearch(tablica, 0, 9, x);
	if(indeks != -1)
		cout << "indeks szukanej liczby w tablicy to:  " << indeks << endl;
	int c;
	cout << "Wprowadz dowolny znak i wcisnij enter aby zakonczyc prace programu." << endl;
	cin >> c;
    return 0;
}

int BinarySearch(int tab[], int p, int n, int x)
{
	if (p <= n)
	{
		int q = (p + n) / 2;
		if (tab[q] == x)
		{
			return q;
		}
		else if (tab[q] > x)
		{
			BinarySearch(tab, p, q - 1, x);
		}
		else
		{
			BinarySearch(tab, q + 1, n, x);
		}
	}
	else
		cout << "Nie odnaleziono szukanej liczby" << endl;
	return -1;
}

