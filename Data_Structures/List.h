#pragma once
#include <exception>
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>

namespace DataStructures {
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
		Node* getNext() const{
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
		friend class ListTest;

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
		int InsertAt(T element, int position) {
			int retCode = 0;
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
				retCode = 1;
				std::cout << e.what() << std::endl;
			}
			return retCode;
		}
/*		int Insert(Node<T>* (Node<T>::*get) () const, void (Node<T>::*set)(Node<T> *), Node<T> *stNode, Node<T> *newNode) {
			//Node<T> *n = new Node<T>(e);
			int retCode = 0;
			try {
				retCode = ((stNode->*get)())->getValue();
				(newNode->set(stNode->get()));
				stNode->set(n);
				(newNode->get())->set(n);
				newNode->set(stNode);

				n->setPrev(startNode->getPrev());
				startNode->setPrev(n);
				n->getPrev()->setNext(n);
				n->setNext(startNode);
			}
			catch(std::exception &e){
				
				retCode = 1;
			}
			return retCode;
		}*/
		int InsertAfter(T element, int before=0) {
			Node<T> *n = new Node<T>(element);
			int retCode = 0;
			try {
				if (startNode == NULL) { //When the list is empty
					startNode = n;
					startNode->setNext(startNode);
					startNode->setPrev(startNode);
				}
				else {
					//typedef void (Node<T>::*f) ();
					//f = &Node<T>::getPrev;
					//int x = Insert(&Node<T>::getPrev, &Node<T>::setNext, startNode,n);
					n->setNext(startNode);
					n->setPrev(startNode->getPrev());
					n->getPrev()->setNext(n);
					startNode->setPrev(n);
					startNode = before ? n : startNode;
/*					n->setNext(startNode);				//The new node is going before the startNode
					n->setPrev(startNode->getPrev());	//and it will point the previous node of startNode to maintai circularity
					startNode->setPrev(n);	//The current startNode will become the second node, so its previous has to point to the new node
					startNode = n;	//Finally, the new node becomes the startNode*/
				}
				count++;
			}
			catch (std::exception &e) {
				retCode = 1;
				std::cout << e.what() << std::endl;
			}
			Print();
			return retCode;
		}

		int InsertBefore(T element) {
/*			Node<T> *n = new Node<T>(element);
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
			count++;*/
			int retCode = 0;
			try {
				retCode = InsertAfter(element, 1);
			}
			catch (std::exception &e) {
				retCode = 1;
			}
			return retCode;
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
				n = NULL;
				std::cout << e.what() << std::endl;
			}
			return n;
		}
		int UpdateAt(T value, int position) {
			Node<T> *n = ElementAt(position);
			int retCode = 0;
			if (n != NULL) {
				n->setValue(value);
			}
			else {
				retCode = 1;
			}
			return retCode;
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

		std::string ToString() {
			std::string retVal = "";
			Node<T> *n = startNode;
			try {
				for (int i = 0; i < count; i++) {
					retVal = retVal + std::to_string(n->getValue());
					n = n->getNext();
				}
			}
			catch (std::exception e) {
				retVal = "";
			}
			return retVal;
		}
		
		void Print() {
			Node<T> *n = startNode;
			std::cout << "Position: ";
			for (int i = 1; i <= count; i++) {
				std::cout << std::setw(3) << std::right << i << ' ';
			}
			std::cout << '\n' << "   Value: ";
			for (int i = 1; i <= count; i++) {
				std::cout << std::setw(3) << std::right << n->getValue() << ' ';
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


}
