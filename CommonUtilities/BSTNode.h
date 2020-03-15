#pragma once

namespace CommonUtilities
{
	template <class T>
	class BSTNode
	{
		template <class U> friend class BSTSet;
		BSTNode(const T& aValue);
		~BSTNode();

		T myElement;
		BSTNode* myLeftChild = nullptr;
		BSTNode* myRightChild = nullptr;
	};

	template <class T>
	BSTNode<T>::BSTNode(const T& aValue) 
	{
		myElement = aValue; 
	};

	template <class T>
	BSTNode<T>::~BSTNode()
	{
		if (myLeftChild != nullptr)
		{
			delete myLeftChild;
			myLeftChild = nullptr;
		}
		if (myRightChild != nullptr)
		{
			delete myRightChild;
			myRightChild = nullptr;
		}
	}
}