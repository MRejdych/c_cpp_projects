#include<iostream>

using namespace std;

struct Stack {
    int key;
    Stack *next = NULL;
};


bool StackEmpty(Stack **top) {
    if (*top == NULL)
        return 1;
    else
        return 0;
}

void Push(Stack **top, int k) {
    Stack *nowa = new Stack;
    nowa->key = k;
    nowa->next = *top;
    *top = nowa;


    Stack *pTop = *top;
    while (pTop != NULL) {
        cout << pTop->key << ", ";
        pTop = pTop->next;
    }

}

void Pop(Stack **top) {
    if (StackEmpty(top)) {
        cout << "Error: stack is empty";
    } else {
        cout << "First record was deleted from stack" << endl;
        Stack *temp = *top;
        *top = (*top)->next;
    }

}


int main() {
    Stack *top = NULL, *next = NULL;
    char var;
    int k;
    cout << "a - add new record, d - pop record, q- quit program" << endl;;
    while (cin >> var) {
        switch (var) {
            case 'a':
                cout << "\nPodaj klucz:  ";
                cin >> k;;
                cout << endl;
                Push(&top, k);
                break;
            case 'd':
                Pop(&top);
                break;
            case 'q':
                return 0;
        }
    }


    return 0;
}