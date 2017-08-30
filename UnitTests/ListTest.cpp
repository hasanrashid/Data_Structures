#include "stdafx.h"
#include "CppUnitTest.h"
#include "List.h"	//Add location of project headers to the list of include directories
#include <string>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DataStructures
{		
	TEST_CLASS(ListTest)
	{
		 List<int> l;
	public:
		
		TEST_CLASS_INITIALIZE(InitializeListTest)
		{

		}
		TEST_METHOD(InsertBefore)
		{
			l.InsertBefore(1);
			l.InsertBefore(2);
			l.InsertBefore(3);
			std::string h = "321";
			Assert::IsTrue(h==l.ToString(), L"Passed");
		}
		TEST_METHOD(InsertAfter)
		{
			l.InsertAfter(1);
			l.InsertAfter(2);
			l.InsertBefore(3);
			std::string h = "312";
			Assert::IsTrue(h == l.ToString(), L"Passed");
		}
		TEST_CLASS_CLEANUP(CleanUp)
		{
			
		}
	};
}