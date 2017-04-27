#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;
template <class T> class Node {
	T nodeValue;
	Node *next;
	Node *prev;
public:
	Node() {
	}
	Node(T nv) {
		this->nodeValue = nv;
	}
	const T getValue() const{
		return nodeValue;
	}
	void setValue(T nv) {
		this->nodeValue = nv;
	}

	void setNext(Node *next) {
		this->next = next;
	}
	Node* getNext() {
		return next;
	}
	void setPrev(Node *prev) {
		this->prev = prev;
	}
	Node* getPrev() const{
		return prev;
	}

};
class ListException : public exception {
	const char* message;
	public:
		ListException(const char* m) {
			this->message = m;
		};
		const char* what() const throw() {
			return message;
		}
};

template <class T> class List {

	template <class T> friend class Stack;
	template <class T> friend class Queue;

	Node<T> *startNode;
	int count;
	void Delete() {
		Node<T> *n = startNode;
		for (int i = 0; i < count; i++) {
			startNode = startNode->getNext();
			delete n;
			n = startNode;
		}
		cout << "Memory has been cleared\n";
	}

	void InsertAt(T element, int position) {
		try {
			if (position <= count) {
				Node<T> *newNode = new Node<T>(element);
				Node<T> *n = startNode;
				if (position < count / 2) {
					for (int i = 0; i < position - 1; i++) {
						n = n->getNext();
					}
				}
				else {
					for (int i = 0; i <= count - position; i++) {
						n = n->getPrev();
					}
				}
				newNode->setNext(n);
				n->getPrev()->setNext(newNode);
				newNode->setPrev(n->getPrev());
				n->setPrev(newNode);
				count++;
			}
			else {
				throw ListException("position is out of bounds");
			}
		}
		catch (ListException &e) {
			cout << e.what() << endl;
		}

	}

	void InsertAfter(T element) {
		Node<T> *n = new Node<T>(element);
		if (startNode == NULL) { //When the list is empty
			startNode = n;
			startNode->setNext(startNode);
			startNode->setPrev(startNode);
		}
		else {
			n->setPrev(startNode->getPrev());
			startNode->setPrev(n);
			n->getPrev()->setNext(n);
			n->setNext(startNode);
		}
		count++;
	}

	void InsertBefore(T element) {
		Node<T> *n = new Node<T>(element);
		if (startNode == NULL) { //When the list is empty
			startNode = n;
			startNode->setNext(startNode);
			startNode->setPrev(startNode);
		}
		else {	//When the list has one or more element
			n->setNext(startNode);				//The new node is going before the startNode
			n->setPrev(startNode->getPrev());	//and it will point the previous node of startNode to maintai circularity
			startNode->setPrev(n);	//The current startNode will become the second node, so its previous has to point to the new node
			startNode = n;	//Finally, the new node becomes the startNode
		}
		count++;
	}

	T RemoveAt(int position) {
		Node<T> *n = startNode;
		T value = NULL;
		try {
			if (position <= count) {
				for (int i = 1; i < position; i++) {
					n = n->getNext();
				}
				n->getNext()->setPrev(n->getPrev());
				n->getPrev()->setNext(n->getNext());
				value = n->getValue();
				if(position == 1)
					startNode = startNode->getNext();
				delete n;
				count--;
			}
			else {
				throw ListException("Position is out of bounds");
			}
		}
		catch (ListException& e) {
			cout << e.what() << endl;
		}
		return value;
	}

	void Print() {
		Node<T> *n = startNode;
		cout << "Position: ";
		for (int i = 1; i <= count; i++) {
			cout << setw(3) << right << i << ' ';
		}
		cout << '\n' << "   Value: ";
		for (int i = 1; i <= count; i++) {
			cout << setw(3) << right << n->getValue() << ' ';
			n = n->getNext();
		}
		cout << '\n';
	}

public:
	List() {
		startNode = NULL;
		count = 0;
	}
	~List() {
		Delete();
	}

};

template <class T> class Stack{
	List<T> l;
public:
	Stack() {
	}
	
	void Push(T element) {
		l.InsertAfter(element);
	}
	T Pop() {
		return l.RemoveAt(l.count);
	}
	int PrintStack() {
		HANDLE hStdout;
		CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
		COORD coordDest;

		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

		if (hStdout == INVALID_HANDLE_VALUE)
		{
			printf("GetStdHandle failed with %d\n", GetLastError());
			return NULL;
		}

		// Get the screen buffer size. 

		if (!GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
		{
			printf("GetConsoleScreenBufferInfo failed %d\n", GetLastError());
			return NULL;
		}

		Node<T> *n = l.startNode;
		if (hStdout == NULL) {
			return 1;
		}

		cout << "Position: " << endl;

		int height = csbiInfo.dwCursorPosition.Y;
		for (int i = 1; i <= l.count; i++) {
			cout << setw(3) << right << i << endl;
			csbiInfo.dwCursorPosition.Y = height+i+1;
			SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition);
		}
		csbiInfo.dwCursorPosition.X = 11;
		csbiInfo.dwCursorPosition.Y = csbiInfo.dwCursorPosition.Y - l.count-1;
		SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition);
		cout << "Value: " << endl;

		height = csbiInfo.dwCursorPosition.Y;

		for (int i = 1; i <= l.count; i++) {			
			n = n->getPrev();
			csbiInfo.dwCursorPosition.X = 11;
			csbiInfo.dwCursorPosition.Y = i+height;
			SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition);
			cout << setw(3) << right << n->getValue() << endl;
		}
		cout << '\n';

		return 0;
	}
};

template <class T> class Queue {
	List<T> l;

public:
	Queue() {
	
	}
	void Enqueue(T element) {
		l.InsertAfter(element);
	}
	T Dequeue() {
		return l.RemoveAt(1);
	}
	void PrintQueue() {
		l.Print();
	}
};

HANDLE setPosition(CONSOLE_SCREEN_BUFFER_INFO *csbiInfo) {
	
	HANDLE hStdout;
	SMALL_RECT srctScrollRect, srctClipRect;
	CHAR_INFO chiFill;
	COORD coordDest;


	return hStdout;
}

int main()
{
	Node<int>n = Node<int>(1);
	Node<char>n1 = Node<char>('a');
	Stack<int> s;
	s.Push(21);
	s.Push(22);
	s.Push(23);
	s.Push(24);
	s.Push(25);
	s.PrintStack();
	s.Pop();
	s.PrintStack();
	s.Pop();
	s.PrintStack();
	s.Push(26);
	s.PrintStack();
	s.Pop();
	s.PrintStack();

/*	Queue<char> q;

	q.Enqueue('c');
	q.Enqueue('d');
	q.Enqueue('e');
	q.Enqueue('f');
	q.Enqueue('g');
	q.Enqueue('h');
	q.PrintQueue();
	cout << q.Dequeue() << endl;
	q.PrintQueue();*/
	return 0;
}
