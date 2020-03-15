#include "pch.h"
#include "CppUnitTest.h"
#include "..//CommonUtilities/BSTSet.hpp"
#include <string>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CommonUtilities;

namespace BSTSetTests
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
				BSTSet<int> bst;
				bst.Insert(8);
				bst.Insert(10);
				bst.Insert(4);
				bst.Insert(5);
				bst.Insert(7);
				bst.Insert(6);
				bst.Insert(9);
				bst.Insert(11);
				
				bst.Remove(8);
				Assert::IsTrue(bst.HasElement(7));
				Assert::IsFalse(bst.IsEmpty());
				bst.Remove(7);
				Assert::IsTrue(bst.HasElement(6));
				Assert::IsFalse(bst.IsEmpty());
				bst.Remove(6);
				Assert::IsTrue(bst.HasElement(4));
				Assert::IsFalse(bst.IsEmpty());
				bst.Remove(4);

				Assert::IsTrue(bst.HasElement(5));
				Assert::IsFalse(bst.IsEmpty());
				bst.Remove(5);

				Assert::IsTrue(bst.HasElement(10));
				Assert::IsFalse(bst.IsEmpty());
				bst.Remove(9);
				bst.Remove(10);
				Assert::IsTrue(!bst.HasElement(8));
				bst.Remove(11);

				Assert::IsTrue(bst.IsEmpty());
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
	};
}