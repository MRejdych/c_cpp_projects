#include<iostream>

using namespace std;

int intsTable[10] = {6, 4, 2, 1, 3, 5, 0, 2, 4, 0};


int *Equal_Count(int tab[], int n, int m);

int *Lesser_Count(int *equal, int m);

int *Reorganise(int *lesser, int tab[], int n, int m);

int *Counting_Sort(int tab[], int n, int m);


int main() {
    int *tab_sorted = new int[10];
    tab_sorted = Counting_Sort(intsTable, 10, 7);

    cout << "Before sorting:  " << endl;
    for (int i = 0; i < 10; i++)
        cout << intsTable[i] << " | ";

    cout << endl << "Sorted: " << endl;
    for (int i = 0; i < 10; i++)
        cout << tab_sorted[i] << " | ";
    cout << endl;

    int c;
    cin >> c;

    return 0;
}


int *Equal_Count(int tab[], int n, int m) {
    int *equal = new int[m];
    int key = 0;
    for (int i = 0; i < m; i++) {
        equal[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        key = tablica[i];
        equal[key]++;

    }
    return equal;
}

int *Lesser_Count(int *equal, int m) {


    int *lesser = new int[m];

    lesser[0] = 0;
    for (int i = 1; i < m; i++) {
        lesser[i] = lesser[i - 1] + equal[i - 1];
    }

    return lesser;
}

int *Reorganise(int *lesser, int tab[], int n, int m) {
    int *next = new int[m];
    int *tab_sorted = new int[n];

    for (int i = 0; i < 7; i++) {
        next[i] = (lesser[i]);
    }

    int key = 0, index = 0;

    for (int i = 0; i < n; i++) {
        key = tab[i];
        indeks = next[key];
        tab_sorted[index] = key;
        next[key]++;
    }

    return tab_sorted;
}

int *Counting_Sort(int tab[], int n, int m) {
    int *lesser = new int[m];
    int *equal = new int[m];
    int *tab_sorted = new int[n];


    equal = Equal_Count(tab, n, m);
    lesser = Lesser_Count(equal, m);
    tab_sorted = Reorganise(lesser, tab, n, m);

    return tab_sorted;
}



