#include<iostream>

using namespace std;

int tab[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

void Insertion_Sort(int tab[], int n);

int main() {
    Insertion_Sort(tab, 9);
    for (int i = 0; i <= 9; i++)
        cout << tab[i] << ", ";

    int c;
    cin >> c;
    return 0;
}

void Insertion_Sort(int tab[], int n) {
    for (int i = 1; i <= n; i++) {
        int key = tab[i];
        int j = i - 1;
        while (j >= 0 && tab[j] > key) {
            tab[j + 1] = tab[j];
            j--;
        }
        tab[j + 1] = key;
    }

}