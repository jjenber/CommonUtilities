#include "pch.h"
#include "CppUnitTest.h"

#include "Shared/Utility.hpp"
#include "..//CommonUtilities/Matrix3x3.h"
//#include "Student Code/Matrix3x3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using Matrix3x3f = CommonUtilities::Matrix3x3<float>;
using Matrix3x3d = CommonUtilities::Matrix3x3<double>;
using Matrix4x4f = CommonUtilities::Matrix4x4<float>;
using Matrix4x4d = CommonUtilities::Matrix4x4<double>;
using Vector3f = CommonUtilities::Vector3<float>;
using Vector3d = CommonUtilities::Vector3<double>;

namespace Assignment4Matrices
{		
	TEST_CLASS(Matrix3x3Tests)
	{
	public:
		
		TEST_METHOD(M3_Default_Constructor)
		{
			// Test the Matrix3x3<float> default constructor.
			Matrix3x3f matrixF;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(row == col ? 1.0f : 0.0f, matrixF(row, col), L"Default constructor for Matrix3x3<float> should result in identity matrix.");
				}
			}

			// Test the Matrix3x3<double> default constructor.
			Matrix3x3d matrixD;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(row == col ? 1.0 : 0.0, matrixD(row, col), L"Default constructor for Matrix3x3<double> should result in identity matrix.");
				}
			}
		}

		TEST_METHOD(M3_Copy_Constructor)
		{
			// Test the Matrix3x3<float> copy constructor.
			Matrix3x3f sourceF;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					sourceF(row, col) = TestUtility::GetRandomFloat();
				}
			}

			const Matrix3x3f copyF(sourceF);

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					// Compilation error if there is no const version of operator().
					Assert::AreEqual(sourceF(row, col), copyF(row, col), L"Copy constructor for Matrix3x3<float> should result in a matrix identical to the source.");
				}
			}

			// Test the Matrix3x3<double> copy constructor.
			Matrix3x3d sourceD;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					sourceD(row, col) = TestUtility::GetRandomDouble();
				}
			}

			const Matrix3x3d copyD(sourceD);

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					// Compilation error if there is no const version of operator().
					Assert::AreEqual(sourceD(row, col), copyD(row, col), L"Copy constructor for Matrix3x3<double> should result in a matrix identical to the source.");
				}
			}
		}

		TEST_METHOD(M3_Copy_Constructor_Matrix4x4)
		{
			// Test the Matrix3x3<float> constructor taking a Matrix4x4<float>.
			Matrix4x4f sourceF;

			for (unsigned int col = 1; col <= 4; ++col)
			{
				for (unsigned int row = 1; row <= 4; ++row)
				{
					sourceF(row, col) = TestUtility::GetRandomFloat();
				}
			}

			Matrix3x3f copyF(sourceF);

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(sourceF(row, col), copyF(row, col), L"Constructor for Matrix3x3<float> taking a Matrix4x4<float> should result in a matrix identical to the upper left 3x3 part of the source.");
				}
			}

			// Test the Matrix3x3<double> constructor taking a Matrix4x4<double>.
			Matrix4x4d sourceD;

			for (unsigned int col = 1; col <= 4; ++col)
			{
				for (unsigned int row = 1; row <= 4; ++row)
				{
					sourceD(row, col) = TestUtility::GetRandomDouble();
				}
			}

			Matrix3x3d copyD(sourceD);

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(sourceD(row, col), copyD(row, col), L"Constructor for Matrix3x3<double> taking a Matrix4x4<double> should result in a matrix identical to the upper left 3x3 part of the source.");
				}
			}
		}

		TEST_METHOD(M3_Assignment_Operator)
		{
			// Test the Matrix3x3<float> assignment operator.
			Matrix3x3f sourceF;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					sourceF(row, col) = TestUtility::GetRandomFloat();
				}
			}

			Matrix3x3f copyF;
			copyF = sourceF;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(sourceF(row, col), copyF(row, col), L"Copy constructor for Matrix3x3<float> should result in a matrix identical to the source.");
				}
			}

			// Test the Matrix3x3<double> assignment operator.
			Matrix3x3d sourceD;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					sourceD(row, col) = TestUtility::GetRandomDouble();
				}
			}

			Matrix3x3d copyD;
			copyD = sourceD;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(sourceD(row, col), copyD(row, col), L"Copy constructor for Matrix3x3<double> should result in a matrix identical to the source.");
				}
			}
		}

		TEST_METHOD(M3_Add_Assignment_Operator)
		{
			// Test the Matrix3x3<float> add-assign operator function.
			Matrix3x3f resultF;
			Matrix3x3f addF;
			float originalNumbersF[ourRowCount][ourColumnCount];

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					originalNumbersF[row - 1][col - 1] = TestUtility::GetRandomFloat();
					resultF(row, col) = originalNumbersF[row - 1][col - 1];
					addF(row, col) = TestUtility::GetRandomFloat();
				}
			}

			resultF += addF;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(originalNumbersF[row - 1][col - 1] + addF(row, col), resultF(row, col), L"Matrix3x3<float>::operator+= should do an element-wise addition.");
				}
			}

			// Test the Matrix3x3<double> add-assign operator function.
			Matrix3x3d resultD;
			Matrix3x3d addD;
			double originalNumbersD[ourRowCount][ourColumnCount];

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					originalNumbersD[row - 1][col - 1] = TestUtility::GetRandomDouble();
					resultD(row, col) = originalNumbersD[row - 1][col - 1];
					addD(row, col) = TestUtility::GetRandomDouble();
				}
			}

			resultD += addD;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(originalNumbersD[row - 1][col - 1] + addD(row, col), resultD(row, col), L"Matrix3x3<double>::operator+= should do an element-wise addition.");
				}
			}
		}

		TEST_METHOD(M3_Add_Operator)
		{
			// Test the Matrix3x3<float> add operator function.
			Matrix3x3f leftF, rightF;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					leftF(row, col) = TestUtility::GetRandomFloat();
					rightF(row, col) = TestUtility::GetRandomFloat();
				}
			}

			Matrix3x3f resultF = leftF + rightF;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(leftF(row, col) + rightF(row, col), resultF(row, col), L"Matrix3x3<float>::operator+ should do an element-wise addition.");
				}
			}

			// Test the Matrix3x3<double> add operator function.
			Matrix3x3d leftD, rightD;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					leftD(row, col) = TestUtility::GetRandomDouble();
					rightD(row, col) = TestUtility::GetRandomDouble();
				}
			}

			Matrix3x3d resultD = leftD + rightD;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(leftD(row, col) + rightD(row, col), resultD(row, col), L"Matrix3x3<double>::operator+ should do an element-wise addition.");
				}
			}
		}

		TEST_METHOD(M3_Subtract_Assignment_Operator)
		{
			// Test the Matrix3x3<float> subtract-assign operator function.
			Matrix3x3f resultF;
			Matrix3x3f subtractF;
			float originalNumbersF[ourRowCount][ourColumnCount];

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					originalNumbersF[row - 1][col - 1] = TestUtility::GetRandomFloat();
					resultF(row, col) = originalNumbersF[row - 1][col - 1];
					subtractF(row, col) = TestUtility::GetRandomFloat();
				}
			}

			resultF -= subtractF;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(originalNumbersF[row - 1][col - 1] - subtractF(row, col), resultF(row, col), L"Matrix3x3<float>::operator-= should do an element-wise addition.");
				}
			}

			// Test the Matrix3x3<double> subtract-assign operator function.
			Matrix3x3d resultD;
			Matrix3x3d subtractD;
			double originalNumbersD[ourRowCount][ourColumnCount];

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					originalNumbersD[row - 1][col - 1] = TestUtility::GetRandomDouble();
					resultD(row, col) = originalNumbersD[row - 1][col - 1];
					subtractD(row, col) = TestUtility::GetRandomDouble();
				}
			}

			resultD -= subtractD;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(originalNumbersD[row - 1][col - 1] - subtractD(row, col), resultD(row, col), L"Matrix3x3<double>::operator-= should do an element-wise addition.");
				}
			}
		}

		TEST_METHOD(M3_Subtract_Operator)
		{
			// Test the Matrix3x3<float> subtract operator function.
			Matrix3x3f leftF, rightF;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					leftF(row, col) = TestUtility::GetRandomFloat();
					rightF(row, col) = TestUtility::GetRandomFloat();
				}
			}

			Matrix3x3f resultF = leftF - rightF;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(leftF(row, col) - rightF(row, col), resultF(row, col), L"Matrix3x3<float>::operator- should do an element-wise subtraction.");
				}
			}

			// Test the Matrix3x3<double> subtract operator function.
			Matrix3x3d leftD, rightD;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					leftD(row, col) = TestUtility::GetRandomFloat();
					rightD(row, col) = TestUtility::GetRandomFloat();
				}
			}

			Matrix3x3d resultD = leftD - rightD;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(leftD(row, col) - rightD(row, col), resultD(row, col), L"Matrix3x3<double>::operator- should do an element-wise subtraction.");
				}
			}
		}

		TEST_METHOD(M3_Multiply_Assignment_Operator)
		{
			// Test the Matrix3x3<float> multiply-assign operator function with an identity matrix.
			Matrix3x3f resultF;
			Matrix3x3f multiplyF;
			float originalNumbersF[ourRowCount][ourColumnCount];

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					originalNumbersF[row - 1][col - 1] = TestUtility::GetRandomFloat();
					resultF(row, col) = originalNumbersF[row - 1][col - 1];
					multiplyF(row, col) = TestUtility::GetRandomFloat();
				}
			}

			resultF *= Matrix3x3f();

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(originalNumbersF[row - 1][col - 1], resultF(row, col), L"Matrix3x3<float>::operator*= with the identity matrix should not change the matrix.");
				}
			}

			// Test the Matrix3x3<float> multiply-assign operator function with a random matrix.
			resultF *= multiplyF;
			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					float element = originalNumbersF[row - 1][0] * multiplyF(1, col) +
						originalNumbersF[row - 1][1] * multiplyF(2, col) +
						originalNumbersF[row - 1][2] * multiplyF(3, col);

					Assert::AreEqual(element, resultF(row, col), L"Matrix3x3<float>::operator*= with a random matrix produces incorrect results.");
				}
			}

			// Test the Matrix3x3<float> multiply-assign operator function with a zero matrix.
			Matrix3x3f zeroF;
			zeroF(1, 1) = zeroF(2, 2) = zeroF(3, 3) = 0.0f;

			resultF *= zeroF;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(0.0f, resultF(row, col), L"Matrix3x3<float>::operator*= with a zero matrix should result in a zero matrix.");
				}
			}

			// Test the Matrix3x3<double> multiply-assign operator function with an identity matrix.
			Matrix3x3d resultD;
			Matrix3x3d multiplyD;
			double originalNumbersD[ourRowCount][ourColumnCount];

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					originalNumbersD[row - 1][col - 1] = TestUtility::GetRandomDouble();
					resultD(row, col) = originalNumbersD[row - 1][col - 1];
					multiplyD(row, col) = TestUtility::GetRandomDouble();
				}
			}

			resultD *= Matrix3x3d();

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(originalNumbersD[row - 1][col - 1], resultD(row, col), L"Matrix3x3<double>::operator*= with the identity matrix should not change the matrix.");
				}
			}

			// Test the Matrix3x3<double> multiply-assign operator function with a random matrix.
			resultD *= multiplyD;
			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					double element = originalNumbersD[row - 1][0] * multiplyD(1, col) +
						originalNumbersD[row - 1][1] * multiplyD(2, col) +
						originalNumbersD[row - 1][2] * multiplyD(3, col);

					Assert::AreEqual(element, resultD(row, col), L"Matrix3x3<double>::operator*= with a random matrix produces incorrect results.");
				}
			}

			// Test the Matrix3x3<double> multiply-assign operator function with a zero matrix.
			Matrix3x3d zeroD;
			zeroD(1, 1) = zeroD(2, 2) = zeroD(3, 3) = 0.0;

			resultD *= zeroD;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(0.0, resultD(row, col), L"Matrix3x3<float>::operator* with a zero matrix should result in a zero matrix.");
				}
			}
		}

		TEST_METHOD(M3_Multiply_Operator)
		{
			// Test the Matrix3x3<float> multiply operator function with an identity matrix.
			Matrix3x3f leftF, rightF;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					leftF(row, col) = TestUtility::GetRandomFloat();
					rightF(row, col) = TestUtility::GetRandomFloat();
				}
			}

			Matrix3x3f resultF;
			resultF = leftF * Matrix3x3f();

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(leftF(row, col), resultF(row, col), L"Matrix3x3<float>::operator* with the identity matrix should not change the matrix.");
				}
			}
			
			// Test the Matrix3x3<float> multiply operator function with a random matrix.
			resultF = leftF * rightF;
			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					float element = leftF(row, 1) * rightF(1, col) +
						leftF(row, 2) * rightF(2, col) +
						leftF(row, 3) * rightF(3, col);

					Assert::AreEqual(element, resultF(row, col), L"Matrix3x3<float>::operator* with a random matrix produces incorrect results.");
				}
			}

			// Test the Matrix3x3<float> multiply operator function with a zero matrix.
			Matrix3x3f zeroF;
			zeroF(1, 1) = zeroF(2, 2) = zeroF(3, 3) = 0.0f;

			resultF = leftF * zeroF;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(0.0f, resultF(row, col), L"Matrix3x3<float>::operator* with a zero matrix should result in a zero matrix.");
				}
			}

			// Test the Matrix3x3<double> multiply operator function with an identity matrix.
			Matrix3x3d leftD, rightD;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					leftD(row, col) = TestUtility::GetRandomDouble();
					rightD(row, col) = TestUtility::GetRandomDouble();
				}
			}

			Matrix3x3d resultD;
			resultD = leftD * Matrix3x3d();

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(leftD(row, col), resultD(row, col), L"Matrix3x3<double>::operator* with the identity matrix should not change the matrix.");
				}
			}

			// Test the Matrix3x3<double> multiply operator function with a random matrix.
			resultD = leftD * rightD;
			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					double element = leftD(row, 1) * rightD(1, col) +
						leftD(row, 2) * rightD(2, col) +
						leftD(row, 3) * rightD(3, col);

					Assert::AreEqual(element, resultD(row, col), L"Matrix3x3<double>::operator* with a random matrix produces incorrect results.");
				}
			}

			// Test the Matrix3x3<double> multiply operator function with a zero matrix.
			Matrix3x3d zeroD;
			zeroD(1, 1) = zeroD(2, 2) = zeroD(3, 3) = 0.0;

			resultD = leftD * zeroD;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(0.0, resultD(row, col), L"Matrix3x3<double>::operator* with a zero matrix should result in a zero matrix.");
				}
			}
		}
		
		TEST_METHOD(M3_Vector_Matrix_Multiplication)
		{
			// Test the Matrix3x3<float> multiply operator function with Vector3<float>.
			Matrix3x3f matrixF;
			Vector3f vectorF(TestUtility::GetRandomFloat(), TestUtility::GetRandomFloat(), TestUtility::GetRandomFloat());

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					matrixF(row, col) = TestUtility::GetRandomFloat();
				}
			}

			Vector3f resultF;
			resultF = vectorF * matrixF;
			Vector3f correctF;

			correctF.x = vectorF.x * matrixF(1, 1) + vectorF.y * matrixF(2, 1) + vectorF.z * matrixF(3, 1);
			correctF.y = vectorF.x * matrixF(1, 2) + vectorF.y * matrixF(2, 2) + vectorF.z * matrixF(3, 2);
			correctF.z = vectorF.x * matrixF(1, 3) + vectorF.y * matrixF(2, 3) + vectorF.z * matrixF(3, 3);

			Assert::AreEqual(correctF.x, resultF.x, L"Vector3<float> and Matrix3x3<float> multiplication yields an incorrect x value.");
			Assert::AreEqual(correctF.y, resultF.y, L"Vector3<float> and Matrix3x3<float> multiplication yields an incorrect y value.");
			Assert::AreEqual(correctF.z, resultF.z, L"Vector3<float> and Matrix3x3<float> multiplication yields an incorrect z value.");

			// Test the Matrix3x3<double> multiply operator function with Vector3<float>.
			Matrix3x3d matrixD;
			Vector3d vectorD(TestUtility::GetRandomDouble(), TestUtility::GetRandomDouble(), TestUtility::GetRandomDouble());

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					matrixD(row, col) = TestUtility::GetRandomDouble();
				}
			}

			Vector3d resultD;
			resultD = vectorD * matrixD;
			Vector3d correctD;

			correctD.x = vectorD.x * matrixD(1, 1) + vectorD.y * matrixD(2, 1) + vectorD.z * matrixD(3, 1);
			correctD.y = vectorD.x * matrixD(1, 2) + vectorD.y * matrixD(2, 2) + vectorD.z * matrixD(3, 2);
			correctD.z = vectorD.x * matrixD(1, 3) + vectorD.y * matrixD(2, 3) + vectorD.z * matrixD(3, 3);

			Assert::AreEqual(correctD.x, resultD.x, L"Vector3<double> and Matrix3x3<double> multiplication yields an incorrect x value.");
			Assert::AreEqual(correctD.y, resultD.y, L"Vector3<double> and Matrix3x3<double> multiplication yields an incorrect y value.");
			Assert::AreEqual(correctD.z, resultD.z, L"Vector3<double> and Matrix3x3<double> multiplication yields an incorrect z value.");
		}

		TEST_METHOD(M3_Comparison_Operator)
		{
			// Test the Matrix3x3<float> comparison operator.
			Matrix3x3f sourceF;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					sourceF(row, col) = TestUtility::GetRandomFloat();
				}
			}

			Assert::IsTrue(sourceF == sourceF, L"Matrix3x3<float>::operator== returns false when comparing a Matrix3x3<float> with itself.");

			const Matrix3x3f copyF(sourceF);

			// Compilation error here if the operator==() function is not const.
			Assert::IsTrue(copyF == sourceF, L"Matrix3x3<float>::operator== returns false when comparing a Matrix3x3<float> with a copy of itself.");

			// Test the Matrix3x3<double> comparison operator.
			Matrix3x3d sourceD;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					sourceD(row, col) = TestUtility::GetRandomDouble();
				}
			}

			Assert::IsTrue(sourceD == sourceD, L"Matrix3x3<float>::operator== returns false when comparing a Matrix3x3<float> with itself.");

			const Matrix3x3d copyD(sourceD);

			// Compilation error here if the operator==() function is not const.
			Assert::IsTrue(copyD == sourceD, L"Matrix3x3<float>::operator== returns false when comparing a Matrix3x3<float> with a copy of itself.");
		}

		TEST_METHOD(M3_Transpose)
		{
			// Test the static Matrix3x3<float> Transpose() function.
			Matrix3x3f matrixF;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					matrixF(row, col) = TestUtility::GetRandomFloat();
				}
			}

			Matrix3x3f transposedF = Matrix3x3f::Transpose(matrixF);

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(matrixF(col, row), transposedF(row, col), L"Transpose() of Matrix3x3<float> is not producing the correct results.");
				}
			}

			// Test the static Matrix3x3<double> Transpose() function.
			Matrix3x3d matrixD;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					matrixD(row, col) = TestUtility::GetRandomDouble();
				}
			}

			Matrix3x3d transposedD = Matrix3x3d::Transpose(matrixD);

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(matrixD(col, row), transposedD(row, col), L"Transpose() of Matrix3x3<double> is not producing the correct results.");
				}
			}
		}

		TEST_METHOD(M3_Create_Rotation_Around_X)
		{
			// Test the static Matrix3x3<float> CreateRotationAroundX() function.
			const float piF = std::acos(-1.0f);
			const float angleF = TestUtility::GetRandomFloat(-piF * 2.0f, piF * 2.0f);

			Matrix3x3f resultF = Matrix3x3f::CreateRotationAroundX(angleF);

			float cosAngleF = std::cos(angleF);
			float sinAngleF = std::sin(angleF);

			Assert::AreEqual(1.0f, resultF(1, 1), L"The Matrix3x3<float>::CreateRotationAroundX() function produced an incorrect result in element (1, 1).");
			Assert::AreEqual(0.0f, resultF(1, 2), L"The Matrix3x3<float>::CreateRotationAroundX() function produced an incorrect result in element (1, 2).");
			Assert::AreEqual(0.0f, resultF(1, 3), L"The Matrix3x3<float>::CreateRotationAroundX() function produced an incorrect result in element (1, 3).");

			Assert::AreEqual(0.0f, resultF(2, 1), L"The Matrix3x3<float>::CreateRotationAroundX() function produced an incorrect result in element (2, 1).");
			Assert::AreEqual(cosAngleF, resultF(2, 2), L"The Matrix3x3<float>::CreateRotationAroundX() function produced an incorrect result in element (2, 2).");
			Assert::AreEqual(sinAngleF, resultF(2, 3), L"The Matrix3x3<float>::CreateRotationAroundX() function produced an incorrect result in element (2, 3).");

			Assert::AreEqual(0.0f, resultF(3, 1), L"The Matrix3x3<float>::CreateRotationAroundX() function produced an incorrect result in element (3, 1).");
			Assert::AreEqual(-sinAngleF, resultF(3, 2), L"The Matrix3x3<float>::CreateRotationAroundX() function produced an incorrect result in element (3, 2).");
			Assert::AreEqual(cosAngleF, resultF(3, 3), L"The Matrix3x3<float>::CreateRotationAroundX() function produced an incorrect result in element (3, 3).");

			// Test the static Matrix3x3<double> CreateRotationAroundX() function.
			const double piD = std::acos(-1.0);
			const double angleD = TestUtility::GetRandomDouble(-piD * 2.0f, piD * 2.0f);

			Matrix3x3d resultD = Matrix3x3d::CreateRotationAroundX(angleD);

			double cosAngleD = std::cos(angleD);
			double sinAngleD = std::sin(angleD);

			Assert::AreEqual(1.0, resultD(1, 1), L"The Matrix3x3<double>::CreateRotationAroundX() function produced an incorrect result in element (1, 1).");
			Assert::AreEqual(0.0, resultD(1, 2), L"The Matrix3x3<double>::CreateRotationAroundX() function produced an incorrect result in element (1, 2).");
			Assert::AreEqual(0.0, resultD(1, 3), L"The Matrix3x3<double>::CreateRotationAroundX() function produced an incorrect result in element (1, 3).");

			Assert::AreEqual(0.0, resultD(2, 1), L"The Matrix3x3<double>::CreateRotationAroundX() function produced an incorrect result in element (2, 1).");
			Assert::AreEqual(cosAngleD, resultD(2, 2), L"The Matrix3x3<double>::CreateRotationAroundX() function produced an incorrect result in element (2, 2).");
			Assert::AreEqual(sinAngleD, resultD(2, 3), L"The Matrix3x3<double>::CreateRotationAroundX() function produced an incorrect result in element (2, 3).");

			Assert::AreEqual(0.0, resultD(3, 1), L"The Matrix3x3<double>::CreateRotationAroundX() function produced an incorrect result in element (3, 1).");
			Assert::AreEqual(-sinAngleD, resultD(3, 2), L"The Matrix3x3<double>::CreateRotationAroundX() function produced an incorrect result in element (3, 2).");
			Assert::AreEqual(cosAngleD, resultD(3, 3), L"The Matrix3x3<double>::CreateRotationAroundX() function produced an incorrect result in element (3, 3).");
		}

		TEST_METHOD(M3_Create_Rotation_Around_Y)
		{
			// Test the static Matrix3x3<float> CreateRotationAroundY() function.
			const float piF = std::acos(-1.0f);
			const float angleF = TestUtility::GetRandomFloat(-piF * 2.0f, piF * 2.0f);

			Matrix3x3f resultF = Matrix3x3f::CreateRotationAroundY(angleF);

			float cosAngleF = std::cos(angleF);
			float sinAngleF = std::sin(angleF);

			Assert::AreEqual(cosAngleF, resultF(1, 1), L"The Matrix3x3<float>::CreateRotationAroundY() function produced an incorrect result in element (1, 1).");
			Assert::AreEqual(0.0f, resultF(1, 2), L"The Matrix3x3<float>::CreateRotationAroundY() function produced an incorrect result in element (1, 2).");
			Assert::AreEqual(-sinAngleF, resultF(1, 3), L"The Matrix3x3<float>::CreateRotationAroundY() function produced an incorrect result in element (1, 3).");

			Assert::AreEqual(0.0f, resultF(2, 1), L"The Matrix3x3<float>::CreateRotationAroundY() function produced an incorrect result in element (2, 1).");
			Assert::AreEqual(1.0f, resultF(2, 2), L"The Matrix3x3<float>::CreateRotationAroundY() function produced an incorrect result in element (2, 2).");
			Assert::AreEqual(0.0f, resultF(2, 3), L"The Matrix3x3<float>::CreateRotationAroundY() function produced an incorrect result in element (2, 3).");

			Assert::AreEqual(sinAngleF, resultF(3, 1), L"The Matrix3x3<float>::CreateRotationAroundY() function produced an incorrect result in element (3, 1).");
			Assert::AreEqual(0.0f, resultF(3, 2), L"The Matrix3x3<float>::CreateRotationAroundY() function produced an incorrect result in element (3, 2).");
			Assert::AreEqual(cosAngleF, resultF(3, 3), L"The Matrix3x3<float>::CreateRotationAroundY() function produced an incorrect result in element (3, 3).");

			// Test the static Matrix3x3<double> CreateRotationAroundY() function.
			const double piD = std::acos(-1.0);
			const double angleD = TestUtility::GetRandomDouble(-piD * 2.0, piD * 2.0);

			Matrix3x3d resultD = Matrix3x3d::CreateRotationAroundY(angleD);

			double cosAngleD = std::cos(angleD);
			double sinAngleD = std::sin(angleD);

			Assert::AreEqual(cosAngleD, resultD(1, 1), L"The Matrix3x3<double>::CreateRotationAroundY() function produced an incorrect result in element (1, 1).");
			Assert::AreEqual(0.0, resultD(1, 2), L"The Matrix3x3<double>::CreateRotationAroundY() function produced an incorrect result in element (1, 2).");
			Assert::AreEqual(-sinAngleD, resultD(1, 3), L"The Matrix3x3<double>::CreateRotationAroundY() function produced an incorrect result in element (1, 3).");

			Assert::AreEqual(0.0, resultD(2, 1), L"The Matrix3x3<double>::CreateRotationAroundY() function produced an incorrect result in element (2, 1).");
			Assert::AreEqual(1.0, resultD(2, 2), L"The Matrix3x3<double>::CreateRotationAroundY() function produced an incorrect result in element (2, 2).");
			Assert::AreEqual(0.0, resultD(2, 3), L"The Matrix3x3<double>::CreateRotationAroundY() function produced an incorrect result in element (2, 3).");

			Assert::AreEqual(sinAngleD, resultD(3, 1), L"The Matrix3x3<double>::CreateRotationAroundY() function produced an incorrect result in element (3, 1).");
			Assert::AreEqual(0.0, resultD(3, 2), L"The Matrix3x3<double>::CreateRotationAroundY() function produced an incorrect result in element (3, 2).");
			Assert::AreEqual(cosAngleD, resultD(3, 3), L"The Matrix3x3<double>::CreateRotationAroundY() function produced an incorrect result in element (3, 3).");
		}

		TEST_METHOD(M3_Create_Rotation_Around_Z)
		{
			// Test the static Matrix3x3<float> CreateRotationAroundZ() function.
			const float piF = std::acos(-1.0f);
			const float angleF = TestUtility::GetRandomFloat(-piF * 2.0f, piF * 2.0f);

			Matrix3x3f resultF = Matrix3x3f::CreateRotationAroundZ(angleF);

			float cosAngleF = std::cos(angleF);
			float sinAngleF = std::sin(angleF);

			Assert::AreEqual(cosAngleF, resultF(1, 1), L"The Matrix3x3<float>::CreateRotationAroundZ() function produced an incorrect result in element (1, 1).");
			Assert::AreEqual(sinAngleF, resultF(1, 2), L"The Matrix3x3<float>::CreateRotationAroundZ() function produced an incorrect result in element (1, 2).");
			Assert::AreEqual(0.0f, resultF(1, 3), L"The Matrix3x3<float>::CreateRotationAroundZ() function produced an incorrect result in element (1, 3).");

			Assert::AreEqual(-sinAngleF, resultF(2, 1), L"The Matrix3x3<float>::CreateRotationAroundZ() function produced an incorrect result in element (2, 1).");
			Assert::AreEqual(cosAngleF, resultF(2, 2), L"The Matrix3x3<float>::CreateRotationAroundZ() function produced an incorrect result in element (2, 2).");
			Assert::AreEqual(0.0f, resultF(2, 3), L"The Matrix3x3<float>::CreateRotationAroundZ() function produced an incorrect result in element (2, 3).");

			Assert::AreEqual(0.0f, resultF(3, 1), L"The Matrix3x3<float>::CreateRotationAroundZ() function produced an incorrect result in element (3, 1).");
			Assert::AreEqual(0.0f, resultF(3, 2), L"The Matrix3x3<float>::CreateRotationAroundZ() function produced an incorrect result in element (3, 2).");
			Assert::AreEqual(1.0f, resultF(3, 3), L"The Matrix3x3<float>::CreateRotationAroundZ() function produced an incorrect result in element (3, 3).");

			// Test the static Matrix3x3<double> CreateRotationAroundZ() function.
			const double piD = std::acos(-1.0);
			const double angleD = TestUtility::GetRandomDouble(-piD * 2.0f, piD * 2.0f);

			Matrix3x3d resultD = Matrix3x3d::CreateRotationAroundZ(angleD);

			double cosAngleD = std::cos(angleD);
			double sinAngleD = std::sin(angleD);

			Assert::AreEqual(cosAngleD, resultD(1, 1), L"The Matrix3x3<double>::CreateRotationAroundZ() function produced an incorrect result in element (1, 1).");
			Assert::AreEqual(sinAngleD, resultD(1, 2), L"The Matrix3x3<double>::CreateRotationAroundZ() function produced an incorrect result in element (1, 2).");
			Assert::AreEqual(0.0, resultD(1, 3), L"The Matrix3x3<double>::CreateRotationAroundZ() function produced an incorrect result in element (1, 3).");

			Assert::AreEqual(-sinAngleD, resultD(2, 1), L"The Matrix3x3<double>::CreateRotationAroundZ() function produced an incorrect result in element (2, 1).");
			Assert::AreEqual(cosAngleD, resultD(2, 2), L"The Matrix3x3<double>::CreateRotationAroundZ() function produced an incorrect result in element (2, 2).");
			Assert::AreEqual(0.0, resultD(2, 3), L"The Matrix3x3<double>::CreateRotationAroundZ() function produced an incorrect result in element (2, 3).");

			Assert::AreEqual(0.0, resultD(3, 1), L"The Matrix3x3<double>::CreateRotationAroundZ() function produced an incorrect result in element (3, 1).");
			Assert::AreEqual(0.0, resultD(3, 2), L"The Matrix3x3<double>::CreateRotationAroundZ() function produced an incorrect result in element (3, 2).");
			Assert::AreEqual(1.0, resultD(3, 3), L"The Matrix3x3<double>::CreateRotationAroundZ() function produced an incorrect result in element (3, 3).");
		}

	private:
		static const unsigned int ourRowCount = 3;
		static const unsigned int ourColumnCount = 3;
	};
}