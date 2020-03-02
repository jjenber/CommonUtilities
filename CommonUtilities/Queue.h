#pragma once
#include "GrowingArray.h"
#include <queue>
namespace CommonUtilities
{
	template <class T>
	class Queue
	{
	public:
		Queue();
		Queue(const int aReserved);
		int GetSize() const;
		bool IsEmpty();
		const T& GetFront() const;
		T& GetFront();
		void Enqueue(const T& aValue);
		T Dequeue();

	private:
		void Grow();

		GrowingArray<T, int> myData;
		int myFront;
		int myBack;
		int mySize;
	};
	
	template<class T>
	inline Queue<T>::Queue() : Queue(1) {}

	template<class T>
	inline Queue<T>::Queue(const int aReserved) : myFront(0), myBack(0), mySize(0)
	{
		myData.Init(aReserved);
	}

	template<class T>
	inline int Queue<T>::GetSize() const
	{
		return mySize;
	}

	template<class T>
	inline bool Queue<T>::IsEmpty()
	{
		return mySize == 0;
	}
	template<class T>
	inline const T& Queue<T>::GetFront() const
	{
		return GetFront();
	}
	template<class T>
	inline T& Queue<T>::GetFront()
	{
		assert(!IsEmpty() && "Queue is empty.");
		return myData[myFront];
	}
	template<class T>
	inline void Queue<T>::Enqueue(const T& aValue)
	{
		if (mySize == myData.mySize)
		{
			if (myFront != 0)
			{
				Grow();
			}
			else
				myBack++;
			myData.Add(T());
			myData[myBack] = aValue;
			mySize++;
			
			return;
		}
		myBack = myBack == myData.mySize - 1 ? 0 : myBack + 1;
		myData[myBack] = aValue;
		++mySize;
	}
	template<class T>
	inline T Queue<T>::Dequeue()
	{
		assert(mySize > 0 && "Queue is empty.");
		T value = myData[myFront];
		(myData.myData + myFront)->~T();
		myFront = (myFront + 1) % myData.mySize;
		--mySize;
		return value;
	}

	template<class T>
	inline void Queue<T>::Grow()
	{
		auto oldData = myData;
		myData = GrowingArray<T, int>(myData.myReserved * 2);
		for (int i = myFront; ; i = (i + 1) % mySize)
		{
			myData.Add(oldData[i]);
			if (i == myBack)
			{
				myFront = 0;
				myBack = mySize;
				break;
			}
		}
	}
}

