#include<iostream>+
using namespace std;

int tablica[10] = { 6,4,2,1,3,5,0,2,4,0 };


int *Equal_Count(int tablica[], int n, int m);
int *Lesser_Count(int *equal, int m);
int *Reorganise(int *lesser, int tablica[], int n, int m);
int *Counting_Sort(int tablica[], int n, int m);


int main()
{
	int *tablica_sorted = new int[10];
	tablica_sorted = Counting_Sort(tablica, 10, 7);

	cout << "Przed sortowaniem:  " << endl;
	for (int i = 0; i < 10; i++)
		cout << tablica[i] << " | ";

	cout << endl << "Po sortowaniu: " << endl;
	for (int i = 0; i < 10; i++)
		cout << tablica_sorted[i] << " | ";
	cout << endl;

	int c;
	cin >> c;

	return 0;
}


int *Equal_Count(int tablica[], int n, int m)
{
	int *equal = new int [m];
	int klucz = 0;
	for (int i = 0; i < m; i++)
	{
		equal[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		klucz = tablica[i];
		equal[klucz]++;

	}
	return equal;
}

int *Lesser_Count(int *equal, int m)
{
	

	int *lesser = new int [m];

	lesser[0] = 0;
	for (int i = 1; i < m; i++)
	{
		lesser[i] = lesser[i - 1] + equal[i - 1];
	}

	return lesser;
}

int *Reorganise(int *lesser, int tablica[], int n, int m)
{
	int *next = new int[m];
	int *tablica_sorted = new int [n];
	
	for (int i = 0; i < 7; i++)
	{
		next[i] = (lesser[i]);
		
	}
	

	int key = 0, indeks = 0;
	
	for (int i = 0; i < n; i++)
	{
		key = tablica[i];
		indeks = next[key];
		tablica_sorted[indeks] = key;
		next[key]++;

	}

	return tablica_sorted;
}

int *Counting_Sort(int tablica[], int n, int m)
{
	int *lesser = new int[m];
	int *equal = new int[m];
	int *tablica_sorted = new int[n];


	equal = Equal_Count(tablica, n, m);
	lesser = Lesser_Count(equal, m);
	tablica_sorted = Reorganise(lesser, tablica, n, m);

	return tablica_sorted;
}



