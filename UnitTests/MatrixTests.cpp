#include "pch.h"
#include "CppUnitTest.h"
#include "..//CommonUtilities/Matrix3x3.h"
#include "..//CommonUtilities/Matrix4x4.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixTests
{
	TEST_CLASS(Matrix3x3)
	{
		TEST_METHOD(Constructor)
		{
			CommonUtilities::Matrix3x3<float> mat;

			Assert::AreEqual(0.f, mat(1, 1));
		}
		TEST_METHOD(CopyConstructor)
		{
			CommonUtilities::Matrix3x3<float> mat;
			mat(1, 1) = 5.f;
			CommonUtilities::Matrix3x3<float> copy{ mat };
			Assert::AreEqual(5.f, copy(1, 1));
		}
		TEST_METHOD(CopyConstructorFrom4x4)
		{
			CommonUtilities::Matrix4x4<float> mat;
			mat(1, 1) = 5.f;
			mat(4, 4) = 5.f;
			CommonUtilities::Matrix3x3<float> copy{ mat };
			Assert::AreEqual(5.f, copy(1, 1));
		}

		TEST_METHOD(Assignment)
		{
			CommonUtilities::Matrix3x3<float> mat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
			CommonUtilities::Matrix3x3<float> copy{ 2.f };
			copy = mat;
			Assert::AreEqual(1.f, mat(1, 1));
			Assert::AreEqual(2.f, mat(2, 1));
			Assert::AreEqual(4.f, mat(1, 2));
			Assert::AreEqual(5.f, mat(2, 2));
			Assert::AreEqual(9.f, mat(3, 3));

			Assert::AreEqual(1.f, copy(1, 1));
			Assert::AreEqual(2.f, copy(2, 1));
			Assert::AreEqual(4.f, copy(1, 2));
			Assert::AreEqual(5.f, copy(2, 2));
			Assert::AreEqual(9.f, copy(3, 3));
		}
		TEST_METHOD(ListInitializationFull)
		{
			CommonUtilities::Matrix3x3<float> mat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
			Assert::AreEqual(1.f, mat(1, 1));
			Assert::AreEqual(2.f, mat(2, 1));
			Assert::AreEqual(4.f, mat(1, 2));
			Assert::AreEqual(5.f, mat(2, 2));
			Assert::AreEqual(9.f, mat(3, 3));
		}

		TEST_METHOD(ListInitializationPartial)
		{
			CommonUtilities::Matrix3x3<float> mat{ 3, 3, 4 };
			Assert::AreNotEqual(3.f, mat(3, 3));
			Assert::AreEqual(4.f, mat(3, 3));
		}

		TEST_METHOD(OperatorAddition)
		{
			CommonUtilities::Matrix3x3<int> mat{ 3, 3, 4 };
			CommonUtilities::Matrix3x3<int> mat2{ 1, 2, 3 };
			auto result = mat + mat2;
			CommonUtilities::Matrix3x3<int> compundResult{ 0 };
			compundResult = mat + mat2;
			
			Assert::AreEqual(4, result(1, 1));
			Assert::AreEqual(7, result(3, 3));
			
			Assert::AreEqual(4, compundResult(1, 1));
			Assert::AreEqual(7, compundResult(3, 3));

		}
		TEST_METHOD(OperatorSubtraktion)
		{
			CommonUtilities::Matrix3x3<int> mat{ 3, 3, 1 };
			CommonUtilities::Matrix3x3<int> mat2{ 1, 2, 3 };
			auto result = mat - mat2;
			CommonUtilities::Matrix3x3<int> compundResult{ 0 };
			compundResult = mat - mat2;

			Assert::AreEqual(2, result(1, 1));
			Assert::AreEqual(-2, result(3, 3));

			Assert::AreEqual(2, compundResult(1, 1));
			Assert::AreEqual(-2, compundResult(3, 3));
		}

		TEST_METHOD(OperatorMultiplication)
		{
			CommonUtilities::Matrix3x3<int> mat{ 
				3, 3, 4,
				2, 6, 2,
				1, 1, 1
			};
			CommonUtilities::Matrix3x3<int> mat2{ 
				1, 2, 3,
				3, 4, 1,
				2, 1, 2
			};
			auto result = mat * mat2;
			CommonUtilities::Matrix3x3<int> compoundResult{ mat };
			compoundResult *= mat2;

			Assert::AreEqual(20, result(1, 1));
			Assert::AreEqual(30, result(2, 2));
			Assert::AreEqual(6, result(3, 3));

			Assert::AreEqual(20, compoundResult(1, 1));
			Assert::AreEqual(16, compoundResult(3, 2));
			Assert::AreEqual(6, compoundResult(3, 3));
		}
		TEST_METHOD(OperatorMultiplicationScalar)
		{
			CommonUtilities::Matrix3x3<int> mat{
				3, 3, 4,
				2, 6, 2,
				1, 1, 1
			};

			auto result = mat * 2;
			CommonUtilities::Matrix3x3<int> compoundResult{ mat };
			compoundResult *= 2;

			Assert::AreEqual(6, result(1, 1));
			Assert::AreEqual(12, result(2, 2));
			Assert::AreEqual(2, result(3, 3));

			Assert::AreEqual(6, compoundResult(1, 1));
			Assert::AreEqual(4, compoundResult(3, 2));
			Assert::AreEqual(2, compoundResult(3, 3));
		}
		TEST_METHOD(OperatorMultiplicationVector3)
		{
			CommonUtilities::Matrix3x3<int> mat{
				3, 3, 4,
				2, 6, 2,
				1, 1, 1
			};
			CommonUtilities::Vector3<int> vector{ 1, 2, 3 };
			auto result = mat * vector;

			Assert::AreEqual(6, result.x);
			Assert::AreEqual(20, result.y);
			Assert::AreEqual(21, result.z);
		}

		TEST_METHOD(Equality)
		{
			CommonUtilities::Matrix3x3<float> mat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
			CommonUtilities::Matrix3x3<float> copy{ 2.f };
			if (copy == mat)
			{
				Assert::Fail(L"Equality failed");
			}

			copy = mat;
			if (copy != mat)
			{
				Assert::Fail(L"Equality failed");
			}
		}

		TEST_METHOD(TransposeMat)
		{
			CommonUtilities::Matrix3x3<int> mat{
				1, 2, 3,
				4, 5, 6,
				7, 8, 9
			};

			CommonUtilities::Matrix3x3<int> transposed{
				1, 4, 7,
				2, 5, 8,
				3, 6, 9
			};

			auto res = CommonUtilities::Matrix3x3<int>::Transpose(mat);
			Assert::AreEqual(transposed(1, 1), res(1, 1));
			Assert::AreEqual(transposed(2, 1), res(2, 1));
			Assert::AreEqual(transposed(3, 1), res(3, 1));

			Assert::AreEqual(transposed(1, 2), res(1, 2));
			Assert::AreEqual(transposed(2, 2), res(2, 2));
			Assert::AreEqual(transposed(3, 2), res(3, 2));

			Assert::AreEqual(transposed(1, 3), res(1, 3));
			Assert::AreEqual(transposed(2, 3), res(2, 3));
			Assert::AreEqual(transposed(3, 3), res(3, 3));
		}

		TEST_METHOD(RotationAroundX)
		{
			CommonUtilities::Matrix3x3<float> mat{
				1.f, 2.f, 3.f,
				4.f, 5.f, 6.f,
				7.f, 8.f, 9.f
			};

			auto rotation = CommonUtilities::Matrix3x3<float>::CreateRotationAroundX(0.5f);
		}
		TEST_METHOD(RotationAroundY)
		{
			CommonUtilities::Matrix3x3<float> mat{
				1.f, 2.f, 3.f,
				4.f, 5.f, 6.f,
				7.f, 8.f, 9.f
			};

			auto rotation = CommonUtilities::Matrix3x3<float>::CreateRotationAroundY(0.5f);
		}
		TEST_METHOD(RotationAroundZ)
		{
			CommonUtilities::Matrix3x3<float> mat{
				1.f, 2.f, 3.f,
				4.f, 5.f, 6.f,
				7.f, 8.f, 9.f
			};

			auto rotation = CommonUtilities::Matrix3x3<float>::CreateRotationAroundZ(0.5f);
		}
	};
	TEST_CLASS(Matrix4x4)
	{
		TEST_METHOD(Constructor)
		{
			CommonUtilities::Matrix4x4<float> mat;

			Assert::AreEqual(0.f, mat(1, 1));
		}
		TEST_METHOD(CopyConstructor)
		{
			CommonUtilities::Matrix4x4<float> mat;
			mat(1, 1) = 5.f;
			CommonUtilities::Matrix4x4<float> copy{ mat };
			Assert::AreEqual(5.f, copy(1, 1));
		}

		TEST_METHOD(ListInitializationFull)
		{
			CommonUtilities::Matrix4x4<float> mat{ 3, 3, 3, 4, 4, 4, 5, 5, 5 };
			Assert::AreEqual(3.f, mat(1, 1));
			Assert::AreEqual(4.f, mat(2, 2));
			Assert::AreEqual(5.f, mat(3, 3));
		}

		TEST_METHOD(ListInitializationPartial)
		{
			CommonUtilities::Matrix4x4<float> mat{ 3, 3, 4 };
			Assert::AreNotEqual(3.f, mat(3, 3));
			Assert::AreEqual(4.f, mat(3, 3));
			Assert::AreEqual(4.f, mat(4, 4));
		}

		TEST_METHOD(Addition)
		{
			CommonUtilities::Matrix4x4<int> mat{ 3, 3, 4, 5 };
			CommonUtilities::Matrix4x4<int> mat2{ 1, 2, 3, 0 };
			auto result = mat + mat2;
			CommonUtilities::Matrix4x4<int> compundResult{ mat };
			compundResult += mat2;

			Assert::AreEqual(4, result(1, 1));
			Assert::AreEqual(5, result(3, 3));

			Assert::AreEqual(4, compundResult(1, 1));
			Assert::AreEqual(5, compundResult(3, 3));
		}
	};
}