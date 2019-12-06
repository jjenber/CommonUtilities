#include "pch.h"
#include "CppUnitTest.h"
#include "..//CommonUtilities/Macros.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Macros
{
	TEST_CLASS(MacroMathMAX)
	{
	public:
		TEST_METHOD(BothPositive)
		{
			int smaller = 1;
			int bigger = 2;

			Assert::AreEqual(MAX(bigger, smaller), bigger, L"Failed testing bigger value as first argument.");
			Assert::AreEqual(MAX(smaller, bigger), bigger, L"Failed testing bigger value as second argument.");
		}
		TEST_METHOD(NegativeAndPositive)
		{
			int negative = -2;
			int positive = 1;

			Assert::AreEqual(MAX(negative, positive), positive, L"Failed testing negative value as first argument.");
			Assert::AreEqual(MAX(positive, negative), positive, L"Failed testing negative value as second argument.");
		}
		TEST_METHOD(BothNegative)
		{
			int smaller = -2;
			int bigger = -1;

			Assert::AreEqual(MAX(bigger, smaller), bigger, L"Failed testing smaller value as first argument.");
			Assert::AreEqual(MAX(smaller, bigger), bigger, L"Failed testing bigger value as second argument.");
		}
		TEST_METHOD(Precedence)
		{
			int result = 12;
			Assert::AreEqual(MAX(8 | 2, 8 | 4), result, L"Failed testing precedence, smallest value as first argument.");
			Assert::AreEqual(MAX(8 | 4, 8 | 2), result, L"Failed testing precedence, smallest value as second argument.");
		}
	};

	TEST_CLASS(MacroMathMIN)
	{
	public:
		TEST_METHOD(BothPositive)
		{
			int smaller = 1;
			int bigger = 2;

			Assert::AreEqual(MIN(smaller, bigger), smaller, L"Failed testing smaller value as first argument.");
			Assert::AreEqual(MIN(bigger, smaller), smaller, L"Failed testing smaller value as second argument.");
		}
		TEST_METHOD(NegativeAndPositive)
		{
			int negative = -2;
			int positive = 1;

			Assert::AreEqual(MIN(negative, positive), negative, L"Failed testing negative value as first argument.");
			Assert::AreEqual(MIN(positive, negative), negative, L"Failed testing negative value as second argument.");
		}
		TEST_METHOD(BothNegative)
		{
			int smaller = -2;
			int bigger = -1;

			Assert::AreEqual(MIN(smaller, bigger), smaller, L"Failed testing smaller value as first argument.");
			Assert::AreEqual(MIN(bigger, smaller), smaller, L"Failed testing smaller value as second argument.");
		}
		TEST_METHOD(Precedence)
		{
			int result = 10;
			Assert::AreEqual(MIN(8 | 2, 8 | 4), result, L"Failed testing precedence, smallest value as first argument.");
			Assert::AreEqual(MIN(8 | 4, 8 | 2), result, L"Failed testing precedence, smallest value as second argument.");
		}
	};

	TEST_CLASS(MacroMathCLAMP)
	{
	public:
		TEST_METHOD(InRange)
		{
			int min = 1;
			int max = 3;
			int testValue = 2;
			int inRangeResult = CLAMP(testValue, min, max);

			Assert::AreEqual(inRangeResult, testValue, L"Failed: testing in range value.");
			Assert::AreNotEqual(inRangeResult, min, L"Failed: testing in range value. Was min value");
			Assert::AreNotEqual(inRangeResult, max, L"Failed: testing in range value. Was max value");
		}
		TEST_METHOD(BelowRange)
		{
			int min = 1;
			int max = 3;
			int testValue = min - 1;
			int belowRangeResult = CLAMP(testValue, min, max);

			Assert::AreEqual(belowRangeResult, min, L"Failed: testing below range.");
			Assert::AreNotEqual(belowRangeResult, testValue, L"Failed: testing below range. Return value was below min.");
		}
		TEST_METHOD(AboveRange)
		{
			int min = 1;
			int max = 3;
			int testValue = max + 1;
			int aboveRangeResult = CLAMP(testValue, min, max);

			Assert::AreEqual(aboveRangeResult, max, L"Failed: testing above range.");
			Assert::AreNotEqual(aboveRangeResult, testValue, L"Failed: testing above range. Return value was above max.");
		}
		
		TEST_METHOD(SameAsMin)
		{
			int min = 1;
			int max = 3;
			int testValue = min;
			int result = CLAMP(testValue, min, max);

			Assert::AreEqual(result, min);
		}
		TEST_METHOD(SameAsMax)
		{
			int min = 1;
			int max = 3;
			int testValue = max;
			int result = CLAMP(testValue, min, max);

			Assert::AreEqual(result, max);
		}
		TEST_METHOD(NegativeValues)
		{
			int min = -4;
			int max = -1;
			int testValue = -6;
			int result = CLAMP(testValue, min, max);

			Assert::AreEqual(result, min);
		}
	};

	TEST_CLASS(SafeDelete)
	{
	public:
		TEST_METHOD(NullInteger)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);

			int* pointer = new int(4);
			SAFE_DELETE(pointer);
			Assert::IsNull(pointer);

			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
		TEST_METHOD(NullStdString)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);

			std::string* pointer = new std::string("test");
			SAFE_DELETE(pointer);
			Assert::IsNull(pointer);

			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}

		struct TestStruct
		{
			int myValue = 2;
			std::string myName = "testStruct";
		};
		TEST_METHOD(NullStruct)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);

			TestStruct* p = new TestStruct();
			SAFE_DELETE(p);

			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
		TEST_METHOD(NoCrashIfNullptr)
		{
			int* p = nullptr;
			SAFE_DELETE(p);
		}

		TEST_METHOD(SafeDeleteNativeArray)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);

			int* pArray = new int[5];
			SAFE_DELETE_NATIVE_ARRAY(pArray);

			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
	};
}
