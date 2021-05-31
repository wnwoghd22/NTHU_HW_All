#include <iostream>
#include <string>
using namespace std;

class LinkedList;

class ListNode {
	friend class LinkedList;
public:
	ListNode(int a = 0)
	{
		data = a;
		next = NULL;
		pre = NULL;
	}
	int getData() { return data; }
private:
	int data;
	ListNode *next;
	ListNode *pre;
};

class LinkedList {
public:
	LinkedList() { first = last = 0; }
	void InsertFront(int);
	void InsertBack(int);
	void InsertBefore(int, int);
	void InsertAfter(int, int);
	void DeleteFront();
	void DeleteBack();
	void Delete(int);
	void Reverse(int, int); //if pos2>pos1 cannot reverse.
	void Clear();
	void Print()
	{
		ListNode* temp = first;
		
		while (temp != 0)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}
private:
	ListNode* getNode(int); //search and return the node that we are looking for.  If returns 0 then there is not node in the list.
	ListNode* getFirst() { return first; }
	bool isAfter(int, ListNode*);
	ListNode *first, *last; //It will help us to insertFront and insertLast.
};

void LinkedList::InsertFront(int d)
{
	if (first)
	{
		ListNode* temp = new ListNode(d);
		first->pre = temp; temp->next = first;
		first = temp;
	}
	else
		last = first = new ListNode(d);
}
void LinkedList::InsertBack(int d)
{
	if (last)
	{
		ListNode* temp = new ListNode(d);
		last->next = temp; temp->pre = last;
		last = temp;
	}
	else
		last = first = new ListNode(d);
}
void LinkedList::InsertBefore(int c, int d) //d is the new value
{
	ListNode *aux = getNode(c);
	if (aux)
	{
		if (aux == first)
			InsertFront(d);
		else
		{
			ListNode* temp = new ListNode(d);
			aux->pre->next = temp; temp->pre = aux->pre;
			aux->pre = temp; temp->next = aux;
		}
	}
}
void LinkedList::InsertAfter(int c, int d) //d is the new value
{
	ListNode *aux = getNode(c);
	if (aux != 0) {
		if (aux == last)
			InsertBack(d);
		else
		{
			ListNode* temp = new ListNode(d);
			aux->next->pre = temp; temp->next = aux->next;
			aux->next = temp; temp->pre = aux;
		}
	}
}

void LinkedList::DeleteFront()
{
	if (first)
	{
		ListNode* aux = first;
		if (first->next)
		{
			first = first->next;
			first->pre = NULL;
		}
		else
			first = last = 0;
		delete aux;
	}
}
void LinkedList::DeleteBack()
{
	if (last)
	{
		ListNode* aux = last;
		if (last->pre)
		{
			last = last->pre;
			last->next = NULL;
		}
		else
			first = last = 0;
		delete aux;
	}
}
void LinkedList::Delete(int f)
{
	if (!first) return;
	else
	{
		if (first->data == f)
			DeleteFront();
		else if (last->data == f)
			DeleteBack();
		else
		{
			ListNode* temp = getNode(f);
			if (!temp) return;
			temp->pre->next = temp->next;
			temp->next->pre = temp->pre;
			delete temp;
		}
	}
}
void LinkedList::Clear() {
	ListNode *aux = first;
	ListNode *temp = 0;
	while (aux != 0) {
		temp = aux;
		aux = aux->next;
		delete temp;
	}
	first = last = 0;
}

ListNode* LinkedList::getNode(int d)
{
	if (first) {
		ListNode *ax = first;
		while (ax != last) {
			if (ax->data == d)
				return ax;
			ax = ax->next;
		}
		if (ax->data == d) {
			return last;
		}
	}
	return 0; //no found
}
bool LinkedList::isAfter(int b, ListNode *a) {
	if (a != 0) {
		ListNode* temp = a->next;
		if (!temp) return false;
		if (b == temp->data) return true;
		else return isAfter(b, temp);
	}
	else {
		return false;
	}
}
void LinkedList::Reverse(int a, int b)
{
	ListNode* fre = getNode(a);
	if (isAfter(b, fre))
	{
		ListNode* fin = getNode(b);
		ListNode* tempFre = fre;
		ListNode* temp = NULL; ListNode* temp2 = NULL;
		ListNode* Pre = NULL; ListNode* Next = NULL;
		if (fre != first)
			Pre = fre->pre;
		if (fin != last)
			Next = fin->next;

		while (temp != fin)
		{
			temp2 = tempFre->next;
			tempFre->next = temp;
			if(temp)
				temp->pre = tempFre;
			temp = tempFre;
			if(temp2)
				tempFre = temp2;
		}

		if (fre == first)
			first = temp;
		else
		{
			Pre->next = temp;
			temp->pre = Pre;
		}
		if (fin == last)
			last = fre;
		else
		{
			Next->pre = fre;
			fre->next = Next;
		}
	}
}

int main()
{
	LinkedList li;
	int d, e;
	string inp;
	while (cin >> inp) {
		if (inp == "InsertFront") {
			cin >> d;
			li.InsertFront(d);
		}
		else if (inp == "InsertBack") {
			cin >> d;
			li.InsertBack(d);
		}
		else if (inp == "InsertBefore") {
			cin >> d >> e;
			li.InsertBefore(d, e);
		}
		else if (inp == "InsertAfter") {
			cin >> d >> e;
			li.InsertAfter(d, e);
		}
		else if (inp == "DeleteFront") {
			li.DeleteFront();
		}
		else if (inp == "DeleteBack") {
			li.DeleteBack();
		}
		else if (inp == "Delete") {
			cin >> d;
			li.Delete(d);
		}
		else if (inp == "Reverse") {
			cin >> d >> e;
			li.Reverse(d, e);
		}
		else if (inp == "Clear") {
			li.Clear();
		}
		else if (inp == "Print") {
			li.Print();
		}
		else {
			continue;
		}
	}
	return 0;
}
