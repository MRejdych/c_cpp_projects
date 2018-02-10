#include<iostream>

using namespace std;

void CountingSort(int tab[], int tabSorted[], int k);

int l, k;

int main() {
    cout << "Enter number of values in table:\t";
    cin >> l;

    int *tab = new int[l];
    int *tabSorted = new int[l];

    cout << "\nEnter range of values in table from 0 to ... (not bigger than number of values in table)" << endl;
    cin >> k;

    int c = 0, y = 0;
    while (c <= (l - 1)) {
        cout << "\nEnter value from 0 to " << k << " for field at index " << c << ":  ";
        cin >> y;
        cout << endl;
        if (y >= 0 && y <= k) {
            tab[c] = y;
            c++;
        } else
            cout << "\nYou entered incorrect value. Try again..";
    }

    CountingSort(tab, tabSorted, k);

    cout << endl;
    for (int i = 0; i < l; i++) {
        cout << tabSorted[i] << ", ";
    }

    int x;
    cin >> x;


    return 0;
}


void CountingSort(int tab[], int tabSorted[], int k) {
    int *before = new int[(k + 1)];
    for (int i = 0; i <= k; i++) {
        before[i] = 0;
    }
    for (int j = 0; j < l; j++) {
        before[tab[j]]++;
    }
    for (int i = 1; i <= k; i++) {
        before[i] = before[i] + before[(i - 1)];
    }

    cout << endl << "before" << endl;
    for (int i = 0; i <= k; i++) {
        cout << before[i] << ", ";
    }


    for (int j = (l - 1); j > 0; j--) {
        tabSorted[before[tab[j]]] = tab[j];
        before[tab[j]]--;
    }
    cout << "TABSORTED 0" << before[0] << endl;
    cout << "\n\n";
    for (int i = 0; i < l; i++) {
        cout << tabSorted[i] << ", ";
    }
    cout << endl;

}