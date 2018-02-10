#include<iostream>

using namespace std;

int intsTable[10] = {1, 5, 9, 11, 13, 17, 19, 21, 24, 28};

int BinarySearch(int tab[], int p, int n, int x);


int main() {
    int x;
    cout << "Enter number which you are looking for." << endl;
    cin >> x;
    int index = BinarySearch(intsTable, 0, 9, x);
    if (index != -1)
        cout << "Number is located in the table under index:  " << index << endl;
    int c;
    cout << "Write any character and hit enter to terminate process." << endl;
    cin >> c;
    return 0;
}

int BinarySearch(int tab[], int p, int n, int x) {
    if (p <= n) {
        int q = (p + n) / 2;
        if (tab[q] == x) {
            return q;
        } else if (tab[q] > x) {
            BinarySearch(tab, p, q - 1, x);
        } else {
            BinarySearch(tab, q + 1, n, x);
        }
    } else
        cout << "Number was not found." << endl;
    return -1;
}

