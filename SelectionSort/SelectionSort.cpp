#include<iostream>

using namespace std;

float tablica[10] = {10.2, 10.1, 13.4, 2.1, 3.5, 1.1, 0.7, 1.71, 2.11, 3.77};


void Selection_Sort(float tab[], int n);

int main() {
    Selection_Sort(tablica, 10);

    for (int i = 0; i < 10; i++)
        cout << tablica[i] << "    ";

    int c;
    cout << "\n\nAby zakonczyc dzialanie programu wprowadz dowolny znak i wcisnij enter.   ";
    cin >> c;

    return 0;
}

void Selection_Sort(float tab[], int n) {
    int najmniejszy;

    for (int i = 0; i < n - 2; i++) {
        najmniejszy = i;
        for (int j = i + 1; j < n; j++)
            if (tab[i] > tab[j])
                najmniejszy = j;
        float temp = tab[i];
        tab[i] = tab[najmniejszy];
        tab[najmniejszy] = temp;
    }
}