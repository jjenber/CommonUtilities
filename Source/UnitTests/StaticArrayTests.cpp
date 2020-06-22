#include "pch.h"
#include "CppUnitTest.h"
#include <Collections/StaticArray.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CommonUtilities;

namespace StaticArrays
{
	TEST_CLASS(Constructors)
	{
	public:
		TEST_METHOD(Assignment)
		{
			StaticArray<int, 3> anArray;
			anArray[0] = 2;
			anArray[1] = 4;
			anArray[2] = 6;

			StaticArray<int, 3> aCopy{ anArray };
			Assert::AreEqual(anArray[0], aCopy[0]);
			Assert::AreEqual(anArray[1], aCopy[1]);
			Assert::AreEqual(anArray[2], aCopy[2]);

			Assert::AreNotEqual(anArray[1], aCopy[2]);
		}
		TEST_METHOD(InitializerList)
		{
			StaticArray<int, 3> arr{ 4, 8, 16 };
			Assert::AreEqual(4, arr[0]);
			Assert::AreEqual(8, arr[1]);
			Assert::AreEqual(16, arr[2]);
		}

		TEST_METHOD(InitializerListFill)
		{
			StaticArray<int, 3> arr{ 4 };

			Assert::AreEqual(4, arr[0]);
			Assert::AreEqual(4, arr[1]);
			Assert::AreEqual(4, arr[2]);
		}
	};

	TEST_CLASS(SubscriptOperator)
	{
	public:
		TEST_METHOD(InsideOfRange)
		{
			StaticArray<int, 3> anArray;
			anArray[0] = 2;
			anArray[1] = 4;
			anArray[2] = 6;

			Assert::AreEqual(2, anArray[0]);
			Assert::AreEqual(4, anArray[1]);
			Assert::AreEqual(6, anArray[2]);
			Assert::AreNotEqual(2, anArray[1]);
		}
	};

	TEST_CLASS(Insert)
	{
	public:
		TEST_METHOD(InsertAtZero)
		{
			StaticArray<int, 3> anArray;
			anArray[0] = 2;
			anArray[1] = 4;
			anArray[2] = 6;

			anArray.Insert(0, 5);
			Assert::AreEqual(5, anArray[0]);
			Assert::AreEqual(2, anArray[1]);
			Assert::AreEqual(4, anArray[2]);
		}
		TEST_METHOD(InsertAtMiddle)
		{
			StaticArray<int, 3> anArray;
			anArray[0] = 2;
			anArray[1] = 4;
			anArray[2] = 6;

			anArray.Insert(1, 5);
			Assert::AreEqual(2, anArray[0]);
			Assert::AreEqual(5, anArray[1]);
			Assert::AreEqual(4, anArray[2]);
		}
		TEST_METHOD(InsertLast)
		{
			StaticArray<int, 3> anArray;
			anArray[0] = 2;
			anArray[1] = 4;
			anArray[2] = 6;

			anArray.Insert(2, 5);
			Assert::AreEqual(2, anArray[0]);
			Assert::AreEqual(4, anArray[1]);
			Assert::AreEqual(5, anArray[2]);

			Assert::AreNotEqual(6, anArray[2]);
		}
	};
}