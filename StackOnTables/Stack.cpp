#include<iostream>

using namespace std;

int top = 0;
int Stack[10];

bool StackEmpty(int Stack[]) {
    if (top == 0)
        return true;
    else return false;
}

void Push(int Stack[], int x) {
    top++;
    Stack[top] = x;
}

int Pop(int Stack[]) {
    if (StackEmpty(Stack)) {
        cout << "Error. Stack is empty";
        return;
    }

    top--;
    return Stack[(top + 1)];
}

int main() {
    return 0;
}