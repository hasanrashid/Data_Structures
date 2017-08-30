#pragma once

#include "List.h"

#include <iostream>
#include <iomanip>
#include <windows.h>

namespace DataStructures {

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
}
