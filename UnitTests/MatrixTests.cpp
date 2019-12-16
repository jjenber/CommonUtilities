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

		TEST_METHOD(ListInitializationFull)
		{
			CommonUtilities::Matrix3x3<float> mat{ 3, 3, 3, 4, 4, 4, 5, 5, 5 };
			Assert::AreEqual(3.f, mat(1, 1));
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
		}

		TEST_METHOD(ListInitializationPartial)
		{
			CommonUtilities::Matrix4x4<float> mat{ 3, 3, 4 };
			Assert::AreNotEqual(3.f, mat(3, 3));
			Assert::AreEqual(4.f, mat(3, 3));
		}

		TEST_METHOD(Addition)
		{

		}
	};
}