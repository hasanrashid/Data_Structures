#pragma once
#include "List.h"

#include <iostream>
#include <iomanip>
#include <windows.h>

namespace DataStructures {
	template <class T> class Element {

		T elementValue;
		Element *parent;
		Element *left;
		Element *right;
		Element *sibling;

	public:

		Element(T ev) {
			this->elementValue = ev;
			cout << "Creating a new Element " << elementValue << endl;
			left = NULL;
			right = NULL;
			parent = NULL;
			sibling = NULL;
		}
		~Element() {
			cout << "Removing element " << elementValue << endl;
		}
		const T getValue() {
			return elementValue;
		}

		void setValue(T ev) {
			this->elementValue = ev;
		}
		Element* getLeft() {
			return left;
		}
		void setLeft(Element *l) {
			this->left = l;
		}
		Element* getRight() {
			return right;
		}
		void setRight(Element *r) {
			this->right = r;
		}
		Element* getParent() {
			return parent;
		}
		void setParent(Element *p) {
			this->parent = p;
		}

		Element* getSibling() {
			return sibling;
		}
		void setSibling(Element *s) {
			this->sibling = s;
		}


	};

	template <class T> class Tree {

		List<T> l;
		Element<T> *root;
		int count;

	public:

		Tree(T value) {
			root = new Element<T>(value);
			count = 0;
		}

		~Tree() {
			delete root;
		}

		int getCount() {
			return count;
		}

		void setCount(int c) {
			count = c;
		}
		Element<T>* getRoot() {
			return this->root;
		}

		void setRoot(Element<T> r) {
			this->root = r;
		}

		void InOrder(Element<T> *e) {

			if (e != NULL) {
				InOrder(e->getLeft());
				std::cout << e->getValue() << endl;
				InOrder(e->getRight());
			}

		}

		void PrintTree(Element<T> r) {
			if (r->getLeft() != NULL) {
				PrintTree(r->getLeft());
			}
			else {
				cout << r->getValue() << ' ';
			}
		}

		void Insert(T value, Element<T> *subTree) {
			if (subTree->getValue() <= value) {
				if (subTree->getLeft() == NULL) {
					Element<T> *ne = new Element<T>(value);
					ne->setParent(subTree);
					subTree->setLeft(ne);
				}
				else {
					Insert(value, subTree->getLeft());
				}
			}
			else {
				if (subTree->getRight() == NULL) {
					Element<T> *ne = new Element<T>(value);
					ne->setParent(subTree);
					subTree->setRight(ne);
				}
				else {
					Insert(value, subTree->getRight());
				}
			}
		}
	};
}
