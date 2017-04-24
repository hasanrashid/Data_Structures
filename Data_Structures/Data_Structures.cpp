#include "stdafx.h"
#include <iostream>
#include <iomanip>
using namespace std;
template <class T>
class Node {
	T nodeValue;
	Node *next;
	Node *prev;
public:
	Node() {
	}
	Node(T nv) {
		this->nodeValue = nv;
	}
	T getValue() {
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
	Node* getPrev() {
		return prev;
	}

};
template <class T>
class List {
	Node<T> *startNode;
	int count;
public:
	List() {
		startNode = NULL;
		count = 0;
	}

	void InsertAt(T element, int position) {
		if (position > count) { //
			cout << "Out of bound";
		}
		else {
			Node<T> *newNode = new Node<T>(element);
			Node<T> *n = startNode;
			for (int i = 0; i < position - 1; i++) {
				n = n->getNext();
			}
			newNode->setNext(n);
			n->getPrev()->setNext(newNode);
			newNode->setPrev(n->getPrev());
			n->setPrev(newNode);
			count++;
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

	void RemoveAt(int position) {
		if (position > count)
			cout << "Out of bounds";
		else {
			Node<T> *n = startNode;
			for (int i = 0; i < position - 1; i++) {
				n = n->getNext();
			}
			n->getNext()->setPrev(n->getPrev());
			n->getPrev()->setNext(n->getNext());
			delete n;
			count--;
		}
	}
	void Delete() {
		Node<T> *n = startNode;
		for (int i = 0; i < count; i++) {
			startNode = startNode->getNext();
			delete n;
			n = startNode;
		}
	}

	void Print() {
		Node<T> *n = startNode;
		cout << "Position: ";
		for (int i = 1; i <= count; i++) {
			cout << setw(3) << right << i << ' ';
		}
		cout << '\n' << "   Value: ";
		for (int i = 0; i < count; i++) {
			cout << setw(3) << right << n->getValue() << ' ';
			n = n->getNext();
		}
		cout << '\n';
	}

};

int main()
{
	Node<int>n = Node<int>(1);
	Node<char>n1 = Node<char>('a');
	List<int> l;
	l.InsertAfter(2);
	l.InsertAfter(4);
	l.InsertAfter(6);
	l.InsertAfter(8);
	l.InsertAfter(9);
	l.InsertAt(10, 3);
	l.RemoveAt(3);
	l.Print();
	l.Delete();
	return 0;
}
