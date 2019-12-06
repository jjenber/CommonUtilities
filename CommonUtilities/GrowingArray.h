#pragma once
#include <cassert>

namespace CommonUtilities
{
	template<typename T, typename SizeType = unsigned short>
	class GrowingArray
	{
	public:
		GrowingArray();
		GrowingArray(SizeType aReservedSize, bool aUseSafeModeFlag = true);
		GrowingArray(const GrowingArray& aGrowingArray);
		GrowingArray(GrowingArray&& aGrowingArray) noexcept;

		~GrowingArray();

		GrowingArray& operator=(const GrowingArray& aGrowingArray);
		GrowingArray& operator=(GrowingArray&& aGrowingArray) noexcept;

		void Init(SizeType aReservedSize = SizeType(1), bool aUseSafeModeFlag = true);
		inline T& operator[](const SizeType aIndex);
		inline const T& operator[](const SizeType aIndex) const;

		inline void Add(const T& aValue);
		inline void Insert(const SizeType aIndex, const T& aValue);
		inline SizeType Find(const T& aValue);

		inline void RemoveCyclic(const T& aValue);
		inline void RemoveCyclicAtIndex(const SizeType aIndex);
		inline void RemoveAll();

		inline void Reserve(SizeType aNewReservedSize);
		void Resize(SizeType aNewSize);
		void Optimize();

		__forceinline SizeType Size() const;
		__forceinline SizeType Capacity() const;
	
	private:
		void Swap(GrowingArray& aGrowingArray) noexcept;
		inline void Free();

		bool myUseSafeMode;
		SizeType mySize;
		SizeType myReserved;

		T* myData;
	};

#pragma region Constructors
	template<typename T, typename SizeType>
	inline GrowingArray<T, SizeType>::GrowingArray() : GrowingArray(0, true)
	{
	}

	template<typename T, typename SizeType>
	inline GrowingArray<T, SizeType>::GrowingArray(SizeType aReservedSize, bool aUseSafeModeFlag) 
		: myData(static_cast<T*>(::operator new(sizeof(T) * aReservedSize))), myReserved(aReservedSize), mySize(0), myUseSafeMode(aUseSafeModeFlag)
	{
	}

	template<typename T, typename SizeType>
	inline GrowingArray<T, SizeType>::GrowingArray(const GrowingArray& aGrowingArray)
		:	myData(static_cast<T*>(::operator new(sizeof(T) * aGrowingArray.myReserved))), 
			myReserved(aGrowingArray.myReserved), mySize(0), myUseSafeMode(aGrowingArray.myUseSafeMode)
	{
		if (myUseSafeMode)
		{
			for (SizeType i = 0; i < aGrowingArray.mySize; i++)
			{
				Add(aGrowingArray.myData[i]);
			}
		}
		else
		{
			std::memcpy(myData, aGrowingArray.myData, sizeof(T) * aGrowingArray.mySize);
			mySize = aGrowingArray.mySize;
		}
	}

	template<typename T, typename SizeType>
	inline GrowingArray<T, SizeType>::GrowingArray(GrowingArray<T, SizeType>&& aGrowingArray) noexcept
		: myData(nullptr), myReserved(0), mySize(0)
	{
		aGrowingArray.Swap(*this); // the rValue is put in a destructible state and destroyed 
	} 

	template<typename T, typename SizeType>
	inline GrowingArray<T, SizeType>::~GrowingArray()
	{
		Free();
	}

#pragma endregion Constructors

#pragma region Operators

	template<typename T, typename SizeType>
	inline GrowingArray<T, SizeType>& GrowingArray<T, SizeType>::operator=(const GrowingArray& aGrowingArray)
	{
		if (myUseSafeMode)
		{
			GrowingArray copy(aGrowingArray);
			copy.Swap(*this);
		}
		else
		{
			Free();
			myData = static_cast<T*>(::operator new(sizeof(T) * aGrowingArray.myReserved));
			std::memcpy(myData, aGrowingArray.myData, sizeof(T) * aGrowingArray.mySize);
			mySize = aGrowingArray.mySize;
			myReserved = aGrowingArray.myReserved;
			myUseSafeMode = aGrowingArray.myUseSafeMode;
		}
		return *this;
	}
	template<typename T, typename SizeType>
	inline GrowingArray<T, SizeType>& GrowingArray<T, SizeType>::operator=(GrowingArray&& aGrowingArray) noexcept
	{
		aGrowingArray.Swap(*this);
		return *this;
	}

	template<typename T, typename SizeType>
	inline T& GrowingArray<T, SizeType>::operator[](const SizeType aIndex)
	{
		assert(aIndex >= 0 && aIndex < mySize && "Index out of bounds.");
		return myData[aIndex];
	}

	template<typename T, typename SizeType>
	inline const T& GrowingArray<T, SizeType>::operator[](const SizeType aIndex) const
	{
		assert(aIndex >= 0 && aIndex < mySize && "Index out of bounds.");
		return myData[aIndex];
	}
	
#pragma endregion Operators

#pragma region FunctionDefinitions
	template<typename T, typename SizeType>
	inline void GrowingArray<T, SizeType>::Init(SizeType aReservedSize, bool aUseSafeModeFlag)
	{
		assert(myReserved == 0 && "GrowingArray is already initialized");
		assert(aReservedSize != 0 && "aReservedSize: Argument out of range. Can't initialize to zero");
		
		myUseSafeMode = aUseSafeModeFlag;
		myReserved = aReservedSize;
		mySize = 0;
		::operator delete(myData);
		myData = static_cast<T*>(::operator new(aReservedSize * sizeof(T)));
	}

	template<typename T, typename SizeType>
	inline void GrowingArray<T, SizeType>::Add(const T& aValue)
	{
		assert(myReserved > 0 && "Vector not initialized. Call Init() before adding.");
		if (mySize == myReserved)
		{
			Reserve(myReserved * SizeType(2));
		}

		new (myData + mySize++) T(aValue); // placement new
	}

	template<typename T, typename SizeType>
	inline void GrowingArray<T, SizeType>::Insert(const SizeType aIndex, const T& aValue)
	{
		assert(myReserved > 0 && "GrowingArray is uninitialized. Call Init() first.");
		assert(aIndex >= 0 && (aIndex <= mySize) && "Index is out of bounds.");
		
		if (mySize == myReserved)
		{
			Reserve(mySize * 2);
		}
		if (myUseSafeMode)
		{
			for (SizeType i = mySize; i > aIndex; i--)
			{
				myData[i] = myData[i - SizeType(1)];
			}
		}
		else
		{
			const SizeType memSize = sizeof(T) * (static_cast<size_t>(mySize) - aIndex);
			std::memcpy(myData + aIndex + SizeType(1), myData + aIndex, memSize);
		}
		myData[aIndex] = aValue;
		++mySize;
	}

	template<typename T, typename SizeType>
	SizeType GrowingArray<T, SizeType>::Find(const T& aValue)
	{
		for (SizeType i = 0; i < mySize; i++)
		{
			const T& value = myData[i];
			if (value == aValue)
			{
				return value;
			}
		}
		static const SizeType FoundNone = -1;
		return FoundNone;
	}

	template<typename T, typename SizeType>
	inline void GrowingArray<T, SizeType>::RemoveCyclic(const T& aValue)
	{
		assert(mySize > 0 && "GrowingArray is already empty.");

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

	template<typename T, typename SizeType>
	inline void GrowingArray<T, SizeType>::RemoveCyclicAtIndex(const SizeType aIndex)
	{
		assert(aIndex >= 0 && aIndex < mySize && "Index out of bounds");
		myData[aIndex] = myData[mySize-- - 1];
	}

	template<typename T, typename SizeType>
	inline void GrowingArray<T, SizeType>::RemoveAll()
	{
		assert(mySize > 0 && "Array is already empty.");
		GrowingArray empty(myReserved);
		empty.Swap(*this);
		mySize = 0;
	}

	template<typename T, typename SizeType>
	inline void GrowingArray<T, SizeType>::Reserve(SizeType aNewReservedSize)
	{
		if (aNewReservedSize > myReserved)
		{
			if (myUseSafeMode)
			{
				GrowingArray copy(aNewReservedSize);
				for (SizeType i = 0; i < mySize; i++)
				{
					copy.Add(myData[i]);
				}
				copy.Swap(*this); // copy gets destroyed and cleans up the old data.
			}
			else
			{
				T* data = myData;
				const int size = sizeof(T) * aNewReservedSize;
				myData = static_cast<T*>(::operator new(size));
				std::memcpy(myData, data, size);
				::operator delete[](data);
				myReserved = aNewReservedSize;
			}
		} 
	}

	template<typename T, typename SizeType>
	inline void GrowingArray<T, SizeType>::Resize(SizeType aNewSize)
	{
		assert(mySize != aNewSize && "Argument size was same as current size.");
		Reserve(aNewSize);
		if (mySize < aNewSize)
		{
			for (SizeType i = mySize; i < aNewSize; i++)
			{
				new (myData + i) T();
			}
			mySize = aNewSize;
		}
		else
		{
			GrowingArray copy(myReserved);
			for (SizeType i = 0; i < aNewSize; i++)
			{
				copy.Add(myData[i]);
			}
			copy.Swap(*this);
		}
	}

	template<typename T, typename SizeType>
	void GrowingArray<T, SizeType>::Optimize()
	{
		if (mySize < myReserved)
		{
			GrowingArray copy(mySize);
			for (SizeType i = 0; i < mySize; i++)
			{
				copy.Add(myData[i]);
			}
			copy.Swap(*this);
		}
	}

	template<typename T, typename SizeType>
	inline SizeType GrowingArray<T, SizeType>::Size() const
	{
		return mySize;
	}

	template<typename T, typename SizeType>
	inline SizeType GrowingArray<T, SizeType>::Capacity() const
	{
		return myReserved;
	}

	template<typename T, typename SizeType>
	inline void GrowingArray<T, SizeType>::Swap(GrowingArray& aGrowingArray) noexcept
	{
		std::swap(aGrowingArray.myData, myData);
		std::swap(aGrowingArray.mySize, mySize);
		std::swap(aGrowingArray.myReserved, myReserved);
		std::swap(aGrowingArray.myUseSafeMode, myUseSafeMode);
	}

	template<typename T, typename SizeType>
	inline void GrowingArray<T, SizeType>::Free()
	{
		for (SizeType i = mySize - SizeType(1); i >= 0; i--)
		{
			(myData + i)->~T();
		}
		::operator delete(myData);
		myReserved = 0;
		mySize = 0;
	}

#pragma endregion FunctionDefinitions
}

