#include "pch.h"
#include "CppUnitTest.h"

#include "Shared\UtilityFunctions.hpp"
#include <Collections/Queue.h>
#include <vector>

//#define RUN_CRASH_TESTS 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using Queuef = CommonUtilities::Queue<float>;

namespace Assignment2StackandQueue
{
	TEST_CLASS(QueueTests)
	{
	public:

		TEST_METHOD(Q_Constructor)
		{
			Queuef queue;

			Assert::AreEqual(0, queue.GetSize(), L"The size of an empty queue should be zero.");
		}

		TEST_METHOD(Q_Enqueue_GetSize)
		{
			Queuef queue;

			for (int i = 0; i < 60; ++i)
			{
				Assert::AreEqual(i, queue.GetSize(), L"GetSize() does not return the correct stack size.");
				queue.Enqueue(static_cast<float>(i));
			}

			for (int i = 0; i < 600; ++i)
			{
				queue.Enqueue(static_cast<float>(i));
			}

			Assert::AreEqual(660, queue.GetSize(), L"GetSize() does not return the correct stack size.");
		}

		TEST_METHOD(Q_GetFront)
		{
			Queuef queue;

			float rng = TestUtility::GetRandomFloat();
			queue.Enqueue(rng);

			for (int i = 0; i < 60; ++i)
			{
				queue.Enqueue(TestUtility::GetRandomFloat());
				Assert::AreEqual(rng, queue.GetFront(), L"GetFront() does not return the correct value.");
			}
		}

		TEST_METHOD(Q_GetFront_Const)
		{
			Queuef queue;
			const Queuef& constQueue = queue;
			constQueue;
			float rng = TestUtility::GetRandomFloat();
			queue.Enqueue(rng);

			for (int i = 0; i < 60; ++i)
			{
				queue.Enqueue(TestUtility::GetRandomFloat());
				Assert::AreEqual(rng, queue.GetFront(), L"GetFront() does not return the correct value.");
			}
		}

		TEST_METHOD(Q_Dequeue)
		{
			Queuef queue;
			std::vector<float> control;

			for (int i = 0; i < 60; ++i)
			{
				queue.Enqueue(static_cast<float>(i));
			}

			for (int i = 0; i < 60; ++i)
			{
				float rng = TestUtility::GetRandomFloat();
				queue.Enqueue(rng);
				control.push_back(rng);
			}

			for (int i = 0; i < 60; ++i)
			{
				Assert::AreEqual(static_cast<float>(i), queue.Dequeue(), L"Dequeue() does not return the expected value.");
			}

			for (int i = 0; i < 60; ++i)
			{
				Assert::AreEqual(control.at(i), queue.Dequeue(), L"Dequeue() does not return the expected value.");
			}
		}
#ifdef RUN_CRASH_TESTS
		TEST_METHOD(Q_SHOULDCRASH_Dequeue_Empty)
		{
			Queuef queue;
			queue.Dequeue();
		}

		TEST_METHOD(Q_SHOULDCRASH_Dequeue)
		{
			Queuef queue;

			for (int i = 0; i < 60; ++i)
			{
				queue.Enqueue(static_cast<float>(i));
			}

			for (int i = 0; i < 61; ++i)
			{
				queue.Dequeue();
			}
		}

		TEST_METHOD(Q_SHOULDCRASH_GetFront)
		{
			Queuef queue;

			queue.GetFront();
		}

		TEST_METHOD(Q_SHOULDCRASH_GetFront_Const)
		{
			const Queuef queue;

			queue.GetFront();
		}
#endif // RUN_CRASH_TESTS
	};
}