#include "pch.h"
#include "CppUnitTest.h"
#include "..//CommonUtilities/Sort.hpp"
#include "Shared/UtilityFunctions.hpp"
#include <string>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SortingTests
{
	using namespace CommonUtilities;

	TEST_CLASS(SortAlgorithms)
	{
		TEST_METHOD(SelectionSortTest)
		{
			std::vector<int> v;
			v.reserve(1000);
			for (int i = 0; i < 1000; i++)
			{
				v.push_back(rand() % 1000);
			}
			SelectionSort(v);
			auto itr = v.cbegin() + 1;
			while (itr != v.end())
			{
				Assert::IsTrue(*(itr - 1) <= *itr);
				++itr;
			}
		}

		TEST_METHOD(QuickSortTest)
		{
			std::vector<int> v;
			v.reserve(100000);
			for (int i = 0; i < 100000; i++)
			{
				v.push_back(rand() % 1000);
			}
			QuickSort(v);
			auto itr = v.cbegin() + 1;
			while (itr != v.end())
			{
				Assert::IsTrue(*(itr - 1) <= *itr);
				++itr;
			}
		}
		TEST_METHOD(MergeSortTest)
		{
			std::vector<int> v
			{
				4, 2, 8, 4, 6, 9, 1
			};
			v.reserve(100000);
			for (int i = 0; i < 100000; i++)
			{
				v.push_back(rand() % 1000);
			}
			MergeSort(v);
			auto itr = v.cbegin() + 1;
			while (itr != v.end())
			{
				Assert::IsTrue(*(itr - 1) <= *itr);
				++itr;
			}
		}
		TEST_METHOD(BubbleSortTest)
		{
			std::vector<int> v;
			v.reserve(100000);
			for (int i = 0; i < 100000; i++)
			{
				v.push_back(rand() % 1000);
			}
			BubbleSort(v);
			auto itr = v.cbegin() + 1;
			while (itr != v.end())
			{
				Assert::IsTrue(*(itr - 1) <= *itr);
				++itr;
			}
		}
	};
}