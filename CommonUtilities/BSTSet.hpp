#pragma once
#include "BSTNode.h"
#include <cassert>
namespace CommonUtilities
{
	template <class T>
	class BSTSet
	{
	public:
		~BSTSet();
		bool HasElement(const T& aValue) const;
		void Insert(const T& aValue);
		void Remove(const T& aValue);
		void Clear();
		bool IsEmpty() const;
		
	private:
		bool FindValue(BSTNode<T>* aNode, const T& aValue) const;
		
		BSTNode<T>* FindNode(const T& aValue);
		BSTNode<T>* RemoveRecursive(BSTNode<T>* aNode, const T& aValue);
		BSTNode<T>* myRoot = nullptr;
	};
	template <class T>
	BSTSet<T>::~BSTSet()
	{
		Clear();
	}
	template<class T>
	inline bool BSTSet<T>::HasElement(const T& aValue) const
	{
		assert(myRoot != nullptr && "Tree is empty.");
		return FindValue(myRoot, aValue);
	}

	template<class T>
	inline void BSTSet<T>::Insert(const T& aValue)
	{
		BSTNode<T>* itr = myRoot;
		BSTNode<T>* previous = nullptr;

		while (itr != nullptr)
		{
			previous = itr;
			if (aValue < itr->myElement)
			{
				itr = itr->myLeftChild;
			}
			else if (itr->myElement < aValue)
			{
				itr = itr->myRightChild;
			}
			else
			{
				return;
			}
		}
		if (myRoot == nullptr)
		{
			myRoot = new BSTNode<T>(aValue);
		}
		else if (aValue < previous->myElement)
		{
			previous->myLeftChild = new BSTNode<T>(aValue);
		}
		else
		{
			previous->myRightChild = new BSTNode<T>(aValue);
		}
	}

	template<class T>
	BSTNode<T>* BSTSet<T>::FindNode(const T& aValue)
	{
		BSTNode<T>* itr = myRoot;
		while (itr != nullptr)
		{
			if (aValue < itr->myElement)
			{
				itr = itr->myLeftChild;
			}
			else if (itr->myElement < aValue)
			{
				itr = itr->myRightChild;
			}
			else // value found
			{
				return itr;
			}
		}
		return itr;
	}

	template<class T>
	inline void BSTSet<T>::Remove(const T& aValue)
	{
		myRoot = RemoveRecursive(myRoot, aValue);
	}
	template<class T>
	BSTNode<T>* BSTSet<T>::RemoveRecursive(BSTNode<T>* aNode, const T& aValue)
	{
		if (aNode == nullptr)
			return nullptr;

		if (aValue < aNode->myElement)
		{
			aNode->myLeftChild = RemoveRecursive(aNode->myLeftChild, aValue);
		}
		else if (aNode->myElement < aValue)
		{
			aNode->myRightChild = RemoveRecursive(aNode->myRightChild, aValue);
		}
		else
		{
			if (aNode->myLeftChild == nullptr && aNode->myRightChild == nullptr)
			{
				delete aNode;
				aNode = nullptr;
			}
			else if (aNode->myLeftChild == nullptr)
			{
				BSTNode<T>* temp = aNode;
				aNode = aNode->myRightChild;
				temp->myLeftChild = nullptr;
				temp->myRightChild = nullptr;
				delete temp;
			}
			else if (aNode->myRightChild == nullptr)
			{
				BSTNode<T>* temp = aNode;
				aNode = aNode->myLeftChild;
				temp->myLeftChild = nullptr;
				temp->myRightChild = nullptr;
				delete temp;
			}
			else
			{
				BSTNode<T>* temp = aNode->myRightChild;
				while (temp->myLeftChild != nullptr)
				{
					temp = temp->myLeftChild;
				}
				aNode->myElement = temp->myElement;
				aNode->myRightChild = RemoveRecursive(aNode->myRightChild, temp->myElement);
			}
		}
		return aNode;
	}

	template<class T>
	inline void BSTSet<T>::Clear()
	{
		if (myRoot != nullptr)
		{
			delete myRoot;
			myRoot = nullptr;
		}
	}

	template<class T>
	inline bool BSTSet<T>::IsEmpty() const
	{
		return myRoot == nullptr;
	}

#pragma region Private
	template<class T>
	inline bool BSTSet<T>::FindValue(BSTNode<T>* aNode, const T& aValue) const
	{
		while (aNode != nullptr)
		{
			bool isLower =  (aValue < aNode->myElement);
			bool isHigher = (aNode->myElement < aValue);
			if (!isLower && !isHigher)
			{
				return true;
			}
			else if (isLower)
			{
				aNode = aNode->myLeftChild;
			}
			else if (isHigher)
			{
				aNode = aNode->myRightChild;
			}
		}
		return false;
	}

#pragma endregion
}
