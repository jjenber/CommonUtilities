#include "CppUnitTest.h"
#include <vector>

#include "Shared/UtilityFunctions.hpp"
#include "..//CommonUtilities/DoublyLinkedList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using DLListf = CommonUtilities::DoublyLinkedList<float>;
using DLListNodef = CommonUtilities::DoublyLinkedListNode<float>;

namespace Assignment1DoublyLinkedList
{		
	TEST_CLASS(DoublyLinkedListTests)
	{
	public:		
		TEST_METHOD(DefaultConstructor)
		{
			DLListf list;

			Assert::IsNull(list.GetFirst(), L"A default list should have no nodes and GetFirst() should return null.");
			Assert::IsNull(list.GetLast(), L"A default list should have no nodes and GetLast() should return null.");
			Assert::AreEqual(0, list.GetSize(), L"A default list should return the size 0.");
		}

		TEST_METHOD(InsertFirst)
		{
			DLListf smallList;
			smallList.InsertFirst(3.f);

			Assert::AreEqual(3.f, smallList.GetFirst()->GetValue(), L"GetFirst() returns the wrong value from the list { 3 }.");
			Assert::AreEqual(3.f, smallList.GetLast()->GetValue(), L"GetLast() returns the wrong value from the list { 3 }.");
			Assert::AreEqual(1, smallList.GetSize(), L"The list { 3 } should return the size 1.");

			smallList.InsertFirst(4.f);

			Assert::AreEqual(4.f, smallList.GetFirst()->GetValue(), L"GetFirst() returns the wrong value from the list { 4, 3 }.");
			Assert::AreEqual(3.f, smallList.GetLast()->GetValue(), L"GetLast() returns the wrong value from the list { 4, 3 }.");
			Assert::AreEqual(2, smallList.GetSize(), L"The list { 4, 3 } should return the size 2.");

			DLListf largeList;
			std::vector<float> vector;

			for (int i = 0; i < 1000; ++i)
			{
				float rndFloat = TestUtility::GetRandomFloat();
				largeList.InsertFirst(rndFloat);
				vector.insert(vector.begin(), rndFloat);
			}

			Assert::AreEqual(static_cast<int>(vector.size()), largeList.GetSize(), L"List size is not equal to control sequence size.");
			DLListNodef* node = largeList.GetFirst();

			for (int i = 0; i < static_cast<int>(vector.size()); ++i)
			{
				Assert::AreEqual(vector[i], node->GetValue(), L"List sequence does not match control sequence.");
				node = node->GetNext();
			}
		}

		TEST_METHOD(InsertLast)
		{
			DLListf smallList;
			smallList.InsertLast(3.f);

			Assert::AreEqual(3.f, smallList.GetFirst()->GetValue(), L"GetFirst() returns the wrong value from the list { 3 }.");
			Assert::AreEqual(3.f, smallList.GetLast()->GetValue(), L"GetLast() returns the wrong value from the list { 3 }.");
			Assert::AreEqual(1, smallList.GetSize(), L"The list { 3 } should return the size 1.");

			smallList.InsertLast(4.f);

			Assert::AreEqual(3.f, smallList.GetFirst()->GetValue(), L"GetFirst() returns the wrong value from the list { 3, 4 }.");
			Assert::AreEqual(4.f, smallList.GetLast()->GetValue(), L"GetLast() returns the wrong value from the list { 3, 4 }.");
			Assert::AreEqual(2, smallList.GetSize(), L"The list { 4, 3 } should return the size 2.");

			DLListf largeList;
			std::vector<float> vector;

			for (int i = 0; i < 1000; ++i)
			{
				float rndFloat = TestUtility::GetRandomFloat();
				largeList.InsertLast(rndFloat);
				vector.push_back(rndFloat);
			}

			Assert::AreEqual(static_cast<int>(vector.size()), largeList.GetSize(), L"List size is not equal to control sequence size.");
			DLListNodef* node = largeList.GetFirst();

			for (int i = 0; i < static_cast<int>(vector.size()); ++i)
			{
				Assert::AreEqual(vector[i], node->GetValue(), L"List sequence does not match control sequence.");
				node = node->GetNext();
			}
		}

		/*TEST_METHOD(RemoveFirst)
		{
			DLListf largeList;
			std::vector<float> vector = {};

			// Fill list and control sequence.
			for (int i = 0; i < 1000; ++i)
			{
				float rndFloat = TestUtility::GetRandomFloat();
				largeList.InsertLast(rndFloat);
				vector.push_back(rndFloat);
			}

			// Remove elements from list.
			int removed = 0;
			for (; removed < 10; ++removed)
			{
				Assert::IsTrue(largeList.RemoveFirst(), L"RemoveFirst() failed unexpectedly.");
			}

			// Make sure list size is correct and that the remaining values are correct.
			Assert::AreEqual(static_cast<int>(vector.size()) - removed, largeList.GetSize(), L"List size is incorrect after several RemoveFirst().");
			DLListNodef* node = largeList.GetFirst();
			for (int j = removed; j < static_cast<int>(vector.size()); ++j)
			{
				Assert::AreEqual(vector[j], node->GetValue(), L"List differs from control sequence after several RemoveFirst().");
				node = node->GetNext();
			}

			// Remove all items and try removal from empty list.
			DLListf smallList;
			smallList.InsertLast(1.f);
			smallList.InsertLast(2.f);
			smallList.InsertLast(3.f);

			Assert::IsTrue(smallList.RemoveFirst(), L"RemoveFirst() failed unexpectedly.");
			Assert::IsTrue(smallList.RemoveFirst(), L"RemoveFirst() failed unexpectedly.");
			Assert::IsTrue(smallList.RemoveFirst(), L"RemoveFirst() failed unexpectedly.");
			Assert::IsFalse(smallList.RemoveFirst(), L"RemoveFirst() on empty list did not fail as it should have done.");
		}

		TEST_METHOD(RemoveLast)
		{
			DLListf largeList;
			std::vector<float> vector = {};

			// Fill list and control sequence.
			for (int i = 0; i < 1000; ++i)
			{
				float rndFloat = TestUtility::GetRandomFloat();
				largeList.InsertLast(rndFloat);
				vector.push_back(rndFloat);
			}

			// Remove elements from list.
			int removed = 0;
			for (; removed < 10; ++removed)
			{
				Assert::IsTrue(largeList.RemoveLast(), L"RemoveLast() failed unexpectedly.");
			}

			// Make sure list size is correct and that the remaining values are correct.
			Assert::AreEqual(static_cast<int>(vector.size()) - removed, largeList.GetSize(), L"List size is incorrect after several RemoveLast().");
			DLListNodef* node = largeList.GetFirst();
			for (int j = 0; j < static_cast<int>(vector.size()) - removed; ++j)
			{
				Assert::AreEqual(vector[j], node->GetValue(), L"List differs from control sequence after several RemoveLast().");
				node = node->GetNext();
			}

			// Remove all items and try removal from empty list.
			DLListf smallList;
			smallList.InsertLast(1.f);
			smallList.InsertLast(2.f);
			smallList.InsertLast(3.f);

			Assert::IsTrue(smallList.RemoveLast(), L"RemoveLast() failed unexpectedly.");
			Assert::IsTrue(smallList.RemoveLast(), L"RemoveLast() failed unexpectedly.");
			Assert::IsTrue(smallList.RemoveLast(), L"RemoveLast() failed unexpectedly.");
			Assert::IsFalse(smallList.RemoveLast(), L"RemoveLast() on empty list did not fail as it should have done.");
		}*/

		TEST_METHOD(GetSize)
		{
			DLListf list1;
			DLListf list2;

			for (int i = 1; i <= 1000; ++i)
			{
				list1.InsertFirst(TestUtility::GetRandomFloat());

				Assert::AreEqual(i, list1.GetSize(), L"The size is incorrect after InsertFirst().");
			}

			/*for (int i = 1000; i >= 0; --i)
			{
				Assert::AreEqual(i, list1.GetSize(), L"The size is incorrect after RemoveFirst().");
				list1.RemoveFirst();
			}*/

			for (int j = 1; j <= 1000; ++j)
			{
				list2.InsertLast(TestUtility::GetRandomFloat());

				Assert::AreEqual(j, list2.GetSize(), L"The size is incorrect after InsertLast().");
			}

			/*for (int i = 1000; i >= 0; --i)
			{
				Assert::AreEqual(i, list2.GetSize(), L"The size is incorrect after RemoveLast().");
				list2.RemoveLast();
			}*/
		}

		TEST_METHOD(FindFirst)
		{
			DLListf list;					// list: { 1, 11, 2, 12, 3, 4, 11, 5, 12, 6, 7, 11, 8, 12, 9, 12, 10 }
			list.InsertLast(1.f);
			list.InsertLast(11.f);
			list.InsertLast(2.f);
			list.InsertLast(12.f);
			list.InsertLast(3.f);
			list.InsertLast(4.f);
			list.InsertLast(11.f);
			list.InsertLast(5.f);
			list.InsertLast(12.f);
			list.InsertLast(6.f);
			list.InsertLast(7.f);
			list.InsertLast(11.f);
			list.InsertLast(8.f);
			list.InsertLast(12.f);
			list.InsertLast(9.f);
			list.InsertLast(12.f);
			list.InsertLast(10.f);

			DLListNodef* node = list.FindFirst(1.f);
			Assert::IsTrue(list.GetFirst() == node, L"FindFirst failed to return the correct node when it was the first.");

			node = list.FindFirst(10.f);
			Assert::IsTrue(list.GetLast() == node, L"FindFirst failed to return the correct node when it was the last.");

			node = list.FindFirst(11.f);
			Assert::AreEqual(11.f, node->GetValue(), L"FindFirst returned a node with an incorrect value.");
			Assert::AreEqual(1.f, node->GetPrevious()->GetValue(), L"FindFirst returned a node with an incorrect value for the previous node.");
			Assert::AreEqual(2.f, node->GetNext()->GetValue(), L"FindFirst returned a node with an incorrect value for the next node.");

			node = list.FindFirst(12.f);
			Assert::AreEqual(12.f, node->GetValue(), L"FindFirst returned a node with an incorrect value.");
			Assert::AreEqual(2.f, node->GetPrevious()->GetValue(), L"FindFirst returned a node with an incorrect value for the previous node.");
			Assert::AreEqual(3.f, node->GetNext()->GetValue(), L"FindFirst returned a node with an incorrect value for the next node.");

			node = list.FindFirst(20.f);
			Assert::IsNull(node, L"FindFirst did not return nullptr when not finding the value.");
		}

		TEST_METHOD(FindLast)
		{
			DLListf list;					// list: { 1, 11, 2, 12, 3, 4, 11, 5, 12, 6, 7, 11, 8, 12, 9, 12, 10 }
			list.InsertLast(1.f);
			list.InsertLast(11.f);
			list.InsertLast(2.f);
			list.InsertLast(12.f);
			list.InsertLast(3.f);
			list.InsertLast(4.f);
			list.InsertLast(11.f);
			list.InsertLast(5.f);
			list.InsertLast(12.f);
			list.InsertLast(6.f);
			list.InsertLast(7.f);
			list.InsertLast(11.f);
			list.InsertLast(8.f);
			list.InsertLast(12.f);
			list.InsertLast(9.f);
			list.InsertLast(12.f);
			list.InsertLast(10.f);

			DLListNodef* node = list.FindLast(1.f);
			Assert::IsTrue(list.GetFirst() == node, L"FindLast failed to return the correct node when it was the first.");

			node = list.FindLast(10.f);
			Assert::IsTrue(list.GetLast() == node, L"FindLast failed to return the correct node when it was the last.");

			node = list.FindLast(11.f);
			Assert::AreEqual(11.f, node->GetValue(), L"FindLast returned a node with an incorrect value.");
			Assert::AreEqual(7.f, node->GetPrevious()->GetValue(), L"FindLast returned a node with an incorrect value for the previous node.");
			Assert::AreEqual(8.f, node->GetNext()->GetValue(), L"FindLast returned a node with an incorrect value for the next node.");

			node = list.FindLast(12.f);
			Assert::AreEqual(12.f, node->GetValue(), L"FindLast returned a node with an incorrect value.");
			Assert::AreEqual(9.f, node->GetPrevious()->GetValue(), L"FindLast returned a node with an incorrect value for the previous node.");
			Assert::AreEqual(10.f, node->GetNext()->GetValue(), L"FindLast returned a node with an incorrect value for the next node.");

			node = list.FindLast(20.f);
			Assert::IsNull(node, L"FindLast did not return nullptr when not finding the value.");
		}

		TEST_METHOD(InsertBefore)
		{
			DLListf list;					// list: { 1, 11, 2, 12, 3, 4, 11, 5, 12, 6, 7, 11, 8, 12, 9, 12, 10 }
			list.InsertLast(1.f);
			list.InsertLast(11.f);
			list.InsertLast(2.f);
			list.InsertLast(12.f);
			list.InsertLast(3.f);
			list.InsertLast(4.f);
			list.InsertLast(11.f);
			list.InsertLast(5.f);
			list.InsertLast(12.f);
			list.InsertLast(6.f);
			list.InsertLast(7.f);
			list.InsertLast(11.f);
			list.InsertLast(8.f);
			list.InsertLast(12.f);
			list.InsertLast(9.f);
			list.InsertLast(12.f);
			list.InsertLast(10.f);

			list.InsertBefore(list.GetFirst(), 0.f);		// list: { 0, 1, 11, 2, 12, 3, 4, 11, 5, 12, 6, 7, 11, 8, 12, 9, 12, 10 }
			Assert::AreEqual(0.f, list.GetFirst()->GetValue(), L"InsertBefore first node in the list does not result in the value being the new first value in the list");

			list.InsertBefore(list.GetLast(), 0.f);			// list: { 0, 1, 11, 2, 12, 3, 4, 11, 5, 12, 6, 7, 11, 8, 12, 9, 12, 10, 0 }
			Assert::AreEqual(0.f, list.GetLast()->GetPrevious()->GetValue(), L"InsertBefore last node in the list does not result in the value being the new next to last value in the list");

			DLListNodef* node = list.FindFirst(11.f);
			list.InsertBefore(node, -1.f);					// list: { 0, 1, -1, 11, 2, 12, 3, 4, 11, 5, 12, 6, 7, 11, 8, 12, 9, 12, 10 }
			Assert::AreEqual(-1.f, node->GetPrevious()->GetValue(), L"InsertBefore a node found with FindFirst does not result in the value being inserted before the found node.");
			Assert::AreEqual(1.f, node->GetPrevious()->GetPrevious()->GetValue(), L"InsertBefore a node found with FindFirst does not result in correct value for the previous node.");

			node = list.FindLast(11.f);
			list.InsertBefore(node, -1.f);					// list: { 0, 1, -1, 11, 2, 12, 3, 4, 11, 5, 12, 6, 7, -1, 11, 8, 12, 9, 12, 10 }
			Assert::AreEqual(-1.f, node->GetPrevious()->GetValue(), L"InsertBefore a node found with FindLast does not result in the value being inserted before the found node.");
			Assert::AreEqual(7.f, node->GetPrevious()->GetPrevious()->GetValue(), L"InsertBefore a node found with FindLast does not result in correct value for the previous node.");

			node = list.FindFirst(12.f);
			list.InsertBefore(node, -1.f);					// list: { 0, 1, -1, 11, 2, -1, 12, 3, 4, 11, 5, 12, 6, 7, -1, 11, 8, 12, 9, 12, 10 }
			Assert::AreEqual(-1.f, node->GetPrevious()->GetValue(), L"InsertBefore a node found with FindLast does not result in the value being inserted before the found node.");
			Assert::AreEqual(2.f, node->GetPrevious()->GetPrevious()->GetValue(), L"InsertBefore a node found with FindFirst does not result in correct value for the previous node.");

			node = list.FindLast(12.f);
			list.InsertBefore(node, -1.f);					// list: { 0, 1, -1, 11, 2, -1, 12, 3, 4, 11, 5, 12, 6, 7, -1, 11, 8, 12, 9, -1, 12, 10 }
			Assert::AreEqual(-1.f, node->GetPrevious()->GetValue(), L"InsertBefore a node found with FindLast does not result in the value being inserted before the found node.");
			Assert::AreEqual(9.f, node->GetPrevious()->GetPrevious()->GetValue(), L"InsertBefore a node found with FindLast does not result in correct value for the previous node.");
		}

		TEST_METHOD(InsertAfter)
		{
			DLListf list;					// list: { 1, 11, 2, 12, 3, 4, 11, 5, 12, 6, 7, 11, 8, 12, 9, 12, 10 }
			list.InsertLast(1.f);
			list.InsertLast(11.f);
			list.InsertLast(2.f);
			list.InsertLast(12.f);
			list.InsertLast(3.f);
			list.InsertLast(4.f);
			list.InsertLast(11.f);
			list.InsertLast(5.f);
			list.InsertLast(12.f);
			list.InsertLast(6.f);
			list.InsertLast(7.f);
			list.InsertLast(11.f);
			list.InsertLast(8.f);
			list.InsertLast(12.f);
			list.InsertLast(9.f);
			list.InsertLast(12.f);
			list.InsertLast(10.f);

			list.InsertAfter(list.GetFirst(), 0.f);			// list: { 1, 0, 11, 2, 12, 3, 4, 11, 5, 12, 6, 7, 11, 8, 12, 9, 12, 10 }
			Assert::AreEqual(0.f, list.GetFirst()->GetNext()->GetValue(), L"InsertAfter first node in the list does not result in the value being the new first value in the list");

			list.InsertAfter(list.GetLast(), 0.f);			// list: { 1, 0, 11, 2, 12, 3, 4, 11, 5, 12, 6, 7, 11, 8, 12, 9, 12, 10, 0 }
			Assert::AreEqual(0.f, list.GetLast()->GetValue(), L"InsertAfter last node in the list does not result in the value being the new last value in the list");

			DLListNodef* node = list.FindFirst(11.f);
			list.InsertAfter(node, -1.f);					// list: { 1, 0, 11, -1, 2, 12, 3, 4, 11, 5, 12, 6, 7, 11, 8, 12, 9, 12, 10, 0 }
			Assert::AreEqual(-1.f, node->GetNext()->GetValue(), L"InsertAfter a node found with FindFirst does not result in the value being inserted before the found node.");
			Assert::AreEqual(2.f, node->GetNext()->GetNext()->GetValue(), L"InsertAfter a node found with FindFirst does not result in correct value for the next node.");

			node = list.FindLast(11.f);
			list.InsertAfter(node, -1.f);					// list: { 1, 0, 11, -1, 2, 12, 3, 4, 11, 5, 12, 6, 7, 11, -1, 8, 12, 9, 12, 10, 0 }
			Assert::AreEqual(-1.f, node->GetNext()->GetValue(), L"InsertAfter a node found with FindLast does not result in the value being inserted before the found node.");
			Assert::AreEqual(8.f, node->GetNext()->GetNext()->GetValue(), L"InsertAfter a node found with FindLast does not result in correct value for the next node.");

			node = list.FindFirst(12.f);
			list.InsertAfter(node, -1.f);					// list: { 1, 0, 11, -1, 2, 12, -1, 3, 4, 11, 5, 12, 6, 7, 11, -1, 8, 12, 9, 12, 10, 0 }
			Assert::AreEqual(-1.f, node->GetNext()->GetValue(), L"InsertAfter a node found with FindFirst does not result in the value being inserted before the found node.");
			Assert::AreEqual(3.f, node->GetNext()->GetNext()->GetValue(), L"InsertAfter a node found with FindFirst does not result in correct value for the next node.");

			node = list.FindLast(12.f);
			list.InsertAfter(node, -1.f);					// list: { 1, 0, 11, -1, 2, 12, -1, 3, 4, 11, 5, 12, 6, 7, 11, -1, 8, 12, 9, 12, -1, 10, 0 }
			Assert::AreEqual(-1.f, node->GetNext()->GetValue(), L"InsertAfter a node found with FindLast does not result in the value being inserted before the found node.");
			Assert::AreEqual(10.f, node->GetNext()->GetNext()->GetValue(), L"InsertAfter a node found with FindLast does not result in correct value for the next node.");
		}

		TEST_METHOD(Remove)
		{
			DLListf list;					// list: { 1, 11, 2, 12, 3, 4, 11, 5, 12, 6, 7, 11, 8, 12, 9, 12, 10 }
			list.InsertLast(1.f);
			list.InsertLast(11.f);
			list.InsertLast(2.f);
			list.InsertLast(12.f);
			list.InsertLast(3.f);
			list.InsertLast(4.f);
			list.InsertLast(11.f);
			list.InsertLast(5.f);
			list.InsertLast(12.f);
			list.InsertLast(6.f);
			list.InsertLast(7.f);
			list.InsertLast(11.f);
			list.InsertLast(8.f);
			list.InsertLast(12.f);
			list.InsertLast(9.f);
			list.InsertLast(12.f);
			list.InsertLast(10.f);

			list.Remove(list.GetFirst());					// list: { 11, 2, 12, 3, 4, 11, 5, 12, 6, 7, 11, 8, 12, 9, 12, 10 }
			Assert::AreEqual(11.f, list.GetFirst()->GetValue(), L"Removing the first node in the list results in an incorrect value for the new first node.");

			list.Remove(list.GetLast());					// list: { 11, 2, 12, 3, 4, 11, 5, 12, 6, 7, 11, 8, 12, 9, 12 }
			Assert::AreEqual(12.f, list.GetLast()->GetValue(), L"Removing the last node in the list results in an incorrect value for the new last node.");

			DLListNodef* node = list.FindFirst(11.f);
			list.Remove(node);								// list: { 2, 12, 3, 4, 11, 5, 12, 6, 7, 11, 8, 12, 9, 12 }
			Assert::AreEqual(2.f, list.GetFirst()->GetValue(), L"Finding and removing the first node in the list results in an incorrect value for the new first node.");

			node = list.FindFirst(12.f);
			list.Remove(node);								// list: { 2, 3, 4, 11, 5, 12, 6, 7, 11, 8, 12, 9, 12 }
			Assert::AreEqual(2.f, list.GetFirst()->GetValue(), L"Finding a value and removing the node results in an incorrect value for the previous node.");
			Assert::AreEqual(3.f, list.GetFirst()->GetNext()->GetValue(), L"Finding a value and removing the node results in an incorrect next value.");

			node = list.FindFirst(11.f);
			DLListNodef* prevNode = node->GetPrevious();
			list.Remove(node);								// list: { 2, 3, 4, 5, 12, 6, 7, 11, 8, 12, 9, 12 }
			Assert::AreEqual(4.f, prevNode->GetValue(), L"Finding a value and removing the node results in an incorrect value for the previous node.");
			Assert::AreEqual(5.f, prevNode->GetNext()->GetValue(), L"Finding a value and removing the node results in an incorrect value for the previous node.");

			node = list.FindLast(12.f);
			list.Remove(node);								// list: { 2, 3, 4, 5, 12, 6, 7, 11, 8, 12, 9 }
			Assert::AreEqual(9.f, list.GetLast()->GetValue(), L"Finding and removing the last node in the list results in an incorrect value for the new last node.");

			node = list.FindLast(12.f);
			prevNode = node->GetPrevious();
			list.Remove(node);								// list: { 2, 3, 4, 5, 12, 6, 7, 11, 8, 9 }
			Assert::AreEqual(8.f, prevNode->GetValue(), L"Finding a value and removing the node results in an incorrect value for the previous node.");
			Assert::AreEqual(9.f, prevNode->GetNext()->GetValue(), L"Finding a value and removing the node results in an incorrect value for the previous node.");
		}

		TEST_METHOD(RemoveFirstOccurrence)
		{
			DLListf list;					// list: { 1, 11, 2, 12, 3, 4, 11, 5, 12, 6, 7, 11, 8, 12, 9, 12, 10 }
			list.InsertLast(1.f);
			list.InsertLast(11.f);
			list.InsertLast(2.f);
			list.InsertLast(12.f);
			list.InsertLast(3.f);
			list.InsertLast(4.f);
			list.InsertLast(11.f);
			list.InsertLast(5.f);
			list.InsertLast(12.f);
			list.InsertLast(6.f);
			list.InsertLast(7.f);
			list.InsertLast(11.f);
			list.InsertLast(8.f);
			list.InsertLast(12.f);
			list.InsertLast(9.f);
			list.InsertLast(12.f);
			list.InsertLast(10.f);

			// list: { 1, 2, 12, 3, 4, 11, 5, 12, 6, 7, 11, 8, 12, 9, 12, 10 }
			Assert::IsTrue(list.RemoveFirst(11.f), L"RemoveFirst(value) failed unexpectedly.");
			Assert::AreEqual(1.f, list.GetFirst()->GetValue(), L"RemoveFirst(value) results in the wrong previous value.");
			Assert::AreEqual(2.f, list.GetFirst()->GetNext()->GetValue(), L"RemoveFirst(value) results in the wrong next value.");

			// list: { 1, 2, 12, 3, 4, 5, 12, 6, 7, 11, 8, 12, 9, 12, 10 }
			DLListNodef* node = list.FindFirst(11.f)->GetPrevious();
			Assert::IsTrue(list.RemoveFirst(11.f), L"RemoveFirst(value) failed unexpectedly.");
			Assert::AreEqual(4.f, node->GetValue(), L"RemoveFirst(value) results in the wrong previous value.");
			Assert::AreEqual(5.f, node->GetNext()->GetValue(), L"RemoveFirst(value) results in the wrong next value.");

			// list: { 1, 2, 3, 4, 5, 12, 6, 7, 11, 8, 12, 9, 12, 10 }
			node = list.FindFirst(12.f)->GetPrevious();
			Assert::IsTrue(list.RemoveFirst(12.f), L"RemoveFirst(value) failed unexpectedly.");
			Assert::AreEqual(2.f, node->GetValue(), L"RemoveFirst(value) results in the wrong previous value.");
			Assert::AreEqual(3.f, node->GetNext()->GetValue(), L"RemoveFirst(value) results in the wrong next value.");

			// list: { 1, 2, 12, 3, 4, 5, 12, 6, 7, 8, 12, 9, 12, 10 }
			node = list.FindFirst(11.f)->GetPrevious();
			Assert::IsTrue(list.RemoveFirst(11.f), L"RemoveFirst(value) failed unexpectedly.");
			Assert::AreEqual(7.f, node->GetValue(), L"RemoveFirst(value) results in the wrong previous value.");
			Assert::AreEqual(8.f, node->GetNext()->GetValue(), L"RemoveFirst(value) results in the wrong next value.");

			Assert::IsFalse(list.RemoveFirst(11.f), L"RemoveFirst(value) did not fail when it should have upon not finding the value.");

			DLListf smallList;
			smallList.InsertFirst(3.f);

			Assert::IsTrue(smallList.RemoveFirst(3.f), L"RemoveFirst(value) failed unexpectedly.");
			Assert::IsNull(smallList.GetFirst(), L"GetFirst() is not null in an empty list.");
			Assert::IsNull(smallList.GetLast(), L"GetLast() is not null in an empty list.");
			Assert::IsFalse(smallList.RemoveFirst(3.f), L"RemoveFirst(value) did not fail on an empty list.");
		}

		TEST_METHOD(RemoveLastOccurrence)
		{
			DLListf list;					// list: { 1, 11, 2, 12, 3, 4, 11, 5, 12, 6, 7, 11, 8, 12, 9, 12, 10 }
			list.InsertLast(1.f);
			list.InsertLast(11.f);
			list.InsertLast(2.f);
			list.InsertLast(12.f);
			list.InsertLast(3.f);
			list.InsertLast(4.f);
			list.InsertLast(11.f);
			list.InsertLast(5.f);
			list.InsertLast(12.f);
			list.InsertLast(6.f);
			list.InsertLast(7.f);
			list.InsertLast(11.f);
			list.InsertLast(8.f);
			list.InsertLast(12.f);
			list.InsertLast(9.f);
			list.InsertLast(12.f);
			list.InsertLast(10.f);

			// list: { 1, 11, 2, 12, 3, 4, 11, 5, 12, 6, 7, 11, 8, 12, 9, 10 }
			Assert::IsTrue(list.RemoveLast(12.f), L"RemoveLast(value) failed unexpectedly.");
			Assert::AreEqual(9.f, list.GetLast()->GetPrevious()->GetValue(), L"RemoveLast(value) results in the wrong previous value.");
			Assert::AreEqual(10.f, list.GetLast()->GetValue(), L"RemoveLast(value) results in the wrong next value.");

			// list: { 1, 11, 2, 12, 3, 4, 11, 5, 12, 6, 7, 8, 12, 9, 10 }
			DLListNodef* node = list.FindLast(11.f)->GetPrevious();
			Assert::IsTrue(list.RemoveLast(11.f), L"RemoveLast(value) failed unexpectedly.");
			Assert::AreEqual(7.f, node->GetValue(), L"RemoveLast(value) results in the wrong previous value.");
			Assert::AreEqual(8.f, node->GetNext()->GetValue(), L"RemoveLast(value) results in the wrong next value.");

			// list: { 1, 11, 2, 12, 3, 4, 11, 5, 12, 6, 7, 8, 9, 10 }
			node = list.FindLast(12.f)->GetPrevious();
			Assert::IsTrue(list.RemoveLast(12.f), L"RemoveLast(value) failed unexpectedly.");
			Assert::AreEqual(8.f, node->GetValue(), L"RemoveLast(value) results in the wrong previous value.");
			Assert::AreEqual(9.f, node->GetNext()->GetValue(), L"RemoveLast(value) results in the wrong next value.");

			// list: { 1, 11, 2, 12, 3, 4, 5, 12, 6, 7, 8, 9, 10 }
			node = list.FindLast(11.f)->GetPrevious();
			Assert::IsTrue(list.RemoveLast(11.f), L"RemoveLast(value) failed unexpectedly.");
			Assert::AreEqual(4.f, node->GetValue(), L"RemoveLast(value) results in the wrong previous value.");
			Assert::AreEqual(5.f, node->GetNext()->GetValue(), L"RemoveLast(value) results in the wrong next value.");

			// list: { 1, 2, 12, 3, 4, 5, 12, 6, 7, 8, 9, 10 }
			Assert::IsTrue(list.RemoveLast(11.f), L"RemoveLast(value) failed unexpectedly.");
			Assert::AreEqual(1.f, list.GetFirst()->GetValue(), L"RemoveLast(value) results in the wrong previous value.");
			Assert::AreEqual(2.f, list.GetFirst()->GetNext()->GetValue(), L"RemoveLast(value) results in the wrong next value.");

			Assert::IsFalse(list.RemoveLast(11.f), L"RemoveLast(value) did not fail when it should have upon not finding the value.");

			DLListf smallList;
			smallList.InsertFirst(3.f);

			Assert::IsTrue(smallList.RemoveLast(3.f), L"RemoveLast(value) failed unexpectedly.");
			Assert::IsNull(smallList.GetFirst(), L"GetFirst() is not null in an empty list.");
			Assert::IsNull(smallList.GetLast(), L"GetLast() is not null in an empty list.");
			Assert::IsFalse(smallList.RemoveLast(3.f), L"RemoveLast(value) did not fail on an empty list.");
		}
	};
}