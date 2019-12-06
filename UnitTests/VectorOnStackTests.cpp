#include "pch.h"
#include "CppUnitTest.h"
#include "..//CommonUtilities/VectorOnStack.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CommonUtilities;

namespace VectorsOnStack
{
	TEST_CLASS(Constructors)
	{
	public:
		TEST_METHOD(Assignment)
		{
			VectorOnStack<int, 3, int> aVector;
			Assert::AreEqual(0, aVector.Size());

			aVector.Add(2);
			aVector.Add(4);
			aVector.Add(6);

			VectorOnStack<int, 3, int> aCopy = aVector;

			// Same size
			Assert::AreEqual(aVector.Size(), aCopy.Size());

			// Same values
			Assert::AreEqual(aVector[0], aCopy[0]);
			Assert::AreEqual(aVector[1], aCopy[1]);
			Assert::AreEqual(aVector[2], aCopy[2]);

			Assert::AreNotEqual(aVector[1], aCopy[2]);
		}
		TEST_METHOD(InitializerList)
		{
			VectorOnStack<int, 3> vector{ 4, 8, 16 };
			Assert::AreEqual(4, vector[0]);
			Assert::AreEqual(8, vector[1]);
			Assert::AreEqual(16, vector[2]);
		}

		TEST_METHOD(InitializerListFill)
		{
			VectorOnStack<int, 3, int> vector{ 4 };

			Assert::AreEqual(4, vector[0]);
			Assert::AreNotEqual(0, vector[0]);

			Assert::AreEqual(1, vector.Size());
			Assert::AreEqual(3, vector.Capacity());
		}

		TEST_METHOD(UnsafeInitializerListFill)
		{
			VectorOnStack<int, 3, int, false> vector{ 4 };

			Assert::AreEqual(4, vector[0]);
			Assert::AreNotEqual(0, vector[0]);

			Assert::AreEqual(1, vector.Size());
			Assert::AreEqual(3, vector.Capacity());
		}

		TEST_METHOD(UnsafeCopyAssignment)
		{
			VectorOnStack<int, 3, int, false> aVector;
			Assert::AreEqual(0, aVector.Size());

			aVector.Add(2);
			aVector.Add(4);
			aVector.Add(6);

			VectorOnStack<int, 3, int, false> aCopy = aVector;

			// Same size
			Assert::AreEqual(aVector.Size(), aCopy.Size());

			// Same values
			Assert::AreEqual(aVector[0], aCopy[0]);
			Assert::AreEqual(aVector[1], aCopy[1]);
			Assert::AreEqual(aVector[2], aCopy[2]);

			Assert::AreNotEqual(aVector[1], aCopy[2]);
		}
	};

	TEST_CLASS(SubscriptOperator)
	{
	public:
		TEST_METHOD(InsideOfRange)
		{
			VectorOnStack<int, 3> vector{ 2, 4, 6 };

			Assert::AreEqual(2, vector[0]);
			Assert::AreEqual(4, vector[1]);
			Assert::AreEqual(6, vector[2]);
			Assert::AreNotEqual(2, vector[1]);
		}
	};

	TEST_CLASS(Add)
	{
	public:
		TEST_METHOD(AddAtEnd)
		{
			VectorOnStack<int, 6> vector{ 1, 2, 3 };
			vector.Add(4);
			vector.Add(5);
			vector.Add(6);

			Assert::AreEqual(1, vector[0]);
			Assert::AreEqual(4, vector[3]);
			Assert::AreEqual(6, vector[vector.Size() - 1]);
		}

		TEST_METHOD(CorrectSize)
		{
			VectorOnStack<int, 5, int> vector;
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);

			Assert::AreEqual(3, vector.Size());
			Assert::AreNotEqual(5, vector.Size());
		}
	};

	TEST_CLASS(Insert)
	{
	public:
		TEST_METHOD(InsertAtZero)
		{
			VectorOnStack<int, 3, int> vector{ 1, 2 };

			Assert::AreEqual(1, vector[0]);
			Assert::AreEqual(2, vector[1]);
			vector.Insert(0, 10);
			Assert::AreEqual(10, vector[0]);
			Assert::AreEqual(1, vector[1]);
			Assert::AreEqual(2, vector[2]);

			Assert::AreEqual(3, vector.Size());
		}

		TEST_METHOD(InsertMiddle)
		{
			VectorOnStack<int, 3, int> vector{ 1, 2 };

			Assert::AreEqual(1, vector[0]);
			Assert::AreEqual(2, vector[1]);
			vector.Insert(1, 10);
			Assert::AreEqual(10, vector[1]);
			Assert::AreEqual(1, vector[0]);
			Assert::AreEqual(2, vector[2]);

			Assert::AreEqual(3, vector.Size());
		}

		TEST_METHOD(InsertAtEnd)
		{
			VectorOnStack<int, 3, int> vector{ 1, 2 };

			Assert::AreEqual(1, vector[0]);
			Assert::AreEqual(2, vector[1]);
			
			vector.Insert(2, 10);
			
			Assert::AreEqual(10, vector[vector.Size() - 1]);
			Assert::AreEqual(3, vector.Size());
		}

		TEST_METHOD(InsertIntoEmpty)
		{
			VectorOnStack<int, 3, int> vector;

			Assert::AreEqual(0, vector.Size());
			vector.Insert(0, 10);
			Assert::AreEqual(10, vector[0]);
			Assert::AreEqual(1, vector.Size());
		}

		TEST_METHOD(UnsafeInsertAtZero)
		{
			VectorOnStack<int, 4, int, false> vector{ 1, 2, 3 };

			Assert::AreEqual(1, vector[0]);
			Assert::AreEqual(3, vector[2]);
			vector.Insert(0, 10);
			Assert::AreEqual(10, vector[0]);
			Assert::AreEqual(2, vector[2]);

			Assert::AreEqual(4, vector.Size());
		}

		TEST_METHOD(UnsafeInsertMiddle)
		{
			VectorOnStack<int, 6, int, false> vector{ 1, 2, 3 };

			Assert::AreEqual(1, vector[0]);
			Assert::AreEqual(3, vector[2]);
			vector.Insert(1, 10);
			Assert::AreEqual(10, vector[1]);
			Assert::AreEqual(1, vector[0]);
			Assert::AreEqual(2, vector[2]);

			Assert::AreEqual(4, vector.Size());
			vector.Insert(4, 5);
		}

		TEST_METHOD(UnsafeInsertAtEnd)
		{
			VectorOnStack<int, 3, int, false> vector{ 1, 2 };

			Assert::AreEqual(1, vector[0]);
			Assert::AreEqual(2, vector[1]);

			vector.Insert(2, 10);

			Assert::AreEqual(10, vector[vector.Size() - 1]);
			Assert::AreEqual(3, vector.Size());
		}

		TEST_METHOD(UnsafeInsertIntoEmpty)
		{
			VectorOnStack<int, 3, int, false> vector{ 1 };

			Assert::AreEqual(1, vector[0]);
			Assert::AreEqual(1, vector.Size());

			vector.Insert(0, 10);

			Assert::AreEqual(10, vector[0]);
			Assert::AreEqual(1, vector[1]);
			Assert::AreEqual(2, vector.Size());
		}
	};

	TEST_CLASS(Clear)
	{
	public:
		TEST_METHOD(SizeIsZero)
		{
			VectorOnStack<int, 3, int> vector{ 1, 2, 3 };
			Assert::AreEqual(3, vector.Size());

			vector.Clear();
			Assert::AreEqual(0, vector.Size());
		}

		TEST_METHOD(AddAfterClear)
		{
			VectorOnStack<int, 3, int> vector{ 1, 2, 3 };
			Assert::AreEqual(3, vector.Size());

			vector.Clear();
			Assert::AreEqual(0, vector.Size());

			vector.Add(3);
			Assert::AreEqual(3, vector[0]);
			Assert::AreEqual(1, vector.Size());
		}
	};

	TEST_CLASS(RemoveCyclic)
	{
		TEST_METHOD(RemoveAtZero)
		{
			VectorOnStack<int, 3, int> vector{ 1, 2, 3 };
			vector.RemoveCyclic(1);
			Assert::AreEqual(2, vector.Size());
			Assert::AreEqual(3, vector[0]); // Last moved to first
		}

		TEST_METHOD(RemoveAtMiddle)
		{
			VectorOnStack<int, 3, int> vector{ 1, 2, 3 };
			vector.RemoveCyclic(2);
			Assert::AreEqual(2, vector.Size());
		}

		TEST_METHOD(RemoveLast)
		{
			VectorOnStack<int, 3, int> vector{ 1, 2, 3 };
			vector.RemoveCyclic(3);
			Assert::AreEqual(2, vector.Size());
			Assert::AreEqual(1, vector[0]);
		}
	};

	TEST_CLASS(RemoveCyclicAtIndex)
	{
		TEST_METHOD(RemoveAtZero)
		{
			VectorOnStack<int, 3, int> vector{ 1, 2, 3 };
			vector.RemoveCyclicAtIndex(0);
			Assert::AreEqual(2, vector.Size());
			Assert::AreEqual(3, vector[0]); // Last moved to first
		}

		TEST_METHOD(RemoveAtMiddle)
		{
			VectorOnStack<int, 3, int> vector{ 1, 2, 3 };
			vector.RemoveCyclicAtIndex(2);
			Assert::AreEqual(2, vector.Size());
		}

		TEST_METHOD(RemoveLast)
		{
			VectorOnStack<int, 3, int> vector{ 1, 2, 3 };
			vector.RemoveCyclicAtIndex(2);
			Assert::AreEqual(2, vector.Size());
			Assert::AreEqual(1, vector[0]);
			Assert::AreEqual(2, vector[1]);
		}
	};
}