#include<iostream>


using namespace std;

double tablica[10] = {10.2, 10.1, 13.4, 2.1, 3.5, 1.1, 0.7, 1.71, 2.11, 3.77};

void Merge_Sort(double tab[], int p, int r);

void Merge(double tab[], int p, int q, int r);

int main() {
    Merge_Sort(tablica, 0, 9);

    for (int i = 0; i <= 9; i++) {
        cout << "Element " << i << ":  " << tablica[i] << endl;
    }

    int c;
    cin >> c;
    return 0;
}

void Merge_Sort(double tab[], int p, int r) {


    if (p < r) {
        int q = (p + r) / 2;
        Merge_Sort(tab, p, q);
        Merge_Sort(tab, q + 1, r);
        Merge(tab, p, q, r);
    }

}

void Merge(double tab[], int p, int q, int r) {
    int n1 = (q - p + 1);
    int n2 = (r - q);

    double *tabL = new double[(n1 + 1)];
    double *tabR = new double[(n2 + 1)];
    int i = 0, j = 0;

    for (i; i < n1; i++) {
        tabL[i] = tab[(p + i)];
    }
    tabL[i] = 10000;

    for (j; j < n2; j++) {
        tabR[j] = tab[(q + j + 1)];
    }
    tabR[j] = 10000;

    i = 0, j = 0;
    for (int k = p; k <= r; k++) {
        if (tabL[i] <= tabR[j]) {
            tab[k] = tabL[i];
            i++;
        } else {
            tab[k] = tabR[j];
            j++;
        }

    }
    delete tabL;
    delete tabR;
} 
