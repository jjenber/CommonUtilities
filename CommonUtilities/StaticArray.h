#pragma once
#include <cassert>
#include <initializer_list>
namespace CommonUtilities
{
	template <typename T, int size>
	class StaticArray
	{
	public:
		StaticArray() = default;
		StaticArray(const StaticArray& aStaticArray);
		StaticArray(const std::initializer_list<T>& aInitList);
		~StaticArray() = default;
		StaticArray& operator=(const StaticArray& aStaticArray);
		inline const T& operator[](const int aIndex) const;
		inline T& operator[](const int aIndex);
		inline void Insert(const int aIndex, const T& aValue);

	private:
		T myData[size] = { };
	};

	template<typename T, int size>
	inline StaticArray<T, size>::StaticArray(const StaticArray& aStaticArray)
	{
		for (int i = 0; i < size; i++)
		{
			myData[i] = aStaticArray[i];
		}
	}

	template<typename T, int size>
	inline StaticArray<T, size>::StaticArray(const std::initializer_list<T>& aInitList)
	{
		assert(aInitList.size() <= size && "Initializer list has too many values.");
		for (int i = 0; i < size; i++)
		{
			myData[i] = i < aInitList.size() ? *(aInitList.begin() + i) : *(aInitList.begin() + aInitList.size() - 1);
		}
	}

	template<typename T, int size>
	inline StaticArray<T, size>& StaticArray<T, size>::operator=(const StaticArray& aStaticArray)
	{
		for (int i = 0; i < size; i++)
		{
			myData[i] = aStaticArray[i];
		}
		return *this;
	}

	template<typename T, int size>
	inline const T& StaticArray<T, size>::operator[](const int aIndex) const
	{
		assert(aIndex >= 0 && aIndex < size && "Index out of bounds");
		return myData[aIndex];
	}

	template<typename T, int size>
	inline T& StaticArray<T, size>::operator[](const int aIndex)
	{
		assert(aIndex >= 0 && aIndex < size && "Index out of bounds");
		return myData[aIndex];
	}

	template<typename T, int size>
	inline void StaticArray<T, size>::Insert(const int aIndex, const T& aValue)
	{
		assert(aIndex >= 0 && aIndex < size && "Index out of bounds");
		for (int i = size - 1; i >= aIndex; i--)
		{
			myData[i] = myData[i - 1];
		}
		myData[aIndex] = aValue;
	}
}