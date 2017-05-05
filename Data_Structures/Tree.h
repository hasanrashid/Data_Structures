#pragma once
#include "List.h"

#include <iostream>
#include <iomanip>
#include <windows.h>

template <class T> class Element {

	T elementValue;
	Element *parent;
	Element *left;
	Element *right;
	Element *sibling;

public:

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

	List l;

public:

	void InOrder(Element *e) {

		if (e != NULL) {
			InOrder(e->getLeft());
			std::cout << e->getValue() << endl;
			InOrder(e->getRight());
		}
	
	}

	void Insert(T value) {
		Element *e;
		while (e != NULL) {
			while (e->getValue() <= value && e->getLeft() != NULL) {
				e = e->getLeft();
			}
			while (e->getValue() > value && e->getRight() != NULL) {
				e = e->getRight();
			}
		}
	}
};