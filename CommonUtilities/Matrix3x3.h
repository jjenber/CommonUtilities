#pragma once
#include <assert.h>
#include <cmath>
#include "Matrix4x4.h"
#include "Vector3.h"
namespace CommonUtilities
{
	template<typename T> 
	class Matrix3x3
	{
	public:
		Matrix3x3<T>();
		Matrix3x3<T>(const Matrix3x3<T>& aMatrix);
		Matrix3x3<T>(std::initializer_list<T> aList);
		Matrix3x3<T>(const Matrix4x4<T>& aMatrix);

		Matrix3x3<T>& operator=(const Matrix3x3<T>& aMatrix);
	
		T& operator()(const int aRow, const int aColumn);
		const T& operator()(const int aRow, const int aColumn) const;
		bool operator==(const Matrix3x3<T>& aMatrix) const;
		bool operator!=(const Matrix3x3<T>& aMatrix) const;

		Vector3<T> operator*(const Vector3<T>& aVector);
		Matrix3x3<T> operator+(const Matrix3x3<T>& aMatrix) const;
		Matrix3x3<T> operator-(const Matrix3x3<T>& aMatrix) const;
		Matrix3x3<T> operator*(const Matrix3x3<T>& aMatrix) const;
		Matrix3x3<T> operator*(const T& aScalar) const;
		Matrix3x3<T>& operator+=(const Matrix3x3<T>& aMatrix);
		Matrix3x3<T>& operator-=(const Matrix3x3<T>& aMatrix);
		Matrix3x3<T>& operator*=(const Matrix3x3<T>& aMatrix);
		Matrix3x3<T>& operator*=(const T& aScalar);
		
		static Matrix3x3<T> CreateRotationAroundX(const T aAngleInRadians);
		static Matrix3x3<T> CreateRotationAroundY(const T aAngleInRadians);
		static Matrix3x3<T> CreateRotationAroundZ(const T aAngleInRadians);
		static Matrix3x3<T> Transpose(const Matrix3x3<T>& aMatrixToTranspose);
	private:
		T myData[9];
	};
	
#pragma region Constructors
	template <typename T> Matrix3x3<T>::Matrix3x3() : myData() {}
	template <typename T> Matrix3x3<T>::Matrix3x3(const Matrix3x3<T>& aMatrix)
	{
		memcpy(myData, aMatrix.myData, sizeof(T) * size_t(9));
	}
	
	template<typename T> inline Matrix3x3<T>::Matrix3x3(std::initializer_list<T> aList)
	{
		assert(aList.size() < 10 && "Initializer list contains too many values.");
		std::memcpy(myData, aList.begin(), sizeof(T) * aList.size());
		if (aList.size() < 9)
		{
			std::fill(myData + aList.size(), myData + 9, myData[aList.size() - 1]);
		}
	}

	template<typename T>
	inline Matrix3x3<T>::Matrix3x3(const Matrix4x4<T>& aMatrix)
	{
		const size_t length = sizeof(T) * 3;
		std::memcpy(myData,     &aMatrix(1, 1), length);
		std::memcpy(myData + 3, &aMatrix(1, 2), length);
		std::memcpy(myData + 6, &aMatrix(1, 3), length);
	}

#pragma endregion Constructors

#pragma region Operators

	template<typename T>
	inline Matrix3x3<T>& Matrix3x3<T>::operator=(const Matrix3x3<T>& aMatrix)
	{
		std::memcpy(myData, aMatrix.myData, sizeof(T) * 9);
		return *this;
	}

	// Rows and Columns start at 1.
	template<typename T> inline T& Matrix3x3<T>::operator()(const int aRow, const int aColumn)
	{
		assert(aRow > 0 && aRow < 4 && aColumn > 0 && aColumn < 4 && "Argument out of bounds");
		return myData[(aRow - 1) + ((aColumn - 1) * 3)];
	}

	// Rows and Columns start at 1.
	template<typename T> inline const T& Matrix3x3<T>::operator()(const int aRow, const int aColumn) const
	{
		return myData[(aRow - 1) + ((aColumn - 1) * 3)];
	}

	template<typename T>
	inline bool Matrix3x3<T>::operator==(const Matrix3x3<T>& aMatrix) const
	{
		for (int i = 0; i < 9; i++)
		{
			if (myData[i] != aMatrix.myData[i])
			{
				return false;
			}
		}
		return true;
	}

	template<typename T>
	inline bool Matrix3x3<T>::operator!=(const Matrix3x3<T>& aMatrix) const
	{
		return !operator==(aMatrix);
	}

	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::operator+(const Matrix3x3<T>& aMatrix) const
	{
		Matrix3x3<T> result{ *this };
		return result += aMatrix;
	}

	template<typename T>
	inline Matrix3x3<T>& Matrix3x3<T>::operator+=(const Matrix3x3<T>& aMatrix)
	{
		for (auto i = 0; i < 9; i++)
		{
			myData[i] += aMatrix.myData[i];
		}
		return *this;
	}

	template<class T>
	Matrix3x3<T> operator+(const Matrix3x3<T>& aMatrix)
	{
		Matrix3x3<T> result{ aMatrix };
		return result += aMatrix;
	}

	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::operator-(const Matrix3x3<T>& aMatrix) const
	{
		Matrix3x3<T> result{ *this };
		return result -= aMatrix;
	}

	template<typename T>
	inline Matrix3x3<T>& Matrix3x3<T>::operator-=(const Matrix3x3<T>& aMatrix)
	{
		for (auto i = 0; i < 9; i++)
		{
			myData[i] -= aMatrix.myData[i];
		}
		return *this;
	}

	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::operator*(const Matrix3x3<T>& aMatrix) const
	{
		Matrix3x3<T> result{ *this };
		return result *= aMatrix;
	}

	template<typename T>
	inline Matrix3x3<T>& Matrix3x3<T>::operator*=(const Matrix3x3<T>& aMatrix)
	{
		Matrix3x3<T> result;
		for (int i = 1; i <= 3; i++)
		{
			for (auto j = 1; j <= 3; j++)
			{
				T product{ 0 };
				for (auto k = 1; k <= 3; k++)
				{
					product += this->operator()(k, i) * aMatrix(j, k);
				}
				result(j, i) = product;
			}
		}
		std::memcpy(this->myData, result.myData, sizeof(T) * 9);
		return *this;
	}

	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::operator*(const T& aScalar) const
	{
		Matrix3x3<T> result{ *this };
		return result *= aScalar;
	}
	template<typename T>
	inline Matrix3x3<T>& Matrix3x3<T>::operator*=(const T& aScalar)
	{
		for (int i = 0; i < 9; i++)
		{
			myData[i] *= aScalar;
		}
		return *this;
	}

	template<typename T>
	inline Vector3<T> Matrix3x3<T>::operator*(const Vector3<T>& aVector)
	{
		Vector3<T> result;
		for (int i = 0; i < 3; i++)
		{
			result.x += myData[i * 3] * aVector.x;
		}
		for (int i = 0; i < 3; i++)
		{
			result.y += myData[i * 3 + 1] * aVector.y;
		}
		for (int i = 0; i < 3; i++)
		{
			result.z += myData[i * 3 + 2] * aVector.z;
		}
		return result;
	}

#pragma endregion Operators

#pragma region Static Functions

	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundX(const T aAngleInRadians)
	{
		const T cos = std::cos(aAngleInRadians);
		const T sin = std::sin(aAngleInRadians);
		return
		{
			T(1), 0, 0,
			0, cos, sin,
			0, -sin, cos
		};
	}

	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundY(const T aAngleInRadians)
	{
		const T cos = std::cos(aAngleInRadians);
		const T sin = std::sin(aAngleInRadians);
		return
		{
			cos, 0, -sin,
			0, T(1), 0,
			sin, 0, cos
		};
	}

	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundZ(const T aAngleInRadians)
	{
		const T cos = std::cos(aAngleInRadians);
		const T sin = std::sin(aAngleInRadians);
		return
		{
			cos,  sin, 0,
			-sin, cos, 0,
			0,    0, T(1)
		};
	}

	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::Transpose(const Matrix3x3<T>& aMatrixToTranspose)
	{
		Matrix3x3<T> result;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				result.myData[i + j * 3] = aMatrixToTranspose.myData[j + i * 3];
			}
		}
		return result;
	}

#pragma endregion Static Functions
}