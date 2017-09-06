#include "stdafx.h"
#include "CppUnitTest.h"
#include "x64\List.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DataStructures
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
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

	};
}