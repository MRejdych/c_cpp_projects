#include<iostream>

using namespace std;

int poczatek, koniec;

void Merge(int tablica[], int poczatek, int srodek, int koniec) {
    int n1, n2;
    n1 = (srodek - poczatek + 1);
    n2 = (koniec - srodek);
    int *tabL = new int[(srodek - poczatek + 1)];
    int *tabP = new int[(koniec - srodek)];
    int i, j;

    for (i = 0; i < (srodek - poczatek + 1); i++) {
        tabL[i] = tablica[(poczatek + i)];
    }

    for (j = 0; j < (koniec - srodek); j++) {
        tabP[j] = tablica[(srodek + 1 + j)];
    }


    i = j = 0;
    int k;
    int quit = 0;

    for (k = poczatek; k <= koniec; k++) {
        if (i >= n1 || j >= n2) {
            quit = 1;
            break;
        }

        if ((tabL[i] <= tabP[j])) {

            tablica[k] = tabL[i];
            i++;

        } else {
            tablica[k] = tabP[j];
            j++;
        }
    }

    if (quit) {
        if (i >= n1)
            while (k <= koniec) {
                tablica[k] = tabP[j];
                j++;
                k++;
            }

        else if (j >= n2)
            while (k <= koniec) {
                tablica[k] = tabL[i];
                i++;
                k++;
            }
    }


    cout << endl;
    for (i = poczatek; i <= koniec; i++) // wypisanie posortowanej tablicy
        cout << "tablica[" << i << "] = " << tablica[i] << endl;
}


void Merge_Sort(int tablica[], int poczatek, int koniec) {
    if (poczatek != koniec) {
        int srodek = (poczatek + koniec) / 2;
        Merge_Sort(tablica, poczatek, srodek);
        Merge_Sort(tablica, srodek + 1, koniec);
        Merge(tablica, poczatek, srodek, koniec);
    }
}


int main() {
    int liczba_elementow;
    cout << "Podaj liczb� element�w: ";
    cin >> liczba_elementow;
    int *tablica = new int[liczba_elementow];

    for (int e = 0; e < liczba_elementow; e++) {
        cout << "Podaj element " << e + 1 << " ";
        cin >> tablica[e];
    }

    Merge_Sort(tablica, 0, liczba_elementow - 1);

    cout << "\n\nPo sortowaniu: ";

    for (int e = 0; e < liczba_elementow; e++) {
        cout << tablica[e] << " ";
    }
    int czas;
    cin >> czas;
}







