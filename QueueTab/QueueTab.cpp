#include<iostream>
using namespace std;



struct Queue
{
	int key;
	Queue * next = NULL;
};

bool Empty(Queue **Head)
{
	if (*Head == NULL)
	{
		cout << "Kolejka pusta\n\n";
		return 1;
	}
	else return 0;

}



void enqueue(Queue **Tail, Queue **Head, int k)
{
	Queue *Nowy = new Queue;
	if(*Tail != NULL)
		(*Tail)->next = Nowy;
	Nowy->key = k;
	Nowy->next = NULL;
	if (*Head == NULL)
		*Head = *Tail =  Nowy;
	else
		*Tail = Nowy;

	Queue *Temp = *Head;
	while (Temp != NULL)
	{
		cout << Temp->key << ", ";
		if (Temp == *Tail)
		{
			Temp = NULL;
		}
		else
		Temp = Temp->next;

	}
	cout << endl;
	delete Temp;
}

void dequeue(Queue ** Tail, Queue ** Head)
{
	if (*Head != NULL)
	{
		cout << "Usunieto element " << (*Head)->key << endl;
		if (*Head == *Tail)
			*Head = *Tail = NULL;
		else 
			*Head = (*Head)->next;
	
	}
	else cout << "Kolejka jest pusta." << endl;
}

int main()
{
	Queue *Tail = NULL;
	Queue *Head = NULL;
	char var;

	cout << " a - dodaj elemnt i wyswietl, d- usun element, q - zakoncz" << endl;
	int k;
	while (cin >> var)
	{
		switch(var)
		{
		case 'a':
			cout << "Podaj wartosc:  ";
			cin >> k;

			enqueue(&Tail, &Head, k);
			break;

		case 'd':
			dequeue(&Tail, &Head);
			break;
		case 'q':
			return 0;
		}

	}


}