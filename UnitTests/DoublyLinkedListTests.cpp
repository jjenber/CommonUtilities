#include "pch.h"
#include "CppUnitTest.h"

#include "..//CommonUtilities/DoublyLinkedList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using LinkedListInt    = CommonUtilities::DoublyLinkedList<int>;
using LinkedListString = CommonUtilities::DoublyLinkedList<std::string>;

namespace AssignmetDoublyLinkedList
{
	TEST_CLASS(DoublyLinkedListTest)
	{
	public:
		TEST_METHOD(NoMemLeak)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				LinkedListInt list;
				Assert::AreEqual(0, list.GetSize());

				for (int i = 0; i < 10; i++)
				{
					list.InsertFirst(i);
				}
				Assert::AreEqual(10, list.GetSize());
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
				LinkedListString list;
				Assert::AreEqual(0, list.GetSize());

				for (int i = 0; i < 10; i++)
				{
					list.InsertFirst(std::to_string(i));
				}
				Assert::AreEqual(10, list.GetSize());
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
		TEST_METHOD(FindFirst)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				LinkedListInt list;
				Assert::AreEqual(0, list.GetSize());

				for (int i = 0; i < 10; i++)
				{
					list.InsertFirst(i);
				}
				LinkedListInt::Node* found = list.FindFirst(4);
				Assert::IsFalse(found == nullptr);
				Assert::AreEqual(found->GetValue(), 4);
				Assert::AreEqual(10, list.GetSize());
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
		TEST_METHOD(FindFirstString)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				LinkedListString list;
				Assert::AreEqual(0, list.GetSize());

				for (int i = 0; i < 10; i++)
				{
					list.InsertFirst(std::to_string(i));
				}
				LinkedListString::Node* found = list.FindFirst("4");
				Assert::IsFalse(found == nullptr);
				Assert::AreEqual(found->GetValue().c_str(), "4");
				Assert::AreEqual(10, list.GetSize());
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
		TEST_METHOD(FindLast)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				LinkedListInt list;
				Assert::AreEqual(0, list.GetSize());

				for (int i = 0; i < 10; i++)
				{
					list.InsertFirst(i);
				}
				LinkedListInt::Node* found = list.FindLast(4);
				Assert::IsFalse(found == nullptr);
				Assert::AreEqual(found->GetValue(), 4);
				Assert::AreEqual(10, list.GetSize());

			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
		TEST_METHOD(FindLastString)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				LinkedListString list;
				Assert::AreEqual(0, list.GetSize());

				for (int i = 0; i < 10; i++)
				{
					list.InsertFirst(std::to_string(i));
				}
				LinkedListString::Node* found = list.FindLast("4");
				Assert::IsFalse(found == nullptr);
				Assert::AreEqual(found->GetValue().c_str(), "4");
				Assert::AreEqual(10, list.GetSize());

			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
		TEST_METHOD(InsertFirst)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				LinkedListInt list;
				Assert::AreEqual(0, list.GetSize());

				for (int i = 0; i < 10; i++)
				{
					list.InsertFirst(i);
				}
				Assert::AreEqual(list.GetFirst()->GetValue(), 9);
				Assert::AreEqual(list.GetLast()->GetValue(), 0);
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
		TEST_METHOD(InsertFirstString)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				LinkedListString list;
				Assert::AreEqual(0, list.GetSize());

				for (int i = 0; i < 10; i++)
				{
					list.InsertFirst(std::to_string(i));
				}
				Assert::AreEqual(10, list.GetSize());
				Assert::AreEqual(list.GetFirst()->GetValue().c_str(), "9");
				Assert::AreEqual(list.GetLast()->GetValue().c_str(), "0");
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}

		TEST_METHOD(InsertLast)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				LinkedListInt list;
				Assert::AreEqual(0, list.GetSize());

				for (int i = 0; i < 10; i++)
				{
					list.InsertLast(i);
				}
				Assert::AreEqual(list.GetFirst()->GetValue(), 0);
				Assert::AreEqual(list.GetLast()->GetValue(), 9);
				Assert::AreEqual(10, list.GetSize());

			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
		TEST_METHOD(InsertLastString)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				LinkedListString list;
				Assert::AreEqual(0, list.GetSize());

				for (int i = 0; i < 10; i++)
				{
					list.InsertLast(std::to_string(i));
				}
				Assert::AreEqual(10, list.GetSize());
				Assert::AreEqual(list.GetFirst()->GetValue().c_str(), "0");
				Assert::AreEqual(list.GetLast()->GetValue().c_str(), "9");
			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}

		TEST_METHOD(InsertBefore)
		{
			LinkedListString list;
			Assert::AreEqual(0, list.GetSize());

			for (int i = 0; i < 10; i++)
			{
				list.InsertLast(std::to_string(i));
			}
			// First
			LinkedListString::Node* insertBeforeNode = list.FindFirst("5");
			list.InsertBefore(insertBeforeNode, "Inserted");
			Assert::AreEqual(insertBeforeNode->GetValue().c_str(), "5");
			Assert::AreEqual(insertBeforeNode->GetNext()->GetValue().c_str(), "6");
			Assert::AreEqual(insertBeforeNode->GetPrevious()->GetValue().c_str(), "Inserted");

			// middle
			insertBeforeNode = list.FindFirst("0");
			list.InsertBefore(insertBeforeNode, "Inserted");
			Assert::AreEqual(insertBeforeNode->GetValue().c_str(), "0");
			Assert::AreEqual(insertBeforeNode->GetNext()->GetValue().c_str(), "1");
			Assert::AreEqual(insertBeforeNode->GetPrevious()->GetValue().c_str(), "Inserted");

			// Last
			insertBeforeNode = list.GetLast();
			list.InsertBefore(insertBeforeNode, "Inserted");
			Assert::AreEqual("9", insertBeforeNode->GetValue().c_str());
			Assert::AreEqual("9", list.GetLast()->GetValue().c_str());
			Assert::IsNull(insertBeforeNode->GetNext());
			Assert::AreEqual("Inserted", insertBeforeNode->GetPrevious()->GetValue().c_str());

			Assert::AreEqual(13, list.GetSize());

		}
		TEST_METHOD(InsertAfter)
		{
			LinkedListString list;
			Assert::AreEqual(0, list.GetSize());

			for (int i = 0; i < 10; i++)
			{
				list.InsertLast(std::to_string(i));
			}

			LinkedListString::Node* insertAfterNode = list.FindFirst("5");
			list.InsertAfter(insertAfterNode, "Inserted");
			Assert::AreEqual(insertAfterNode->GetValue().c_str(), "5");
			Assert::AreEqual(insertAfterNode->GetPrevious()->GetValue().c_str(), "4");
			Assert::AreEqual(insertAfterNode->GetNext()->GetValue().c_str(), "Inserted");

			insertAfterNode = list.FindFirst("0");
			list.InsertAfter(insertAfterNode, "Inserted");
			Assert::AreEqual(insertAfterNode->GetValue().c_str(), "0");
			Assert::IsNull(insertAfterNode->GetPrevious());
			Assert::AreEqual("Inserted", insertAfterNode->GetNext()->GetValue().c_str());

			insertAfterNode = list.FindFirst("9");
			list.InsertAfter(insertAfterNode, "Inserted");
			Assert::AreEqual(insertAfterNode->GetValue().c_str(), "9");
			Assert::AreEqual(insertAfterNode->GetPrevious()->GetValue().c_str(), "8");
			Assert::AreEqual(insertAfterNode->GetNext()->GetValue().c_str(), "Inserted");
			Assert::AreEqual(list.GetLast()->GetValue().c_str(), "Inserted");

			Assert::AreEqual(13, list.GetSize());

		}
		TEST_METHOD(Remove)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				LinkedListString list;
				Assert::AreEqual(0, list.GetSize());

				for (int i = 0; i < 10; i++)
				{
					list.InsertLast(std::to_string(i));
				}
				Assert::AreEqual(10, list.GetSize());
				
				Assert::AreEqual(list.GetLast()->GetValue().c_str(), "9");
				Assert::AreEqual(list.GetFirst()->GetValue().c_str(), "0");
				
				list.Remove(list.GetFirst());
				Assert::AreEqual(list.GetFirst()->GetValue().c_str(), "1");
				Assert::AreEqual(list.GetLast()->GetValue().c_str(), "9");
				
				list.Remove(list.GetLast());
				Assert::AreEqual(list.GetFirst()->GetValue().c_str(), "1");
				Assert::AreEqual(list.GetLast()->GetValue().c_str(), "8");

				LinkedListString::Node* middle = list.FindFirst("5");
				list.Remove(middle);
				auto fourth = list.FindFirst("4");

				Assert::AreEqual("6",fourth->GetNext()->GetValue().c_str());

				Assert::AreEqual(7, list.GetSize());

			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}

		TEST_METHOD(RemoveFirst)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				LinkedListString list;
				Assert::AreEqual(0, list.GetSize());

				for (int i = 0; i < 10; i++)
				{
					list.InsertLast(std::to_string(i));
				}
				Assert::AreEqual(10, list.GetSize());

				// First
				list.RemoveFirst("0");
				Assert::AreEqual(list.GetFirst()->GetValue().c_str(), "1");
				Assert::AreEqual(list.GetLast()->GetValue().c_str(), "9");

				// Middle
				list.RemoveFirst("5");
				Assert::AreEqual(list.GetFirst()->GetValue().c_str(), "1");
				Assert::AreEqual("6", list.FindFirst("4")->GetNext()->GetValue().c_str());
				Assert::AreEqual(list.GetLast()->GetValue().c_str(), "9");

				// Last
				list.RemoveFirst("9");
				Assert::AreEqual("8", list.GetLast()->GetValue().c_str());
				Assert::AreEqual("7", list.GetLast()->GetPrevious()->GetValue().c_str());
				Assert::IsNull(list.GetLast()->GetNext());

				Assert::AreEqual(7, list.GetSize());

			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
		TEST_METHOD(RemoveLast)
		{
			_CrtMemState memStart;
			_CrtMemState memEnd;
			_CrtMemState memDiff;
			_CrtMemCheckpoint(&memStart);
			{
				LinkedListString list;
				Assert::AreEqual(0, list.GetSize());

				for (int i = 0; i < 10; i++)
				{
					list.InsertLast(std::to_string(i));
				}
				Assert::AreEqual(10, list.GetSize());

				// First
				list.RemoveLast("0");
				Assert::AreEqual(list.GetFirst()->GetValue().c_str(), "1");
				Assert::AreEqual(list.GetLast()->GetValue().c_str(), "9");

				// Middle
				list.RemoveLast("5");
				Assert::AreEqual(list.GetFirst()->GetValue().c_str(), "1");
				Assert::AreEqual("6", list.FindFirst("4")->GetNext()->GetValue().c_str());
				Assert::AreEqual(list.GetLast()->GetValue().c_str(), "9");

				// Last
				list.RemoveLast("9");
				Assert::AreEqual("8", list.GetLast()->GetValue().c_str());
				Assert::AreEqual("7", list.GetLast()->GetPrevious()->GetValue().c_str());
				Assert::IsNull(list.GetLast()->GetNext());

				Assert::AreEqual(7, list.GetSize());

			}
			_CrtMemCheckpoint(&memEnd);
			Assert::IsFalse(_CrtMemDifference(&memDiff, &memStart, &memEnd), L"There is a memory leak!");
		}
	};
}
