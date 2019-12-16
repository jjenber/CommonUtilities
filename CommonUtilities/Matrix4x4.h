#pragma once
#include <assert.h>
#include <initializer_list>
namespace CommonUtilities
{
	template<typename T>
	class Matrix4x4
	{
	public:
		Matrix4x4<T>();
		Matrix4x4<T>(const Matrix4x4<T>& aMatrix);
		Matrix4x4<T>(std::initializer_list<T> aList);

		T& operator()(const int aRow, const int aColumn);
		const T& operator()(const int aRow, const int aColumn) const;

		static Matrix4x4<T> CreateRotationAroundX(T aAngleInRadians);
		static Matrix4x4<T> CreateRotationAroundY(T aAngleInRadians);
		static Matrix4x4<T> CreateRotationAroundZ(T aAngleInRadians);
		static Matrix4x4<T> Transpose(const Matrix4x4<T>& aMatrixToTranspose);

	private:
		T myData[12];
	};

#pragma region Constructors
	template <typename T> Matrix4x4<T>::Matrix4x4() : myData() {}
	template <typename T> Matrix4x4<T>::Matrix4x4(const Matrix4x4<T>& aMatrix)
	{
		memcpy(myData, aMatrix.myData, sizeof(T) * size_t(12));
	}

	template<typename T> inline Matrix4x4<T>::Matrix4x4(std::initializer_list<T> aList)
	{
		assert(aList.size() < 13 && "Initializer list contains too many values.");
		std::memcpy(myData, aList.begin(), sizeof(T) * aList.size());
		if (aList.size() < 12)
		{
			std::fill(myData + aList.size(), myData + 12, myData[aList.size() - 1]);
		}
	}
#pragma endregion Constructors


#pragma region Operators
	// Rows and Columns start at 1.
	template<typename T> inline T& Matrix4x4<T>::operator()(const int aRow, const int aColumn)
	{
		assert(aRow > 0 && aRow < 5 && aColumn > 0 && aColumn < 5 && "Argument out of bounds");
		return myData[(aRow - 1) * 4 + (aColumn - 1)];
	}

	// Rows and Columns start at 1.
	template<typename T> inline const T& Matrix4x4<T>::operator()(const int aRow, const int aColumn) const
	{
		return operator(aRow, aColumn);
	}
#pragma endregion Operators
}