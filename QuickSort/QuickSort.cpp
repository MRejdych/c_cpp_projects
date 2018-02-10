#include<iostream>

using namespace std;

int tablica[20] = {20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};


void Quicksort(int tab[], int p, int r);

int Partition(int tab[], int p, int r);


int main() {

    Quicksort(tablica, 0, 19);

    for (int i = 0; i <= 19; i++) {
        cout << tablica[i] << endl;
    }

    int c;
    cin >> c;

    return 0;
}

void Quicksort(int tab[], int p, int r) {
    if (p < r) {
        int q = Partition(tab, p, r);
        Quicksort(tab, p, q - 1);
        Quicksort(tab, q + 1, r);
    }
}

int Partition(int tab[], int p, int r) {
    int q = p;
    int temp;
    int pivot = tab[r];

    for (int u = p; u < r; u++)
        if (tab[u] <= pivot) {
            temp = tab[u];
            tab[u] = tab[q];
            tab[q] = temp;
            q++;
        }

    temp = tab[r];
    tab[r] = tab[q];
    tab[q] = temp;

    return q;
}