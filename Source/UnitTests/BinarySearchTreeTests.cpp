#include "pch.h"
#include "CppUnitTest.h"
#include <Containers/BinarySearchTree/BSTSet.hpp>
#include <string>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BSTSetTests
{
	using namespace CommonUtilities;
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
				BSTSet<int> bst;
				bst.Insert(8);
				bst.Insert(10);
				bst.Insert(4);
				bst.Insert(5);
				bst.Insert(7);
				bst.Insert(6);
				bst.Insert(9);
				bst.Insert(11);
				Assert::AreEqual(size_t(8), bst.GetSize());

				bst.Remove(8);

				Assert::AreEqual(size_t(7), bst.GetSize());
				Assert::IsTrue(bst.HasElement(7));
				Assert::IsFalse(bst.IsEmpty());
				bst.Remove(7);

				Assert::AreEqual(size_t(6), bst.GetSize());
				Assert::IsTrue(bst.HasElement(6));
				Assert::IsFalse(bst.IsEmpty());
				bst.Remove(6);

				Assert::AreEqual(size_t(5), bst.GetSize());
				Assert::IsTrue(bst.HasElement(4));
				Assert::IsFalse(bst.IsEmpty());
				bst.Remove(4);

				Assert::AreEqual(size_t(4), bst.GetSize());
				Assert::IsTrue(bst.HasElement(5));
				Assert::IsFalse(bst.IsEmpty());
				bst.Remove(5);

				Assert::IsTrue(bst.HasElement(10));
				Assert::IsFalse(bst.IsEmpty());
				bst.Remove(9);
				bst.Remove(10);
				Assert::IsTrue(!bst.HasElement(8));
				bst.Remove(11);
				Assert::AreEqual(size_t(0), bst.GetSize());
				Assert::IsTrue(bst.IsEmpty());
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}

		TEST_METHOD(BalanceTest)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				BSTSet<int> bst;
				bst.Insert(5);
				bst.Insert(10);
				bst.Insert(20);
				bst.Insert(15);
				bst.Insert(30);
				bst.Insert(25);
				bst.Insert(40);
				bst.Insert(23);
				bst.Insert(28);

				bst.DSWBalance();
				Assert::AreEqual(size_t(9), bst.GetSize());
				Assert::IsFalse(bst.IsEmpty());
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
	};
}