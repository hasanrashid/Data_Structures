#pragma once
#include <exception>
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>

#define LIST_API __declspec(dllexport)

namespace DataStructures {
	template <class T> class Node {
		T nodeValue;
		Node *next;
		Node *prev;
	public:
		Node();
		Node(T nv);
		const T getValue() const;
		void setValue(T nv);

		void setNext(Node *next);
		Node* getNext() const;
		void setPrev(Node *prev);
		Node* getPrev() const;

	};
	class ListException : public std::exception {
		const char* message;

	public:
		ListException(const char* m);
		const char* what() const throw();
	};
	template <class T> class LIST_API List {

		Node<T> *startNode;
		int count;

		template <class T> friend class Stack;
		template <class T> friend class Queue;
		template <class T> friend class Tree;
		friend class ListTest;

		void Delete();
		int InsertAt(T element, int position);
		int InsertAfter(T element, int before = 0);
		int InsertBefore(T element);
		Node<T>* ElementAt(int position);
		int UpdateAt(T value, int position);
		T RemoveAt(int position);
		std::string ToString();
		void Print();

	public:
		List();
		~List();
	};
}
