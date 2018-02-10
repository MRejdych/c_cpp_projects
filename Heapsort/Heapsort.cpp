#include<iostream>

using namespace std;

int TabSize;
int HeapSize;

int Parent(int i);

int Left(int i);

int Right(int i);

void Heapify(int tab[], int i);

void BuildMaxHeap(int tab[]);

void Heapsort(int tab[]);

int main() {
    cout << "Enter amount of element on the heap" << endl;
    cin >> TabSize;
    int *tablica = new int[TabSize];
    cout << "\nEnter values on the heap" << endl;
    for (int i = 0; i < TabSize; i++) {
        cout << "Element " << i << ":\t";
        cin >> tablica[i];
        cout << endl;
    }

    Heapsort(tablica);

    for (int i = 0; i < TabSize; i++)
        cout << tablica[i] << ", ";

    cout << endl;
    int c;
    cin >> c;

    return 0;
}


int Parent(int i) // Procedura obliczajaca indeks rodzica wezla i
{
    return (i / 2);
}

int Left(int i) // Procedura obliczajaca indeks lewego dziecka wezla i
{
    if (i != 0)
        return (2 * i);
    else
        return 1;
}

int Right(int i) // Procedura obliczajaca indekst prawego dziecka wezla i
{
    if (i != 0)
        return ((2 * i) + 1);
    else
        return 2;
}

// Procedura Heapify przywracajaca wlasnosc kopca MAX dla poddrzewa zaczepionego w wezle i

void Heapify(int tab[], int i) {
    int r = Right(i);
    int l = Left(i);
    int largest = i;
    /* Sprawdzanie, czy dzieci wezla i sa od niego wieksze - jesli tak, wskazuje ktore z nich ma najwiekszy klucz */
    if (l < HeapSize && tab[l] > tab[i]) {
        largest = l;
    }
    if (r < HeapSize && tab[r] > tab[largest]) {
        largest = r;
    }
    if (largest !=
        i) // jezeli klucz wezla i nie jest najwiekszy, jest zamieniany z najwiekszym kluczem jego prawego lub lewego dziecka.
        // Nastepnie procedura Heapify wywolywana jest rekurencyjnie z indeksem zapisanym w zmiennej largest
    {
        int temp = tab[i];
        tab[i] = tab[largest];
        tab[largest] = temp;

        Heapify(tab, largest);
    }
}

// Procedura BuildMaxHeap wykorzystuje procedure Heapify do stworzenia kopca o wlasnosci MAX. Wszsytkie elementy od n/2 do n-1 sa liscmi, sa one jednoczesnie jednoelementowymi kopcami.
// Procedura przechodzi przez pozostale wezly i wywoluje na nich Heapify, by ustawic je w sposob spelniajacy wlasnosc kopca MAX.

void BuildMaxHeap(int tab[]) {
    HeapSize = TabSize;
    for (int i = (TabSize / 2); i >= 0; i--) {
        Heapify(tab, i);
    }

    for (int i = 0; i < TabSize; i++)
        cout << tab[i] << ", ";
    cout << endl;

}


//Procedura Heapsort jednorazowo korzysta z procedury BuildMaxHeap w celu przeksztalcenia tablicy wejsciowej w kopiec typu max. 
//Nastepnie, skoro najwiekszy element znajduje sie w tab[0], moze on zostac umieszczony na wlasciwym miejscu poprzez zamiane z tab[HeapSize].
//Nastepnie wykluczamy element bedacy na wlasciwym miejscu poprzez zmniejszenie wartosci HeapSize, wywolaniu Heapify w celu przywrocenia 
//wlasnosci kopca max i powtarzania tej czynnosci az HeapSize osiagnie wartosc 1. W tym momencie tablica jest posortowana rosnaco.

void Heapsort(int tab[]) {
    BuildMaxHeap(tab);
    for (int i = (TabSize - 1); i >= 1; i--) {
        int temp = tab[i];
        tab[i] = tab[0];
        tab[0] = temp;

        HeapSize--;
        Heapify(tab, 0);
    }

}


