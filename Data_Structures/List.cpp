
#include "stdafx.h"
#include "List.h"
using namespace std;

namespace DataStructures {

	template <class T> Node<T>::Node() {
	}
	template <class T> Node<T>::Node(T nv) : nodeValue(nv) {

	}
	template <class T> const T Node<T>::getValue() const {
		return nodeValue;
	}
	template <class T> void Node<T>::setValue(T nv) {
		this->nodeValue = nv;
	}

	template <class T> void Node<T>::setNext(Node *next) {
		this->next = next;
	}
	template <class T> Node<T>* Node<T>::getNext() const {
		return next;
	}
	template <class T> void Node<T>::setPrev(Node<T> *prev) {
		this->prev = prev;
	}
	template <class T> Node<T>* Node<T>::getPrev() const {
		return prev;
	}

	ListException::ListException(const char* m) : message(m) {}
	const char* ListException::what() const throw() {
		return message;
	}

	template <class T> List<T>::List() : startNode(NULL), count(0) {
	}

	template <class T> List<T>::~List() {
		Delete();
	}

	template <class T> void List<T>::Delete() {
		Node<T> *n = startNode;
		for (int i = 0; i < count; i++) {
			startNode = startNode->getNext();
			delete n;
			n = startNode;
		}
		std::cout << "Memory has been cleared\n";
	}
	template <class T> int List<T>::InsertAt(T element, int position) {
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

	template <class T> int List<T>::InsertAfter(T element, int before = 0) {
		Node<T> *n = new Node<T>(element);
		int retCode = 0;
		try {
			if (startNode == NULL) { //When the list is empty
				startNode = n;
				startNode->setNext(startNode);
				startNode->setPrev(startNode);
			}
			else {
				n->setNext(startNode);
				n->setPrev(startNode->getPrev());
				n->getPrev()->setNext(n);
				startNode->setPrev(n);
				startNode = before ? n : startNode;
			}
			count++;
		}
		catch (std::exception &e) {
			retCode = 1;
			std::cout << e.what() << std::endl;
		}
		return retCode;
	}

	template <class T> int List<T>::InsertBefore(T element) {
		int retCode = 0;
		try {
			retCode = InsertAfter(element, 1);
		}
		catch (std::exception &e) {
			retCode = 1;
		}
		return retCode;
	}

	template <class T> Node<T>* List<T>::ElementAt(int position) {
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
	template <class T> int List<T>::UpdateAt(T value, int position) {
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

	template<class T> T DataStructures::List<T>::RemoveAt(int position) {
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



	template <class T> std::string List<T>::ToString() {
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

	template <class T> void List<T>::Print() {
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
}