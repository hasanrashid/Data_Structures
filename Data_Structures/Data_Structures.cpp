#include "stdafx.h"
#include "Stack.h"
#include "Queue.h"
using namespace std;




int main()
{
	Node<int>n = Node<int>(1);
	Node<char>n1 = Node<char>('a');
	Stack<int> s;
	s.Push(21);
	s.Push(22);
	s.Push(23);
	s.Push(24);
	s.Push(25);
	s.PrintStack();
	s.Pop();
	s.PrintStack();
	s.Pop();
	s.PrintStack();
	s.Push(26);
	s.PrintStack();
	s.Pop();
	s.PrintStack();

	Queue<char> q;

	q.Enqueue('c');
	q.Enqueue('d');
	q.Enqueue('e');
	q.Enqueue('f');
	q.Enqueue('g');
	q.Enqueue('h');
	q.PrintQueue();
	cout << q.Dequeue() << endl;
	q.PrintQueue();
	return 0;
}
