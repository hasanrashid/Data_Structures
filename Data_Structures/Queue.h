#pragma once

#include "List.h"

#include <iostream>
#include <iomanip>
#include <windows.h>

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
