#include "pch.h"
#include "CppUnitTest.h"
#include <Containers/Heap.hpp>
#include <string>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HeapTests
{
	using namespace CommonUtilities;

	TEST_CLASS(HeapClass)
	{
		_CrtMemState memStart;
		_CrtMemState memEnd;
		_CrtMemState memDiff;
	public:
		TEST_METHOD(NoMemLeak)
		{
			_CrtMemCheckpoint(&memStart);
			{
				Heap<int> heap;
				heap.Enqueue(5);
				heap.Enqueue(1);
				heap.Enqueue(4);
				heap.Enqueue(7);
				heap.Enqueue(3);

				Assert::AreEqual(7, heap.GetTop());
				Assert::AreEqual(7, heap.Dequeue());
				Assert::AreEqual(5, heap.Dequeue());
				Assert::AreEqual(4, heap.Dequeue());
				Assert::AreEqual(3, heap.Dequeue());
				Assert::AreEqual(1, heap.Dequeue());
				Assert::AreEqual(0, heap.GetSize());
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
	};
}