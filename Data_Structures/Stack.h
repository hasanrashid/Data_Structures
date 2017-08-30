#pragma once
#include "List.h"

#include <iostream>
#include <iomanip>
#include <windows.h>

namespace DataStructures {
	template <class T> class Stack {
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
				std::cout << "GetStdHandle failed with " << GetLastError();
				return NULL;
			}

			// Get the screen buffer size. 

			if (!GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
			{
				std::cout << "GetConsoleScreenBufferInfo failed " << GetLastError();
				return NULL;
			}

			Node<T> *n = l.startNode;
			if (hStdout == NULL) {
				return 1;
			}

			std::cout << "Position: " << endl;

			int height = csbiInfo.dwCursorPosition.Y;
			for (int i = 1; i <= l.count; i++) {
				cout << setw(3) << right << i << endl;
				csbiInfo.dwCursorPosition.Y = height + i + 1;
				SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition);
			}
			csbiInfo.dwCursorPosition.X = 11;
			csbiInfo.dwCursorPosition.Y = csbiInfo.dwCursorPosition.Y - l.count - 1;
			SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition);
			std::cout << "Value: " << endl;

			height = csbiInfo.dwCursorPosition.Y;

			for (int i = 1; i <= l.count; i++) {
				n = n->getPrev();
				csbiInfo.dwCursorPosition.X = 11;
				csbiInfo.dwCursorPosition.Y = i + height;
				SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition);
				std::cout << setw(3) << right << n->getValue() << endl;
			}
			std::cout << '\n';

			return 0;
		}
	};

}
