#pragma once
#include <exception>

#include <iostream>
#include <iomanip>
#include <windows.h>

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
	const T getValue() const {
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
	Node* getPrev() const {
		return prev;
	}

};
class ListException : public std::exception {
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
	template <class T> friend class Tree;

	Node<T> *startNode;
	int count;
	void Delete() {
		Node<T> *n = startNode;
		for (int i = 0; i < count; i++) {
			startNode = startNode->getNext();
			delete n;
			n = startNode;
		}
		std::cout << "Memory has been cleared\n";
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
			std::cout << e.what() << endl;
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
	
	Node<T>* ElementAt(int position) {
		Node<T> *n = startNode;
		try {
			if (position <= count) {
				for (int i = 1; i < position; i++) {
					n = n->getNext();
				}
			}
			else {
				throw ListException("Position is out of bounds");
			}
		}
		catch (ListException& e) {
			std::cout << e.what() << endl;
		}
		return n;
	}
	void UpdateAt(T value, int position) {
		Node<T> *n = ElementAt(position);
		if (n != NULL) {
			n->setValue(value);
		}
	}
	T RemoveAt(int position) {
		Node<T> *n = ElementAt(position);
		T value = NULL;
		if (n != NULL) {
			value = n->getValue();
			n->getNext()->setPrev(n->getPrev());
			n->getPrev()->setNext(n->getNext());
			if (position == 1)
				startNode = startNode->getNext();
			delete n;
			count--;
		}
		return value;
	}

	void Print() {
		Node<T> *n = startNode;
		std::cout << "Position: ";
		for (int i = 1; i <= count; i++) {
			std::cout << setw(3) << right << i << ' ';
		}
		std::cout << '\n' << "   Value: ";
		for (int i = 1; i <= count; i++) {
			cout << setw(3) << right << n->getValue() << ' ';
			n = n->getNext();
		}
		std::cout << '\n';
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