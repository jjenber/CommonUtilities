#pragma once
#include <cassert>
#include <initializer_list>

namespace CommonUtilities
{
	template <typename T, int size, typename SizeType = unsigned short, bool UseSafeModeFlag = true>
	class VectorOnStack
	{
	public:
		VectorOnStack() = default;
		VectorOnStack(const VectorOnStack& aVectorOnStack);
		VectorOnStack(const std::initializer_list<T>& aInitList);
		
		~VectorOnStack() = default;

		VectorOnStack& operator=(const VectorOnStack& aVectorOnStack);
		inline const T& operator[](const SizeType aIndex) const;
		inline T& operator[](const SizeType aIndex);
		
		inline void Add(const T& aValue);
		inline void Insert(const SizeType aIndex, const T& aValue);
		inline void RemoveCyclic(const T& aValue);
		inline void RemoveCyclicAtIndex(const SizeType aIndex);
		inline void Clear();
		__forceinline SizeType Size() const;
		__forceinline constexpr int Capacity() const;

	private:
		T myData[size] = { };
		SizeType mySize = 0;
	};

	template<typename T, int size, typename SizeType, bool UseSafeModeFlag>
	inline VectorOnStack<T, size, SizeType, UseSafeModeFlag>::VectorOnStack(const VectorOnStack& aVectorOnStack)
	{
		if (UseSafeModeFlag)
		{
			for (SizeType i = 0; i < aVectorOnStack.mySize; i++)
			{
				myData[i] = aVectorOnStack[i];
			}
		}
		else
		{
			std::memcpy(myData, aVectorOnStack.myData, sizeof(T) * aVectorOnStack.mySize);
		}
		mySize = aVectorOnStack.mySize;
	}

	template<typename T, int size, typename SizeType, bool UseSafeModeFlag>
	inline VectorOnStack<T, size, SizeType, UseSafeModeFlag>::VectorOnStack(const std::initializer_list<T>& aInitList)
	{
		assert(aInitList.size() <= size && "Initializer list has too many values.");
		if (UseSafeModeFlag)
		{
			for (int i = 0; i < aInitList.size(); i++)
			{
				myData[i] = *(aInitList.begin() + i);
			}
		}
		else
		{
			std::memcpy(myData, aInitList.begin(), sizeof(T) * aInitList.size());
		}
		mySize = static_cast<SizeType>(aInitList.size());
	}

	template<typename T, int size, typename SizeType, bool UseSafeModeFlag>
	inline VectorOnStack<T, size, SizeType, UseSafeModeFlag>& VectorOnStack<T, size, SizeType, UseSafeModeFlag>::operator=(const VectorOnStack& aVectorOnStack)
	{
		if (UseSafeModeFlag)
		{
			for (SizeType i = 0; i < aVectorOnStack.mySize; i++)
			{
				myData[i] = aVectorOnStack[i];
			}
		}
		else
		{
			std::memcpy(myData, aVectorOnStack.myData, sizeof(T) * size);
		}
		mySize = aVectorOnStack.mySize;
		return *this;
	}

	template<typename T, int size, typename SizeType, bool UseSafeModeFlag>
	inline const T& VectorOnStack<T, size, SizeType, UseSafeModeFlag>::operator[](const SizeType aIndex) const
	{
		assert(aIndex >= 0 && aIndex < mySize && "Index out of bounds");
		return myData[aIndex];
	}

	template<typename T, int size, typename SizeType, bool UseSafeModeFlag>
	inline T& VectorOnStack<T, size, SizeType, UseSafeModeFlag>::operator[](const SizeType aIndex)
	{
		assert(aIndex >= 0 && aIndex < mySize && "Index out of bounds");
		return myData[aIndex];
	}

	template<typename T, int size, typename SizeType, bool UseSafeModeFlag>
	inline void VectorOnStack<T, size, SizeType, UseSafeModeFlag>::Add(const T& aObject)
	{
		assert(mySize < size && "Vector is full.");
		myData[mySize++] = aObject;
	}

	template<typename T, int size, typename SizeType, bool UseSafeModeFlag>
	inline void VectorOnStack<T, size, SizeType, UseSafeModeFlag>::Insert(const SizeType aIndex, const T& aValue)
	{
		assert(aIndex >= 0 && (aIndex <= mySize) && "Index is out of bounds.");
		assert(mySize < size && "Vector is full.");
		if (UseSafeModeFlag)
		{
			for (SizeType i = mySize; i > aIndex; i--)
			{
				myData[i] = myData[i - SizeType(1)];
			}
		}
		else
		{
			const size_t memSize = sizeof(T) * (static_cast<size_t>(mySize) - aIndex);
			std::memcpy(&myData[aIndex + 1], &myData[aIndex], memSize);
		}
		myData[aIndex] = aValue;
		mySize = mySize < size ? mySize + 1 : mySize;
	}

	template<typename T, int size, typename SizeType, bool UseSafeModeFlag>
	inline void VectorOnStack<T, size, SizeType, UseSafeModeFlag>::RemoveCyclic(const T& aValue)
	{
		assert(mySize > 0 && "Vector is already empty.");

		for (SizeType i = 0; i < mySize; i++)
		{
			if (myData[i] == aValue)
			{
				myData[i] = myData[mySize-- - 1];
				break;
			}
			if (i == mySize - 1)
			{
				assert(false && "Value not found.");
			}
		}
	}

	template<typename T, int size, typename SizeType, bool UseSafeModeFlag>
	inline void VectorOnStack<T, size, SizeType, UseSafeModeFlag>::RemoveCyclicAtIndex(const SizeType aIndex)
	{
		assert(aIndex >= 0 && aIndex < mySize && "Index out of bounds");
		myData[aIndex] = myData[mySize-- - 1];
	}

	template<typename T, int size, typename SizeType, bool UseSafeModeFlag>
	inline void VectorOnStack<T, size, SizeType, UseSafeModeFlag>::Clear()
	{
		mySize = 0;
	}

	template<typename T, int size, typename SizeType, bool UseSafeModeFlag>
	__forceinline SizeType VectorOnStack<T, size, SizeType, UseSafeModeFlag>::Size() const
	{
		return mySize;
	}
	template<typename T, int size, typename SizeType, bool UseSafeModeFlag>
	__forceinline constexpr int VectorOnStack<T, size, SizeType, UseSafeModeFlag>::Capacity() const
	{
		return size;
	}
}
