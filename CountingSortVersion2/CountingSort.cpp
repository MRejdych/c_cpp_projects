#include<iostream>
using namespace std;

void CountingSort(int tab[], int tabSorted[], int k);
int l, k;

int main()
{
	cout << "Podaj liczbe elementow w tablicy:\t";
	cin >> l;

	int *tablica = new int[l];
	int *tabSorted = new int[l];

	cout << "\nPodaj przedzial wartosci elementow w tablicy od 0 do ... (nie wiekszy niz liczba jej elementow)" << endl;
	cin >> k;

	int c=0, y=0;
	while (c <= (l-1))
	{
		cout << "\nPodaj wartosc z przedialu od 0 do "<< k << " dla pola o indeksie " << c << ":  ";
		cin >> y;
		cout << endl;
		if (y >= 0 && y <= k)
		{
			tablica[c] = y;
			c++;
		}
		else
			cout << "\nPodales nieprawidlowa wartosc, sproboj ponownie.";
	}

	CountingSort(tablica, tabSorted, k);

	cout << endl;
	for (int i = 0; i < l; i++)
	{
		cout << tabSorted[i] << ", ";
	}

	int x;
	cin >> x; 


	return 0;
}


void CountingSort(int tab[], int tabSorted[], int k)
{

	//cout << endl << "tablica" << endl;
	//for (int i = 0; i < l; i++)
	//{
	//	cout << tab[i] << ", ";
	//}


	int *before = new int[(k+1)];
	for (int i = 0; i <= k; i++)
	{
		before[i] = 0;
	}
	for (int j = 0; j < l; j++)
	{
		before[tab[j]]++;
	}
	for (int i = 1; i <= k; i++)
	{
		before[i] = before[i] + before[(i - 1)];
	}
	
	cout << endl << "before" << endl;
	for (int i = 0; i <=k; i++)
	{
		cout << before[i] << ", ";
	}


	for (int j = (l - 1); j > 0; j--)
	{   
		tabSorted[before[tab[j]]] = tab[j];
		before[tab[j]]--;
	}
	cout << "TABSORTED 0" << before[0] << endl;
	cout << "\n\n";
	for (int i = 0; i < l; i++)
	{
		cout << tabSorted[i] << ", ";
	}
	cout << endl;

}