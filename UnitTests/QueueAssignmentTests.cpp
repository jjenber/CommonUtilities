#include "pch.h"
#include "CppUnitTest.h"
#include "..//CommonUtilities/Queue.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace CommonUtilities;

namespace QueueTests
{
	TEST_CLASS(QueueTest)
	{
		TEST_METHOD(Enqueue)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				Queue<std::string> queue;
				Assert::IsTrue(queue.IsEmpty());

				queue.Enqueue("Hello");
				Assert::AreEqual("Hello", queue.GetFront().c_str());

				queue.Enqueue("Hello1");
				Assert::AreEqual("Hello", queue.GetFront().c_str());
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}

		TEST_METHOD(Dequeue)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				Queue<std::string> queue;
				Assert::IsTrue(queue.IsEmpty());

				queue.Enqueue("Hello");
				queue.Enqueue("Hello1");
				queue.Enqueue("Hello2");

				auto value = queue.Dequeue();
				Assert::AreEqual("Hello", value.c_str());
				Assert::AreEqual("Hello1", queue.GetFront().c_str());
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}

		TEST_METHOD(DequeueAll)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				Queue<std::string> queue;
				Assert::IsTrue(queue.IsEmpty());

				queue.Enqueue("Hello");
				queue.Enqueue("Hello1");
				queue.Enqueue("Hello2");

				auto value = queue.Dequeue();
				Assert::AreEqual("Hello", value.c_str());
				value = queue.Dequeue();
				Assert::AreEqual("Hello1", value.c_str());
				value = queue.Dequeue();
				Assert::AreEqual("Hello2", value.c_str());
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}

	};
}