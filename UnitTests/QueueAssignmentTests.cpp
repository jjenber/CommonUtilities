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
		TEST_METHOD(EnqueueFromDequeue)
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
				queue.Enqueue("Hello2");

				auto value = queue.Dequeue(); // Hello
				Assert::AreEqual("Hello1", queue.GetFront().c_str());
				Assert::AreEqual("Hello", value.c_str());
				value = queue.Dequeue(); // Hello1
				Assert::AreEqual("Hello1", value.c_str());

				queue.Enqueue("Hello3");
				Assert::AreEqual("Hello2", queue.GetFront().c_str());

				while (!queue.IsEmpty())
				{
					auto v = queue.Dequeue();
				}

				Assert::IsTrue(queue.IsEmpty());

				queue.Enqueue("Hello");
				Assert::AreEqual("Hello", queue.GetFront().c_str());
				queue.Enqueue("Hello1");
				Assert::AreEqual("Hello", queue.GetFront().c_str());
				queue.Enqueue("Hello2");

				value = queue.Dequeue(); // Hello
				Assert::AreEqual("Hello1", queue.GetFront().c_str());
				value = queue.Dequeue(); // Hello1

				queue.Enqueue("Hello3");
				Assert::AreEqual("Hello2", queue.GetFront().c_str());
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

		TEST_METHOD(TestGrowing)
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
				queue.Enqueue("Hello3");

				auto value = queue.Dequeue(); // Hello
				Assert::AreEqual("Hello", value.c_str());
				value = queue.Dequeue();
				Assert::AreEqual("Hello1", value.c_str());
				int i = 0;
				while (i < 10)
				{
					i++;
					queue.Enqueue(std::to_string(i));
				}
				Assert::AreEqual("Hello2", queue.GetFront().c_str());
				i = 0;
				while (i < 2)
				{
					i++;
					queue.Dequeue();
				}
				while (i < 50)
				{
					queue.Enqueue(std::to_string(i++));
				}
				Assert::AreEqual("1", queue.GetFront().c_str());
				value = queue.Dequeue();
				Assert::AreEqual("1", value.c_str());
				value = queue.Dequeue();
				Assert::AreEqual("2", value.c_str());

			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
	};
}