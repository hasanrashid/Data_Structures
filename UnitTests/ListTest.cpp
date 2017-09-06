#include "stdafx.h"
#include "CppUnitTest.h"
#include "List.h"	//Add location of project headers to the list of include directories
#include <string>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DataStructures
{		
	TEST_CLASS(ListTest)
	{
	public:
		
		List<int> l;
		TEST_CLASS_INITIALIZE(InitializeListTest)
		{
		}
		TEST_METHOD(Circularity)
		{
			l.InsertAfter(1);
			l.InsertAfter(2);
			l.InsertBefore(8);
			l.InsertAfter(3);
			l.InsertBefore(7);
			std::string message = "Passed";
			Node<int> n1 = *l.ElementAt(5);
//			Assert::AreEqual(l.ElementAt(5), (l.ElementAt(5)->getPrev()),L"Passed");
			//Assert::AreEqual(l.ElementAt(5), l.ElementAt(1), L"Passed");

		}
		TEST_METHOD(ElementAt)
		{
			l.InsertAfter(1);
			l.InsertAfter(2);
			l.InsertBefore(8);
			l.InsertAfter(3);
			l.InsertBefore(7);
			Assert::AreEqual(7, l.ElementAt(1)->getValue(), L"Passed");
			Assert::AreEqual(7, l.ElementAt(1)->getValue(), L"Passed");

		}
		TEST_METHOD(InsertBefore)
		{
			l.InsertBefore(1);
			l.InsertBefore(2);
			std::string h = "21";
			Assert::IsTrue(h==l.ToString(), L"Passed");
		}
		TEST_METHOD(InsertAfter)
		{
			l.InsertAfter(7);
			l.InsertAfter(8);
			std::string h = "78";
			Assert::IsTrue(h == l.ToString(), L"Passed");
		}
		TEST_CLASS_CLEANUP(CleanUp)
		{
			
		}
	};
}