#include<iostream>
using namespace std;


struct List {
	List *prev = NULL;
	List *next = NULL;

	int key;
};

List *Search(List **head, int k)
{
	List *Temp = *head;

	while (Temp != NULL && k != Temp->key)
	{
		Temp = Temp->next;
	}

	if (Temp != NULL)
	{
		cout << "Znaleziono wartosc." << endl;
		return Temp;
	}

	else
		cout << "Nie znaleziono szukanej wartosci." << endl;
	return NULL;
}

void Delete(List **head, List **tail, int k)
{	
	List *Temp;
	while ((Temp = Search(head, k)) != NULL)
	{
		if (Temp->prev != NULL)
			Temp->prev->next = Temp->next;
		else
			*head = Temp->next;

		if (Temp->next != NULL)
			Temp->next->prev = Temp->prev;
		else
			*tail = Temp->prev;

		cout << "Usunieto wyznaczona wartosc z listy." << endl;

		
	}
	List *Tempp = *head;
	while (Tempp != NULL)
	{
		cout << Tempp->key << ", ";
		Tempp = Tempp->next;

	}
	cout << endl;
}

void Insert(List **head, List **tail, List *New)
{
	if (*head != NULL)
	{
		(*head)->prev = New;
		New->next = *head;
		if (*tail == NULL)
			*tail = New->next;
	}

	*head = New;

	List *Temp = *head;
	while (Temp != NULL)
	{
		cout << Temp->key << ", ";
		Temp = Temp->next;

	}
	cout << endl;
}

List *Create()
{
	List *New = new List;
	int c;
	cout << "Podaj wartosc klucza dla nowego elementu:\t";
	cin >> c;
	cout << endl;

	New->key = c;

	return New;
}

int main()
{
	List *head = NULL, *tail = NULL;
	char q;

	cout << " a - dodaj element, d - usun element, s - znajdz element, q -zakoncz" << endl;

	while (cin >> q)
	{
		
		switch (q)
		{
		case 'a':
			Insert(&head, &tail, Create());
			break;
		case 'd':
			int k;
			cout << "Podaj wartosc do usuniecia:\t";
			cin >> k;
			cout << endl;

			Delete(&head, &tail, k);
			break;
		case 's':
			cout << "Podaj wartosc do znalezienia:\t";
			int w;
			cin >> w;
			cout << endl;

			Search(&head, w);
			break;
		case 'q':
			return 0;

		}
		cout << " a - dodaj element, d - usun element, s - znajdz element, q -zakoncz" << endl;
	}

}