#include "pch.h"
#include "CppUnitTest.h"
#include "..//CommonUtilities/GrowingArray.h"
#include <string>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CommonUtilities;

namespace GrowingArrayTest
{
	TEST_CLASS(Constructors)
	{
	public:
		TEST_METHOD(NoMemLeak)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				GrowingArray<int, int> arr(10);
				Assert::AreEqual(0, arr.Size());

				arr.Add(1);
				Assert::AreEqual(1, arr[0]);
				Assert::AreEqual(1, arr.Size());
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
		TEST_METHOD(UnsafeNoMemLeak)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				GrowingArray<int, int> arr(10, false);
				Assert::AreEqual(0, arr.Size());

				arr.Add(1);
				Assert::AreEqual(1, arr[0]);
				Assert::AreEqual(1, arr.Size());
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
		TEST_METHOD(NoMemLeakString)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				GrowingArray<std::string, int> arr(10);
				arr.Add("hej");
				arr.Add("nej");
				arr.Add("ja");
				GrowingArray <std::string, int> aCopy = arr;
				Assert::AreEqual(3, aCopy.Size());
				Assert::AreEqual(10, aCopy.Capacity());
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
		TEST_METHOD(ModifyingSourceValue)
		{
			GrowingArray<std::string, int> arr;
			arr.Init();
			Assert::AreEqual(0, arr.Size());

			arr.Add("hej");
			arr.Add("nej");
			arr.Add("ja");
			GrowingArray<std::string, int> aCopy = arr;

			// Same values
			Assert::AreEqual(arr[0], aCopy[0]);

			arr[0] = "changed";
			// Not sharing memory
			Assert::AreNotEqual(arr[0], aCopy[0]);
			Assert::AreEqual("changed", arr[0].c_str());
			Assert::AreEqual("hej", aCopy[0].c_str());
		}
		TEST_METHOD(MoveConstructor)
		{
			GrowingArray<int, int> arr;
			arr.Init();
			arr.Add(1);
			arr.Add(1);
			arr.Add(1);

			GrowingArray<int, int> test = std::move(arr);
		}
		TEST_METHOD(UnsafeSameValueAfterInts)
		{
			{
				_CrtMemState memStart;
				_CrtMemState memEnd;
				_CrtMemState memDiff;
				_CrtMemCheckpoint(&memStart);
				{
					GrowingArray<int, int> arr2(5, false);
					arr2.Add(1);
					arr2.Add(2);
					arr2.Add(3);
					GrowingArray <int, int> aCopy(3, false);
					aCopy.Add(23);
					aCopy = arr2;
				}
				_CrtMemCheckpoint(&memEnd);
				Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");

			}
			GrowingArray<int, int> arr(5, false);
			arr.Add(1);
			arr.Add(2);
			arr.Add(3);
			GrowingArray <int, int> aCopy = arr;
			// Same size
			Assert::AreEqual(arr.Size(), aCopy.Size());
			Assert::AreEqual(1, arr[0]);
			Assert::AreEqual(1, aCopy[0]);

			// Same values
			Assert::AreEqual(arr[0], aCopy[0]);
			Assert::AreEqual(arr[1], aCopy[1]);
			Assert::AreEqual(arr[2], aCopy[2]);
		}
		TEST_METHOD(NoMemLeakStringEmpty)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				{
					GrowingArray<std::string, int> arr(10);
					GrowingArray <std::string, int> aCopy = arr;
				}
				{
					GrowingArray<std::string, int> arr;
				}
				{
					GrowingArray<std::string, int> arr(100);
				}
				{
					GrowingArray<std::string, int> arr;
					arr.Init();
				}
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
		TEST_METHOD(NoMemLeakStringEmptyUnsafe)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				{
					GrowingArray<std::string, int> arr(10, false);
					GrowingArray <std::string, int> aCopy = arr;
				}
				{
					GrowingArray<std::string, int> arr;
				}
				{
					GrowingArray<std::string, int> arr(100, false);
				}
				{
					GrowingArray<std::string, int> arr;
					arr.Init(10, false);
				}
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
	};

	TEST_CLASS(SubscriptOperator)
	{
	public:
		TEST_METHOD(AccessInsideOfRange)
		{
			GrowingArray<int, int> arr;
			arr.Init();
			arr.Add(1);
			arr.Add(2);
			Assert::AreEqual(1, arr[0]);
			Assert::AreEqual(2, arr[1]);
		}
		TEST_METHOD(AssignWithSubscript)
		{
			GrowingArray<int, int> arr;
			arr.Init();
			arr.Add(1);
			arr.Add(2);
			Assert::AreEqual(1, arr[0]);
			Assert::AreEqual(2, arr[1]);
			
			arr[0] = 5;
			Assert::AreEqual(5, arr[0]);
			Assert::AreEqual(2, arr[1]);
		}
		TEST_METHOD(UnsafeAccessInsideOfRange)
		{
			GrowingArray<int, int> arr;
			arr.Init(2, false);
			arr.Add(1);
			arr.Add(2);
			Assert::AreEqual(1, arr[0]);
			Assert::AreEqual(2, arr[1]);
		}
		TEST_METHOD(UnsafeAssignWithSubscript)
		{
			GrowingArray<int, int> arr;
			arr.Init(2, false);
			arr.Add(1);
			arr.Add(2);
			Assert::AreEqual(1, arr[0]);
			Assert::AreEqual(2, arr[1]);

			arr[0] = 5;
			Assert::AreEqual(5, arr[0]);
			Assert::AreEqual(2, arr[1]);
		}
		TEST_METHOD(MemoryLeak)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				{
					GrowingArray<int, int> arr;
					arr.Init();
					arr.Add(1);
					arr.Add(2);
					Assert::AreEqual(1, arr[0]);
					Assert::AreEqual(2, arr[1]);
				}
				{
					GrowingArray<int, int> arr;
					arr.Init(2);
					arr.Add(1);
					arr.Add(2);
					Assert::AreEqual(1, arr[0]);
					Assert::AreEqual(2, arr[1]);

					arr[0] = 5;
					Assert::AreEqual(5, arr[0]);
					Assert::AreEqual(2, arr[1]);
				}
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
		TEST_METHOD(UnsafeMemoryLeak)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				{
					GrowingArray<int, int> arr;
					arr.Init(1, false);
					arr.Add(1);
					arr.Add(2);
					Assert::AreEqual(1, arr[0]);
					Assert::AreEqual(2, arr[1]);
				}
				{
					GrowingArray<int, int> arr(1, false);
					arr.Add(1);
					arr.Add(2);
					Assert::AreEqual(1, arr[0]);
					Assert::AreEqual(2, arr[1]);

					arr[0] = 5;
					Assert::AreEqual(5, arr[0]);
					Assert::AreEqual(2, arr[1]);
				}
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
	};

	TEST_CLASS(Resize)
	{
	public:

		TEST_METHOD(ResizeCapacityGrowth)
		{
			GrowingArray<int, int> arr;
			arr.Init();
			arr.Add(1);
			Assert::AreEqual(1, arr.Size());
			arr.Add(2);
			Assert::AreEqual(2, arr.Size());
			Assert::AreEqual(2, arr.Capacity());
		}
		TEST_METHOD(ResizeToBigger)
		{
			GrowingArray<int, int> arr;
			arr.Init();
			arr.Add(1);
			Assert::AreEqual(1, arr.Capacity());
			Assert::AreEqual(1, arr.Size());

			arr.Resize(100);
			Assert::AreEqual(100, arr.Capacity());
			Assert::AreEqual(100, arr.Size());
		}
		TEST_METHOD(ResizeToSmaller)
		{
			GrowingArray<int, int> arr;
			arr.Init();
			arr.Add(2);
			arr.Add(4);
			arr.Add(6);
			arr.Add(8);
			const int capacity = arr.Capacity();
			arr.Resize(2);
			Assert::AreEqual(2, arr.Size());
			Assert::AreEqual(4, arr[1]);
			Assert::AreEqual(capacity, arr.Capacity());
		}
		TEST_METHOD(UnsafeResizeCapacityGrowth)
		{
			GrowingArray<int, int> arr;
			arr.Init(1, false);
			arr.Add(1);
			Assert::AreEqual(1, arr.Size());
			arr.Add(2);
			Assert::AreEqual(2, arr.Size());
			Assert::AreEqual(2, arr.Capacity());
		}
		TEST_METHOD(UnsafeResizeToBigger)
		{
			GrowingArray<int, int> arr;
			arr.Init(1, false);
			arr.Add(1);
			Assert::AreEqual(1, arr.Capacity());
			Assert::AreEqual(1, arr.Size());

			arr.Resize(100);
			Assert::AreEqual(100, arr.Capacity());
			Assert::AreEqual(100, arr.Size());
		}
		TEST_METHOD(UnsafeResizeToSmaller)
		{
			GrowingArray<int, int> arr;
			arr.Init(4, false);
			arr.Add(2);
			arr.Add(4);
			arr.Add(6);
			arr.Add(8);
			const int capacity = arr.Capacity();
			arr.Resize(2);
			Assert::AreEqual(2, arr.Size());
			Assert::AreEqual(4, arr[1]);
			Assert::AreEqual(capacity, arr.Capacity());
		}

		TEST_METHOD(UnsafeMemoryLeak)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				{
					GrowingArray<int, int> arr;
					arr.Init(4, false);
					arr.Add(2);
					arr.Add(4);
					arr.Add(6);
					arr.Add(8);
					const int capacity = arr.Capacity();
					arr.Resize(2);
					Assert::AreEqual(2, arr.Size());
					Assert::AreEqual(4, arr[1]);
					Assert::AreEqual(capacity, arr.Capacity());
				}
				{
					GrowingArray<int, int> arr(4, false);
					arr.Add(2);
					arr.Add(4);
					arr.Add(6);
					arr.Add(8);
					const int capacity = arr.Capacity();
					arr.Resize(2);
					Assert::AreEqual(2, arr.Size());
					Assert::AreEqual(4, arr[1]);
					Assert::AreEqual(capacity, arr.Capacity());
				}
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}

		TEST_METHOD(MemoryLeak)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				GrowingArray<int, int> arr;
				arr.Init();
				arr.Add(2);
				arr.Add(4);
				arr.Add(6);
				arr.Add(8);
				const int capacity = arr.Capacity();
				arr.Resize(2);
				Assert::AreEqual(2, arr.Size());
				Assert::AreEqual(4, arr[1]);
				Assert::AreEqual(capacity, arr.Capacity());
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
	};
	TEST_CLASS(Reserve)
	{
		TEST_METHOD(MemoryLeak)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				GrowingArray<int, int> arr(1);
				arr.Add(1);
				arr.Reserve(100);
				Assert::AreEqual(1, arr.Size());
				Assert::AreEqual(100, arr.Capacity());
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");

		}
		TEST_METHOD(UnsafeMemoryLeak)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				GrowingArray<int, int> arr;
				arr.Init(4, false);
				arr.Add(2);
				arr.Add(4);
				arr.Add(6);
				arr.Add(8);
				const int capacity = arr.Capacity();
				arr.Resize(2);
				Assert::AreEqual(2, arr.Size());
				Assert::AreEqual(4, arr[1]);
				Assert::AreEqual(capacity, arr.Capacity());
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
	};
	
	TEST_CLASS(Insert)
	{
	public:
		TEST_METHOD(InsertAtZeroStrings)
		{
			GrowingArray<std::string, int> vector;
			vector.Init();
			vector.Insert(0, "1");
			Assert::AreEqual("1", vector[0].c_str());

			vector.Insert(0, "0");
			Assert::AreEqual("0", vector[0].c_str());
			Assert::AreEqual("1", vector[1].c_str());
		}
		TEST_METHOD(InsertAtZero)
		{
			GrowingArray<int, int> vector;
			vector.Init();
			vector.Insert(0, 10);
			Assert::AreEqual(10, vector[0]);

			vector.Insert(0, 5);
			Assert::AreEqual(5, vector[0]);
			Assert::AreEqual(10, vector[1]);
		}

		TEST_METHOD(InsertMiddle)
		{
			GrowingArray<int, int> vector;
			vector.Init();
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);
			vector.Add(4);
			vector.Insert(1, 10);
			Assert::AreEqual(1, vector[0]);
			Assert::AreEqual(10, vector[1]);
			Assert::AreEqual(2, vector[2]);
			Assert::AreEqual(3, vector[3]);
			Assert::AreEqual(4, vector[4]);
		}

		TEST_METHOD(InsertAtEnd)
		{
			GrowingArray<int, int> vector;
			vector.Init();
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);
			vector.Add(4);
			vector.Insert(vector.Size(), 10);
			Assert::AreEqual(10, vector[vector.Size() -1]);
		}
		TEST_METHOD(UnsafeInsertAtZero)
		{
			GrowingArray<int, int> vector;
			vector.Init(1, false);
			vector.Insert(0, 10);
			Assert::AreEqual(10, vector[0]);

			vector.Insert(0, 5);
			Assert::AreEqual(5, vector[0]);
			Assert::AreEqual(10, vector[1]);
		}

		TEST_METHOD(UnsafeInsertMiddle)
		{
			GrowingArray<int, int> vector;
			vector.Init(3, false);
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);
			vector.Add(4);
			vector.Insert(1, 10);
			Assert::AreEqual(1, vector[0]);
			Assert::AreEqual(10, vector[1]);
			Assert::AreEqual(2, vector[2]);
			Assert::AreEqual(3, vector[3]);
			Assert::AreEqual(4, vector[4]);
		}

		TEST_METHOD(UnsafeInsertAtEnd)
		{
			GrowingArray<int, int> vector;
			vector.Init(1, false);
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);
			vector.Add(4);
			vector.Insert(vector.Size(), 10);
			Assert::AreEqual(10, vector[vector.Size() - 1]);
		}

		TEST_METHOD(UnsafeMemoryLeakTest)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				{
					GrowingArray<int, int> vector;
					vector.Init(3, false);
					vector.Add(1);
					vector.Add(2);
					vector.Add(3);
					vector.Add(4);
					vector.Insert(1, 10);
					Assert::AreEqual(1, vector[0]);
					Assert::AreEqual(10, vector[1]);
					Assert::AreEqual(2, vector[2]);
					Assert::AreEqual(3, vector[3]);
					Assert::AreEqual(4, vector[4]);
				}
				{
					GrowingArray<int, int> vector;
					vector.Init(1, false);
					vector.Add(1);
					vector.Add(2);
					vector.Add(3);
					vector.Add(4);
					vector.Insert(vector.Size(), 10);
					Assert::AreEqual(10, vector[vector.Size() - 1]);
				}
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
		TEST_METHOD(MemoryLeakTest)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				{
					GrowingArray<int, int> vector;
					vector.Init(3);
					vector.Add(1);
					vector.Add(2);
					vector.Add(3);
					vector.Add(4);
					vector.Insert(1, 10);
					Assert::AreEqual(1, vector[0]);
					Assert::AreEqual(10, vector[1]);
					Assert::AreEqual(2, vector[2]);
					Assert::AreEqual(3, vector[3]);
					Assert::AreEqual(4, vector[4]);
				}
				{
					GrowingArray<int, int> vector(1);
					vector.Add(1);
					vector.Add(2);
					vector.Add(3);
					vector.Add(4);
					vector.Insert(vector.Size(), 10);
					Assert::AreEqual(10, vector[vector.Size() - 1]);
				}
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
	};

	TEST_CLASS(RemoveCyclic)
	{
		TEST_METHOD(RemoveAtZero)
		{
			GrowingArray<int, int> vector;
			vector.Init();
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);
			Assert::AreEqual(3, vector.Size());
			vector.RemoveCyclic(1);
			Assert::AreEqual(2, vector.Size());
			Assert::AreEqual(3, vector[0]);
		}

		TEST_METHOD(RemoveAtMiddle)
		{
			GrowingArray<int, int> vector;
			vector.Init();
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);
			Assert::AreEqual(3, vector.Size());
			vector.RemoveCyclic(2);
			Assert::AreEqual(2, vector.Size());
			Assert::AreEqual(3, vector[1]);
		}

		TEST_METHOD(RemoveLast)
		{
			GrowingArray<int, int> vector;
			vector.Init();
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);
			Assert::AreEqual(3, vector.Size());
			vector.RemoveCyclic(3);
			Assert::AreEqual(2, vector.Size());
			Assert::AreEqual(2, vector[1]);
		}
		TEST_METHOD(UnsafeRemoveAtZero)
		{
			GrowingArray<int, int> vector;
			vector.Init(1, false);
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);
			Assert::AreEqual(3, vector.Size());
			vector.RemoveCyclic(1);
			Assert::AreEqual(2, vector.Size());
			Assert::AreEqual(3, vector[0]);
		}

		TEST_METHOD(UnsafeRemoveAtMiddle)
		{
			GrowingArray<int, int> vector;
			vector.Init(1, false);
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);
			Assert::AreEqual(3, vector.Size());
			vector.RemoveCyclic(2);
			Assert::AreEqual(2, vector.Size());
			Assert::AreEqual(3, vector[1]);
		}

		TEST_METHOD(UnsafeRemoveLast)
		{
			GrowingArray<int, int> vector;
			vector.Init(1, false);
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);
			Assert::AreEqual(3, vector.Size());
			vector.RemoveCyclic(3);
			Assert::AreEqual(2, vector.Size());
			Assert::AreEqual(2, vector[1]);
		}
		TEST_METHOD(MemoryLeakTest)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				{
					GrowingArray<int, int> vector;
					vector.Init();
					vector.Add(1);
					vector.Add(2);
					vector.Add(3);
					Assert::AreEqual(3, vector.Size());
					vector.RemoveCyclic(3);
					Assert::AreEqual(2, vector.Size());
					Assert::AreEqual(2, vector[1]);
				}
				{
					GrowingArray<int, int> vector;
					vector.Init();
					vector.Add(1);
					vector.Add(2);
					vector.Add(3);
					Assert::AreEqual(3, vector.Size());
					vector.RemoveCyclic(2);
					Assert::AreEqual(2, vector.Size());
					Assert::AreEqual(3, vector[1]);
				}
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
		TEST_METHOD(MemoryLeakTestString)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				{
					GrowingArray<std::string, int> vector;
					vector.Init();
					vector.Add("lorem");
					vector.Add("ipsum");
					vector.Add("dolor");
					Assert::AreEqual(3, vector.Size());
					vector.RemoveCyclic("ipsum");
					Assert::AreEqual(2, vector.Size());
					Assert::AreEqual(std::string("dolor"), vector[1]);
				}
				{
					GrowingArray<std::string, int> vector(3, false);
					vector.Add("lorem");
					vector.Add("ipsum");
					vector.Add("dolor");
					Assert::AreEqual(3, vector.Size());
					vector.RemoveCyclic("ipsum");
					Assert::AreEqual(2, vector.Size());
					Assert::AreEqual(std::string("dolor"), vector[1]);
					
				}
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
	};
	
	TEST_CLASS(RemoveCyclicAtIndex)
	{
		TEST_METHOD(RemoveAtZero)
		{
			GrowingArray<int, int> vector;
			vector.Init();
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);
			Assert::AreEqual(3, vector.Size());
			vector.RemoveCyclicAtIndex(0);
			Assert::AreEqual(2, vector.Size());
			Assert::AreEqual(3, vector[0]);
		}

		TEST_METHOD(RemoveAtMiddle)
		{
			GrowingArray<int, int> vector;
			vector.Init();
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);
			Assert::AreEqual(3, vector.Size());
			vector.RemoveCyclicAtIndex(1);
			Assert::AreEqual(2, vector.Size());
			Assert::AreEqual(3, vector[1]);
		}

		TEST_METHOD(RemoveLast)
		{
			GrowingArray<int, int> vector;
			vector.Init();
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);
			Assert::AreEqual(3, vector.Size());
			vector.RemoveCyclicAtIndex(2);
			Assert::AreEqual(2, vector.Size());
			Assert::AreEqual(2, vector[1]);
		}

		TEST_METHOD(UnsafeRemoveAtZero)
		{
			GrowingArray<int, int> vector;
			vector.Init(1, false);
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);
			Assert::AreEqual(3, vector.Size());
			vector.RemoveCyclicAtIndex(0);
			Assert::AreEqual(2, vector.Size());
			Assert::AreEqual(3, vector[0]);
		}

		TEST_METHOD(UnsafeRemoveAtMiddle)
		{
			GrowingArray<int, int> vector;
			vector.Init(1, false);
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);
			Assert::AreEqual(3, vector.Size());
			vector.RemoveCyclicAtIndex(1);
			Assert::AreEqual(2, vector.Size());
			Assert::AreEqual(3, vector[1]);
		}

		TEST_METHOD(UnsafeRemoveLast)
		{
			GrowingArray<int, int> vector;
			vector.Init(1, false);
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);
			Assert::AreEqual(3, vector.Size());
			vector.RemoveCyclicAtIndex(2);
			Assert::AreEqual(2, vector.Size());
			Assert::AreEqual(2, vector[1]);
		}

		TEST_METHOD(MemLeakStrings)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				{
					GrowingArray<std::string, int> vector;
					vector.Init();
					vector.Add("lorem");
					vector.Add("ipsum");
					vector.Add("dolor");
					vector.RemoveCyclicAtIndex(0);
					Assert::AreEqual(std::string("dolor"), vector[0]);
					vector.RemoveCyclicAtIndex(0);
					vector.RemoveCyclicAtIndex(0);
					Assert::AreEqual(0, vector.Size());
				}
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
	};

	TEST_CLASS(RemoveAll)
	{
		TEST_METHOD(RemoveFullArray)
		{
			GrowingArray<int, int> vector(3);
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);
			const int capacity = vector.Capacity();
			vector.RemoveAll();
			Assert::AreEqual(capacity, vector.Capacity());
			Assert::AreEqual(0, vector.Size());
		}
		TEST_METHOD(AddAfterRemove)
		{
			GrowingArray<int, int> vector(3);
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);

			vector.RemoveAll();
			Assert::AreEqual(0, vector.Size());
			vector.Add(5);
			Assert::AreEqual(1, vector.Size());
			Assert::AreEqual(5, vector[0]);

		}
		TEST_METHOD(UnsafeRemoveFullArray)
		{
			GrowingArray<int, int> vector(3, false);
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);
			const int capacity = vector.Capacity();
			vector.RemoveAll();
			Assert::AreEqual(capacity, vector.Capacity());
			Assert::AreEqual(0, vector.Size());
		}
		TEST_METHOD(UnsafeAddAfterRemove)
		{
			GrowingArray<int, int> vector(3, false);
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);

			vector.RemoveAll();
			Assert::AreEqual(0, vector.Size());
			vector.Add(5);
			Assert::AreEqual(1, vector.Size());
			Assert::AreEqual(5, vector[0]);

		}

		TEST_METHOD(RemoveAllMemLeak)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				{
					GrowingArray<std::string, int> vector;
					vector.Init();
					vector.Add("lorem");
					vector.Add("ipsum");
					vector.Add("dolor");
					vector.RemoveAll();
					Assert::AreEqual(0, vector.Size());
				}
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
	};

	TEST_CLASS(Optimize)
	{
		TEST_METHOD(RemoveFullArray)
		{
			GrowingArray<int, int> vector(10);
			vector.Add(1);
			vector.Add(2);
			vector.Add(3);
			Assert::AreEqual(10, vector.Capacity());
			Assert::AreEqual(3, vector.Size());
			vector.Optimize();
			Assert::AreEqual(3, vector.Capacity());
			Assert::AreEqual(3, vector.Size());
		}
		TEST_METHOD(MemoryLeak)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				GrowingArray<std::string, int> vector(10);
				vector.Add("lorem");
				vector.Add("ipsum");
				vector.Add("dolor");
				Assert::AreEqual(10, vector.Capacity());
				Assert::AreEqual(3, vector.Size());
				vector.Optimize();
				Assert::AreEqual(3, vector.Capacity());
				Assert::AreEqual(3, vector.Size());
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
		TEST_METHOD(MemoryLeakStrings)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				GrowingArray<int, int> vector(10);
				vector.Add(1);
				vector.Add(2);
				vector.Add(3);
				Assert::AreEqual(10, vector.Capacity());
				Assert::AreEqual(3, vector.Size());
				vector.Optimize();
				Assert::AreEqual(3, vector.Capacity());
				Assert::AreEqual(3, vector.Size());
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}

		TEST_METHOD(UnsafeMemoryLeak)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				{
					GrowingArray<int, int> vector(10, false);
					vector.Add(1);
					vector.Add(2);
					vector.Add(3);
					Assert::AreEqual(10, vector.Capacity());
					Assert::AreEqual(3, vector.Size());
					vector.Optimize();
					Assert::AreEqual(3, vector.Capacity());
					Assert::AreEqual(3, vector.Size());
				}
				{
					GrowingArray<int, int> vector;
					vector.Init(10, false);
					vector.Add(1);
					vector.Add(2);
					vector.Add(3);
					Assert::AreEqual(10, vector.Capacity());
					Assert::AreEqual(3, vector.Size());
					vector.Optimize();
					Assert::AreEqual(3, vector.Capacity());
					Assert::AreEqual(3, vector.Size());
				}
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
	};

	TEST_CLASS(Find)
	{
		TEST_METHOD(FindAtZero)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				{
					GrowingArray<std::string, int> vector;
					vector.Init();
					vector.Add("lorem");
					vector.Add("ipsum");
					vector.Add("dolor");
					Assert::AreEqual(0, vector.Find("lorem"));
				}
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
		TEST_METHOD(FindNone)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				{
					GrowingArray<std::string, int> vector(3, false);
					vector.Add("lorem");
					vector.Add("ipsum");
					vector.Add("dolor");
					Assert::AreEqual(GrowingArray<std::string, int>::FoundNone, vector.Find("none"));
				}
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
	};
}