#include "pch.h"
#include "CppUnitTest.h"

#include "Shared/Utility.hpp"
#include <Math/Matrix/Matrix4x4.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using Matrix4x4f = CommonUtilities::Matrix4x4<float>;
using Matrix4x4d = CommonUtilities::Matrix4x4<double>;
using Vector4f = CommonUtilities::Vector4<float>;
using Vector4d = CommonUtilities::Vector4<double>;

namespace Assignment5FastInverse
{		
	TEST_CLASS(Matrix4x4Tests)
	{
	public:
		// Make sure the multiply operator is working in this version.
		TEST_METHOD(M4_Multiply_Operator)
		{
			// Test the Matrix4x4<float> multiply operator function with an identity matrix.
			Matrix4x4f leftF, rightF;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					leftF(row, col) = TestUtility::GetRandomFloat();
					rightF(row, col) = TestUtility::GetRandomFloat();
				}
			}

			Matrix4x4f resultF;
			resultF = leftF * Matrix4x4f();

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(leftF(row, col), resultF(row, col), L"Matrix4x4<float>::operator* with the identity matrix should not change the matrix.");
				}
			}

			// Test the Matrix4x4<float> multiply operator function with a random matrix.
			resultF = leftF * rightF;
			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					float element = leftF(row, 1) * rightF(1, col) +
						leftF(row, 2) * rightF(2, col) +
						leftF(row, 3) * rightF(3, col) +
						leftF(row, 4) * rightF(4, col);

					Assert::AreEqual(element, resultF(row, col), L"Matrix4x4<float>::operator* with a random matrix produces incorrect results.");
				}
			}

			// Test the Matrix4x4<float> multiply operator function with a zero matrix.
			Matrix4x4f zeroF;
			zeroF(1, 1) = zeroF(2, 2) = zeroF(3, 3) = zeroF(4, 4) = 0.0f;

			resultF = leftF * zeroF;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(0.0f, resultF(row, col), L"Matrix4x4<float>::operator* with a zero matrix should result in a zero matrix.");
				}
			}

			// Test the Matrix4x4<double> multiply operator function with an identity matrix.
			Matrix4x4d leftD, rightD;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					leftD(row, col) = TestUtility::GetRandomDouble();
					rightD(row, col) = TestUtility::GetRandomDouble();
				}
			}

			Matrix4x4d resultD;
			resultD = leftD * Matrix4x4d();

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(leftD(row, col), resultD(row, col), L"Matrix4x4<double>::operator* with the identity matrix should not change the matrix.");
				}
			}

			// Test the Matrix4x4<double> multiply operator function with a random matrix.
			resultD = leftD * rightD;
			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					double element = leftD(row, 1) * rightD(1, col) +
						leftD(row, 2) * rightD(2, col) +
						leftD(row, 3) * rightD(3, col) +
						leftD(row, 4) * rightD(4, col);

					Assert::AreEqual(element, resultD(row, col), L"Matrix4x4<double>::operator* with a random matrix produces incorrect results.");
				}
			}

			// Test the Matrix4x4<double> multiply operator function with a zero matrix.
			Matrix4x4d zeroD;
			zeroD(1, 1) = zeroD(2, 2) = zeroD(3, 3) = zeroD(4, 4) = 0.0;

			resultD = leftD * zeroD;

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(0.0, resultD(row, col), L"Matrix4x4<double>::operator* with a zero matrix should result in a zero matrix.");
				}
			}
		}

		// Make sure CreateRotationAroundX() is working in this version.
		TEST_METHOD(M4_Create_Rotation_Around_X)
		{
			// Test the static Matrix4x4<float> CreateRotationAroundX() function.
			const float piF = std::acos(-1.0f);
			const float angleF = TestUtility::GetRandomFloat(-piF * 2.0f, piF * 2.0f);

			Matrix4x4f resultF = Matrix4x4f::CreateRotationAroundX(angleF);

			float cosAngleF = std::cos(angleF);
			float sinAngleF = std::sin(angleF);

			Assert::AreEqual(1.0f, resultF(1, 1), L"The Matrix4x4<float>::CreateRotationAroundX() function produced an incorrect result in element (1, 1).");
			Assert::AreEqual(0.0f, resultF(1, 2), L"The Matrix4x4<float>::CreateRotationAroundX() function produced an incorrect result in element (1, 2).");
			Assert::AreEqual(0.0f, resultF(1, 3), L"The Matrix4x4<float>::CreateRotationAroundX() function produced an incorrect result in element (1, 3).");
			Assert::AreEqual(0.0f, resultF(1, 4), L"The Matrix4x4<float>::CreateRotationAroundX() function produced an incorrect result in element (1, 4).");

			Assert::AreEqual(0.0f, resultF(2, 1), L"The Matrix4x4<float>::CreateRotationAroundX() function produced an incorrect result in element (2, 1).");
			Assert::AreEqual(cosAngleF, resultF(2, 2), L"The Matrix4x4<float>::CreateRotationAroundX() function produced an incorrect result in element (2, 2).");
			Assert::AreEqual(sinAngleF, resultF(2, 3), L"The Matrix4x4<float>::CreateRotationAroundX() function produced an incorrect result in element (2, 3).");
			Assert::AreEqual(0.0f, resultF(2, 4), L"The Matrix4x4<float>::CreateRotationAroundX() function produced an incorrect result in element (2, 4).");

			Assert::AreEqual(0.0f, resultF(3, 1), L"The Matrix4x4<float>::CreateRotationAroundX() function produced an incorrect result in element (3, 1).");
			Assert::AreEqual(-sinAngleF, resultF(3, 2), L"The Matrix4x4<float>::CreateRotationAroundX() function produced an incorrect result in element (3, 2).");
			Assert::AreEqual(cosAngleF, resultF(3, 3), L"The Matrix4x4<float>::CreateRotationAroundX() function produced an incorrect result in element (3, 3).");
			Assert::AreEqual(0.0f, resultF(3, 4), L"The Matrix4x4<float>::CreateRotationAroundX() function produced an incorrect result in element (3, 4).");

			Assert::AreEqual(0.0f, resultF(4, 1), L"The Matrix4x4<float>::CreateRotationAroundX() function produced an incorrect result in element (4, 1).");
			Assert::AreEqual(0.0f, resultF(4, 2), L"The Matrix4x4<float>::CreateRotationAroundX() function produced an incorrect result in element (4, 2).");
			Assert::AreEqual(0.0f, resultF(4, 3), L"The Matrix4x4<float>::CreateRotationAroundX() function produced an incorrect result in element (4, 3).");
			Assert::AreEqual(1.0f, resultF(4, 4), L"The Matrix4x4<float>::CreateRotationAroundX() function produced an incorrect result in element (4, 4).");

			// Test the static Matrix4x4<double> CreateRotationAroundX() function.
			const double piD = std::acos(-1.0);
			const double angleD = TestUtility::GetRandomDouble(-piD * 2.0f, piD * 2.0f);

			Matrix4x4d resultD = Matrix4x4d::CreateRotationAroundX(angleD);

			double cosAngleD = std::cos(angleD);
			double sinAngleD = std::sin(angleD);

			Assert::AreEqual(1.0, resultD(1, 1), L"The Matrix4x4<double>::CreateRotationAroundX() function produced an incorrect result in element (1, 1).");
			Assert::AreEqual(0.0, resultD(1, 2), L"The Matrix4x4<double>::CreateRotationAroundX() function produced an incorrect result in element (1, 2).");
			Assert::AreEqual(0.0, resultD(1, 3), L"The Matrix4x4<double>::CreateRotationAroundX() function produced an incorrect result in element (1, 3).");
			Assert::AreEqual(0.0, resultD(1, 4), L"The Matrix4x4<double>::CreateRotationAroundX() function produced an incorrect result in element (1, 4).");

			Assert::AreEqual(0.0, resultD(2, 1), L"The Matrix4x4<double>::CreateRotationAroundX() function produced an incorrect result in element (2, 1).");
			Assert::AreEqual(cosAngleD, resultD(2, 2), L"The Matrix4x4<double>::CreateRotationAroundX() function produced an incorrect result in element (2, 2).");
			Assert::AreEqual(sinAngleD, resultD(2, 3), L"The Matrix4x4<double>::CreateRotationAroundX() function produced an incorrect result in element (2, 3).");
			Assert::AreEqual(0.0, resultD(2, 4), L"The Matrix4x4<double>::CreateRotationAroundX() function produced an incorrect result in element (2, 4).");

			Assert::AreEqual(0.0, resultD(3, 1), L"The Matrix4x4<double>::CreateRotationAroundX() function produced an incorrect result in element (3, 1).");
			Assert::AreEqual(-sinAngleD, resultD(3, 2), L"The Matrix4x4<double>::CreateRotationAroundX() function produced an incorrect result in element (3, 2).");
			Assert::AreEqual(cosAngleD, resultD(3, 3), L"The Matrix4x4<double>::CreateRotationAroundX() function produced an incorrect result in element (3, 3).");
			Assert::AreEqual(0.0, resultD(3, 4), L"The Matrix4x4<double>::CreateRotationAroundX() function produced an incorrect result in element (3, 4).");

			Assert::AreEqual(0.0, resultD(4, 1), L"The Matrix4x4<double>::CreateRotationAroundX() function produced an incorrect result in element (4, 1).");
			Assert::AreEqual(0.0, resultD(4, 2), L"The Matrix4x4<double>::CreateRotationAroundX() function produced an incorrect result in element (4, 2).");
			Assert::AreEqual(0.0, resultD(4, 3), L"The Matrix4x4<double>::CreateRotationAroundX() function produced an incorrect result in element (4, 3).");
			Assert::AreEqual(1.0, resultD(4, 4), L"The Matrix4x4<double>::CreateRotationAroundX() function produced an incorrect result in element (4, 4).");
		}

		// Make sure CreateRotationAroundY() is working in this version.
		TEST_METHOD(M4_Create_Rotation_Around_Y)
		{
			// Test the static Matrix4x4<float> CreateRotationAroundY() function.
			const float piF = std::acos(-1.0f);
			const float angleF = TestUtility::GetRandomFloat(-piF * 2.0f, piF * 2.0f);

			Matrix4x4f resultF = Matrix4x4f::CreateRotationAroundY(angleF);

			float cosAngleF = std::cos(angleF);
			float sinAngleF = std::sin(angleF);

			Assert::AreEqual(cosAngleF, resultF(1, 1), L"The Matrix4x4<float>::CreateRotationAroundY() function produced an incorrect result in element (1, 1).");
			Assert::AreEqual(0.0f, resultF(1, 2), L"The Matrix4x4<float>::CreateRotationAroundY() function produced an incorrect result in element (1, 2).");
			Assert::AreEqual(-sinAngleF, resultF(1, 3), L"The Matrix4x4<float>::CreateRotationAroundY() function produced an incorrect result in element (1, 3).");
			Assert::AreEqual(0.0f, resultF(1, 4), L"The Matrix4x4<float>::CreateRotationAroundY() function produced an incorrect result in element (1, 4).");

			Assert::AreEqual(0.0f, resultF(2, 1), L"The Matrix4x4<float>::CreateRotationAroundY() function produced an incorrect result in element (2, 1).");
			Assert::AreEqual(1.0f, resultF(2, 2), L"The Matrix4x4<float>::CreateRotationAroundY() function produced an incorrect result in element (2, 2).");
			Assert::AreEqual(0.0f, resultF(2, 3), L"The Matrix4x4<float>::CreateRotationAroundY() function produced an incorrect result in element (2, 3).");
			Assert::AreEqual(0.0f, resultF(2, 4), L"The Matrix4x4<float>::CreateRotationAroundY() function produced an incorrect result in element (2, 4).");

			Assert::AreEqual(sinAngleF, resultF(3, 1), L"The Matrix4x4<float>::CreateRotationAroundY() function produced an incorrect result in element (3, 1).");
			Assert::AreEqual(0.0f, resultF(3, 2), L"The Matrix4x4<float>::CreateRotationAroundY() function produced an incorrect result in element (3, 2).");
			Assert::AreEqual(cosAngleF, resultF(3, 3), L"The Matrix4x4<float>::CreateRotationAroundY() function produced an incorrect result in element (3, 3).");
			Assert::AreEqual(0.0f, resultF(3, 4), L"The Matrix4x4<float>::CreateRotationAroundY() function produced an incorrect result in element (3, 4).");

			Assert::AreEqual(0.0f, resultF(4, 1), L"The Matrix4x4<float>::CreateRotationAroundY() function produced an incorrect result in element (4, 1).");
			Assert::AreEqual(0.0f, resultF(4, 2), L"The Matrix4x4<float>::CreateRotationAroundY() function produced an incorrect result in element (4, 2).");
			Assert::AreEqual(0.0f, resultF(4, 3), L"The Matrix4x4<float>::CreateRotationAroundY() function produced an incorrect result in element (4, 3).");
			Assert::AreEqual(1.0f, resultF(4, 4), L"The Matrix4x4<float>::CreateRotationAroundY() function produced an incorrect result in element (4, 4).");

			// Test the static Matrix4x4<double> CreateRotationAroundY() function.
			const double piD = std::acos(-1.0);
			const double angleD = TestUtility::GetRandomDouble(-piD * 2.0f, piD * 2.0f);

			Matrix4x4d resultD = Matrix4x4d::CreateRotationAroundY(angleD);

			double cosAngleD = std::cos(angleD);
			double sinAngleD = std::sin(angleD);

			Assert::AreEqual(cosAngleD, resultD(1, 1), L"The Matrix4x4<double>::CreateRotationAroundY() function produced an incorrect result in element (1, 1).");
			Assert::AreEqual(0.0, resultD(1, 2), L"The Matrix4x4<double>::CreateRotationAroundY() function produced an incorrect result in element (1, 2).");
			Assert::AreEqual(-sinAngleD, resultD(1, 3), L"The Matrix4x4<double>::CreateRotationAroundY() function produced an incorrect result in element (1, 3).");
			Assert::AreEqual(0.0, resultD(1, 4), L"The Matrix4x4<double>::CreateRotationAroundY() function produced an incorrect result in element (1, 4).");

			Assert::AreEqual(0.0, resultD(2, 1), L"The Matrix4x4<double>::CreateRotationAroundY() function produced an incorrect result in element (2, 1).");
			Assert::AreEqual(1.0, resultD(2, 2), L"The Matrix4x4<double>::CreateRotationAroundY() function produced an incorrect result in element (2, 2).");
			Assert::AreEqual(0.0, resultD(2, 3), L"The Matrix4x4<double>::CreateRotationAroundY() function produced an incorrect result in element (2, 3).");
			Assert::AreEqual(0.0, resultD(2, 4), L"The Matrix4x4<double>::CreateRotationAroundY() function produced an incorrect result in element (2, 4).");

			Assert::AreEqual(sinAngleD, resultD(3, 1), L"The Matrix4x4<double>::CreateRotationAroundY() function produced an incorrect result in element (3, 1).");
			Assert::AreEqual(0.0, resultD(3, 2), L"The Matrix4x4<double>::CreateRotationAroundY() function produced an incorrect result in element (3, 2).");
			Assert::AreEqual(cosAngleD, resultD(3, 3), L"The Matrix4x4<double>::CreateRotationAroundY() function produced an incorrect result in element (3, 3).");
			Assert::AreEqual(0.0, resultD(3, 4), L"The Matrix4x4<double>::CreateRotationAroundY() function produced an incorrect result in element (3, 4).");

			Assert::AreEqual(0.0, resultD(4, 1), L"The Matrix4x4<double>::CreateRotationAroundY() function produced an incorrect result in element (4, 1).");
			Assert::AreEqual(0.0, resultD(4, 2), L"The Matrix4x4<double>::CreateRotationAroundY() function produced an incorrect result in element (4, 2).");
			Assert::AreEqual(0.0, resultD(4, 3), L"The Matrix4x4<double>::CreateRotationAroundY() function produced an incorrect result in element (4, 3).");
			Assert::AreEqual(1.0, resultD(4, 4), L"The Matrix4x4<double>::CreateRotationAroundY() function produced an incorrect result in element (4, 4).");
		}

		// Make sure CreateRotationAroundZ() is working in this version.
		TEST_METHOD(M4_Create_Rotation_Around_Z)
		{
			// Test the static Matrix4x4<float> CreateRotationAroundZ() function.
			const float piF = std::acos(-1.0f);
			const float angleF = TestUtility::GetRandomFloat(-piF * 2.0f, piF * 2.0f);

			Matrix4x4f resultF = Matrix4x4f::CreateRotationAroundZ(angleF);

			float cosAngleF = std::cos(angleF);
			float sinAngleF = std::sin(angleF);

			Assert::AreEqual(cosAngleF, resultF(1, 1), L"The Matrix4x4<float>::CreateRotationAroundZ() function produced an incorrect result in element (1, 1).");
			Assert::AreEqual(sinAngleF, resultF(1, 2), L"The Matrix4x4<float>::CreateRotationAroundZ() function produced an incorrect result in element (1, 2).");
			Assert::AreEqual(0.0f, resultF(1, 3), L"The Matrix4x4<float>::CreateRotationAroundZ() function produced an incorrect result in element (1, 3).");
			Assert::AreEqual(0.0f, resultF(1, 4), L"The Matrix4x4<float>::CreateRotationAroundZ() function produced an incorrect result in element (1, 4).");

			Assert::AreEqual(-sinAngleF, resultF(2, 1), L"The Matrix4x4<float>::CreateRotationAroundZ() function produced an incorrect result in element (2, 1).");
			Assert::AreEqual(cosAngleF, resultF(2, 2), L"The Matrix4x4<float>::CreateRotationAroundZ() function produced an incorrect result in element (2, 2).");
			Assert::AreEqual(0.0f, resultF(2, 3), L"The Matrix4x4<float>::CreateRotationAroundZ() function produced an incorrect result in element (2, 3).");
			Assert::AreEqual(0.0f, resultF(2, 4), L"The Matrix4x4<float>::CreateRotationAroundZ() function produced an incorrect result in element (2, 4).");

			Assert::AreEqual(0.0f, resultF(3, 1), L"The Matrix4x4<float>::CreateRotationAroundZ() function produced an incorrect result in element (3, 1).");
			Assert::AreEqual(0.0f, resultF(3, 2), L"The Matrix4x4<float>::CreateRotationAroundZ() function produced an incorrect result in element (3, 2).");
			Assert::AreEqual(1.0f, resultF(3, 3), L"The Matrix4x4<float>::CreateRotationAroundZ() function produced an incorrect result in element (3, 3).");
			Assert::AreEqual(0.0f, resultF(3, 4), L"The Matrix4x4<float>::CreateRotationAroundZ() function produced an incorrect result in element (3, 4).");

			Assert::AreEqual(0.0f, resultF(4, 1), L"The Matrix4x4<float>::CreateRotationAroundZ() function produced an incorrect result in element (4, 1).");
			Assert::AreEqual(0.0f, resultF(4, 2), L"The Matrix4x4<float>::CreateRotationAroundZ() function produced an incorrect result in element (4, 2).");
			Assert::AreEqual(0.0f, resultF(4, 3), L"The Matrix4x4<float>::CreateRotationAroundZ() function produced an incorrect result in element (4, 3).");
			Assert::AreEqual(1.0f, resultF(4, 4), L"The Matrix4x4<float>::CreateRotationAroundZ() function produced an incorrect result in element (4, 4).");

			// Test the static Matrix4x4<double> CreateRotationAroundZ() function.
			const double piD = std::acos(-1.0);
			const double angleD = TestUtility::GetRandomDouble(-piD * 2.0f, piD * 2.0f);

			Matrix4x4d resultD = Matrix4x4d::CreateRotationAroundZ(angleD);

			double cosAngleD = std::cos(angleD);
			double sinAngleD = std::sin(angleD);

			Assert::AreEqual(cosAngleD, resultD(1, 1), L"The Matrix4x4<double>::CreateRotationAroundZ() function produced an incorrect result in element (1, 1).");
			Assert::AreEqual(sinAngleD, resultD(1, 2), L"The Matrix4x4<double>::CreateRotationAroundZ() function produced an incorrect result in element (1, 2).");
			Assert::AreEqual(0.0, resultD(1, 3), L"The Matrix4x4<double>::CreateRotationAroundZ() function produced an incorrect result in element (1, 3).");
			Assert::AreEqual(0.0, resultD(1, 4), L"The Matrix4x4<double>::CreateRotationAroundZ() function produced an incorrect result in element (1, 4).");

			Assert::AreEqual(-sinAngleD, resultD(2, 1), L"The Matrix4x4<double>::CreateRotationAroundZ() function produced an incorrect result in element (2, 1).");
			Assert::AreEqual(cosAngleD, resultD(2, 2), L"The Matrix4x4<double>::CreateRotationAroundZ() function produced an incorrect result in element (2, 2).");
			Assert::AreEqual(0.0, resultD(2, 3), L"The Matrix4x4<double>::CreateRotationAroundZ() function produced an incorrect result in element (2, 3).");
			Assert::AreEqual(0.0, resultD(2, 4), L"The Matrix4x4<double>::CreateRotationAroundZ() function produced an incorrect result in element (2, 4).");

			Assert::AreEqual(0.0, resultD(3, 1), L"The Matrix4x4<double>::CreateRotationAroundZ() function produced an incorrect result in element (3, 1).");
			Assert::AreEqual(0.0, resultD(3, 2), L"The Matrix4x4<double>::CreateRotationAroundZ() function produced an incorrect result in element (3, 2).");
			Assert::AreEqual(1.0, resultD(3, 3), L"The Matrix4x4<double>::CreateRotationAroundZ() function produced an incorrect result in element (3, 3).");
			Assert::AreEqual(0.0, resultD(3, 4), L"The Matrix4x4<double>::CreateRotationAroundZ() function produced an incorrect result in element (3, 4).");

			Assert::AreEqual(0.0, resultD(4, 1), L"The Matrix4x4<double>::CreateRotationAroundZ() function produced an incorrect result in element (4, 1).");
			Assert::AreEqual(0.0, resultD(4, 2), L"The Matrix4x4<double>::CreateRotationAroundZ() function produced an incorrect result in element (4, 2).");
			Assert::AreEqual(0.0, resultD(4, 3), L"The Matrix4x4<double>::CreateRotationAroundZ() function produced an incorrect result in element (4, 3).");
			Assert::AreEqual(1.0, resultD(4, 4), L"The Matrix4x4<double>::CreateRotationAroundZ() function produced an incorrect result in element (4, 4).");
		}

		TEST_METHOD(Get_Fast_Inverse_X_Rotation)
		{
			// Test the Matrix4x4<float> GetFastInverse() function on an x rotation matrix.
			const float twoPiF = std::acos(-1.0f) * 2.0f;
			float angleF = TestUtility::GetRandomFloat(-twoPiF, twoPiF);

			Matrix4x4f rotationXInvF(Matrix4x4f::GetFastInverse(Matrix4x4f::CreateRotationAroundX(angleF)));
			Matrix4x4f rotationXNegF(Matrix4x4f::CreateRotationAroundX(-angleF));

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(rotationXNegF(row, col), rotationXInvF(row, col), L"Matrix4x4<float>::GetFastInverse() of a rotation matrix (around x) should result in a rotation matrix of the negative angle.");
				}
			}

			// Test the Matrix4x4<double> GetFastInverse() function on an x rotation matrix.
			const double twoPiD = std::acos(-1.0) * 2.0;
			double angleD = TestUtility::GetRandomDouble(-twoPiD, twoPiD);

			Matrix4x4d rotationXInvD(Matrix4x4d::GetFastInverse(Matrix4x4d::CreateRotationAroundX(angleD)));
			Matrix4x4d rotationXNegD(Matrix4x4d::CreateRotationAroundX(-angleD));

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(rotationXNegD(row, col), rotationXInvD(row, col), L"Matrix4x4<double>::GetFastInverse() of a rotation matrix (around x) should result in a rotation matrix of the negative angle.");
				}
			}
		}

		TEST_METHOD(Get_Fast_Inverse_Y_Rotation)
		{
			// Test the Matrix4x4<float> GetFastInverse() function on an y rotation matrix.
			const float twoPiF = std::acos(-1.0f) * 2.0f;
			float angleF = TestUtility::GetRandomFloat(-twoPiF, twoPiF);

			Matrix4x4f rotationYInvF(Matrix4x4f::GetFastInverse(Matrix4x4f::CreateRotationAroundY(angleF)));
			Matrix4x4f rotationYNegF(Matrix4x4f::CreateRotationAroundY(-angleF));

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(rotationYNegF(row, col), rotationYInvF(row, col), L"Matrix4x4<float>::GetFastInverse() of a rotation matrix (around y) should result in a rotation matrix of the negative angle.");
				}
			}

			// Test the Matrix4x4<double> GetFastInverse() function on an y rotation matrix.
			const double twoPiD = std::acos(-1.0) * 2.0;
			double angleD = TestUtility::GetRandomDouble(-twoPiD, twoPiD);

			Matrix4x4d rotationYInvD(Matrix4x4d::GetFastInverse(Matrix4x4d::CreateRotationAroundY(angleD)));
			Matrix4x4d rotationYNegD(Matrix4x4d::CreateRotationAroundY(-angleD));

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(rotationYNegD(row, col), rotationYInvD(row, col), L"Matrix4x4<double>::GetFastInverse() of a rotation matrix (around y) should result in a rotation matrix of the negative angle.");
				}
			}
		}

		TEST_METHOD(Get_Fast_Inverse_Z_Rotation)
		{
			// Test the Matrix4x4<float> GetFastInverse() function on an z rotation matrix.
			const float twoPiF = std::acos(-1.0f) * 2.0f;
			float angleF = TestUtility::GetRandomFloat(-twoPiF, twoPiF);

			Matrix4x4f rotationZInvF(Matrix4x4f::GetFastInverse(Matrix4x4f::CreateRotationAroundZ(angleF)));
			Matrix4x4f rotationZNegF(Matrix4x4f::CreateRotationAroundZ(-angleF));

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(rotationZNegF(row, col), rotationZInvF(row, col), L"Matrix4x4<float>::GetFastInverse() of a rotation matrix (around z) should result in a rotation matrix of the negative angle.");
				}
			}

			// Test the Matrix4x4<double> GetFastInverse() function on an z rotation matrix.
			const double twoPiD = std::acos(-1.0) * 2.0;
			double angleD = TestUtility::GetRandomDouble(-twoPiD, twoPiD);

			Matrix4x4d rotationZInvD(Matrix4x4d::GetFastInverse(Matrix4x4d::CreateRotationAroundZ(angleD)));
			Matrix4x4d rotationZNegD(Matrix4x4d::CreateRotationAroundZ(-angleD));

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(rotationZNegD(row, col), rotationZInvD(row, col), L"Matrix4x4<double>::GetFastInverse() of a rotation matrix (around z) should result in a rotation matrix of the negative angle.");
				}
			}
		}

		TEST_METHOD(Get_Fast_Inverse_XYZ_Rotation)
		{
			// Test the Matrix4x4<float> GetFastInverse() function on an x rotation matrix.
			const float twoPiF = std::acos(-1.0f) * 2.0f;
			float xAngleF = TestUtility::GetRandomFloat(-twoPiF, twoPiF);
			float yAngleF = TestUtility::GetRandomFloat(-twoPiF, twoPiF);
			float zAngleF = TestUtility::GetRandomFloat(-twoPiF, twoPiF);

			Matrix4x4f rotationXYZf(Matrix4x4f::CreateRotationAroundX(xAngleF) * Matrix4x4f::CreateRotationAroundY(yAngleF) * Matrix4x4f::CreateRotationAroundZ(zAngleF));
			
			Matrix4x4f rotationInvF(Matrix4x4f::GetFastInverse(rotationXYZf));
			Matrix4x4f rotationNegF(Matrix4x4f::CreateRotationAroundZ(-zAngleF) * (Matrix4x4f::CreateRotationAroundY(-yAngleF) * Matrix4x4f::CreateRotationAroundX(-xAngleF)));

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(rotationNegF(row, col), rotationInvF(row, col), L"Matrix4x4<float>::GetFastInverse() of the matrices\n" \
						"CreateRotationAroundX(xAngle) * CreateRotationAroundY(yAngle) * CreateRotationAroundZ(zAngle) should equal\n" \
						"CreateRotationAroundZ(-zAngle) * (CreateRotationAroundY(-yAngle) * CreateRotationAroundX(-xAngle))");
				}
			}

			// Test the Matrix4x4<double> GetFastInverse() function on an x rotation matrix.
			const double twoPiD = std::acos(-1.0) * 2.0;
			double xAngleD = TestUtility::GetRandomDouble(-twoPiD, twoPiD);
			double yAngleD = TestUtility::GetRandomDouble(-twoPiD, twoPiD);
			double zAngleD = TestUtility::GetRandomDouble(-twoPiD, twoPiD);

			Matrix4x4d rotationXYZd(Matrix4x4d::CreateRotationAroundX(xAngleD) * Matrix4x4d::CreateRotationAroundY(yAngleD) * Matrix4x4d::CreateRotationAroundZ(zAngleD));

			Matrix4x4d rotationInvD(Matrix4x4d::GetFastInverse(rotationXYZd));
			Matrix4x4d rotationNegD(Matrix4x4d::CreateRotationAroundZ(-zAngleD) * (Matrix4x4d::CreateRotationAroundY(-yAngleD) * Matrix4x4d::CreateRotationAroundX(-xAngleD)));

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(rotationNegD(row, col), rotationInvD(row, col), L"Matrix4x4<double>::GetFastInverse() of the matrices\n" \
						"CreateRotationAroundX(xAngle) * CreateRotationAroundY(yAngle) * CreateRotationAroundZ(zAngle) should equal\n" \
						"CreateRotationAroundZ(-zAngle) * (CreateRotationAroundY(-yAngle) * CreateRotationAroundX(-xAngle))");
				}
			}
		}

		TEST_METHOD(Get_Fast_Inverse_Translation)
		{
			// Test the Matrix4x4<float> GetFastInverse() function on a translation matrix.
			float xTranslationF = TestUtility::GetRandomFloat(-1000.0f, 1000.0f);
			float yTranslationF = TestUtility::GetRandomFloat(-1000.0f, 1000.0f);
			float zTranslationF = TestUtility::GetRandomFloat(-1000.0f, 1000.0f);

			Matrix4x4f translationF;
			translationF(4, 1) = xTranslationF;
			translationF(4, 2) = yTranslationF;
			translationF(4, 3) = zTranslationF;

			Matrix4x4f translationInvF(Matrix4x4f::GetFastInverse(translationF));

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount - 1; ++row)
				{
					Assert::AreEqual((col == row ? 1.0f : 0.0f), translationInvF(row, col), L"A translation matrix upper left 3x3 part is the identity matrix - Matrix4x4<float>::GetFastInverse() shouldn't change that.");
				}
			}

			Assert::AreEqual(-xTranslationF, translationInvF(4, 1), L"Matrix4x4<float>::GetFastInverse() of a translation should result in a translation matrix of the negative position, but the x value is wrong.");
			Assert::AreEqual(-yTranslationF, translationInvF(4, 2), L"Matrix4x4<float>::GetFastInverse() of a translation should result in a translation matrix of the negative position, but the y value is wrong.");
			Assert::AreEqual(-zTranslationF, translationInvF(4, 3), L"Matrix4x4<float>::GetFastInverse() of a translation should result in a translation matrix of the negative position, but the z value is wrong.");

			// Test the Matrix4x4<double> GetFastInverse() function on a translation matrix.
			double xTranslationD = TestUtility::GetRandomDouble(-1000.0, 1000.0);
			double yTranslationD = TestUtility::GetRandomDouble(-1000.0, 1000.0);
			double zTranslationD = TestUtility::GetRandomDouble(-1000.0, 1000.0);

			Matrix4x4d translationD;
			translationD(4, 1) = xTranslationD;
			translationD(4, 2) = yTranslationD;
			translationD(4, 3) = zTranslationD;

			Matrix4x4d translationInvD(Matrix4x4d::GetFastInverse(translationD));

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount - 1; ++row)
				{
					Assert::AreEqual((col == row ? 1.0 : 0.0), translationInvD(row, col), L"A translation matrix upper left 3x3 part is the identity matrix - Matrix4x4<double>::GetFastInverse() shouldn't change that.");
				}
			}

			Assert::AreEqual(-xTranslationD, translationInvD(4, 1), L"Matrix4x4<double>::GetFastInverse() of a translation should result in a translation matrix of the negative position, but the x value is wrong.");
			Assert::AreEqual(-yTranslationD, translationInvD(4, 2), L"Matrix4x4<double>::GetFastInverse() of a translation should result in a translation matrix of the negative position, but the y value is wrong.");
			Assert::AreEqual(-zTranslationD, translationInvD(4, 3), L"Matrix4x4<double>::GetFastInverse() of a translation should result in a translation matrix of the negative position, but the z value is wrong.");
		}

		TEST_METHOD(Get_Fast_Inverse_XYZ_Rotation_Translation)
		{
			// Test the Matrix4x4<float> GetFastInverse() function on an xyz rotation and translation matrix.
			const float twoPiF = std::acos(-1.0f) * 2.0f;
			float xAngleF = TestUtility::GetRandomFloat(-twoPiF, twoPiF);
			float yAngleF = TestUtility::GetRandomFloat(-twoPiF, twoPiF);
			float zAngleF = TestUtility::GetRandomFloat(-twoPiF, twoPiF);

			float xTranslationF = TestUtility::GetRandomFloat(-1000.0f, 1000.0f);
			float yTranslationF = TestUtility::GetRandomFloat(-1000.0f, 1000.0f);
			float zTranslationF = TestUtility::GetRandomFloat(-1000.0f, 1000.0f);

			Matrix4x4f translationF;
			translationF(4, 1) = xTranslationF;
			translationF(4, 2) = yTranslationF;
			translationF(4, 3) = zTranslationF;

			Matrix4x4f rotationXYZf(Matrix4x4f::CreateRotationAroundX(xAngleF) * Matrix4x4f::CreateRotationAroundY(yAngleF) * Matrix4x4f::CreateRotationAroundZ(zAngleF));
			Matrix4x4f transformationInvF(Matrix4x4f::GetFastInverse(rotationXYZf * translationF));

			Matrix4x4f translationNegF;
			translationNegF(4, 1) = -xTranslationF;
			translationNegF(4, 2) = -yTranslationF;
			translationNegF(4, 3) = -zTranslationF;

			Matrix4x4f transformationNegF(translationNegF *
				(Matrix4x4f::CreateRotationAroundZ(-zAngleF) * 
				(Matrix4x4f::CreateRotationAroundY(-yAngleF) * Matrix4x4f::CreateRotationAroundX(-xAngleF))));

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(transformationNegF(row, col), transformationInvF(row, col), L"Matrix4x4<float>::GetFastInverse() of the matrices\n" \
						"CreateRotationAroundX(xAngle) * CreateRotationAroundY(yAngle) * CreateRotationAroundZ(zAngle) * Translation(position) should equal\n" \
						"Translation(-position) * CreateRotationAroundZ(-zAngle) * (CreateRotationAroundY(-yAngle) * CreateRotationAroundX(-xAngle))");
				}
			}



			// Test the Matrix4x4<double> GetFastInverse() function on an xyz rotation and translation matrix.
			const double twoPiD = std::acos(-1.0) * 2.0;
			double xAngleD = TestUtility::GetRandomDouble(-twoPiD, twoPiD);
			double yAngleD = TestUtility::GetRandomDouble(-twoPiD, twoPiD);
			double zAngleD = TestUtility::GetRandomDouble(-twoPiD, twoPiD);

			double xTranslationD = TestUtility::GetRandomDouble(-1000.0, 1000.0);
			double yTranslationD = TestUtility::GetRandomDouble(-1000.0, 1000.0);
			double zTranslationD = TestUtility::GetRandomDouble(-1000.0, 1000.0);

			Matrix4x4d translationD;
			translationD(4, 1) = xTranslationD;
			translationD(4, 2) = yTranslationD;
			translationD(4, 3) = zTranslationD;

			Matrix4x4d rotationXYZd(Matrix4x4d::CreateRotationAroundX(xAngleD) * Matrix4x4d::CreateRotationAroundY(yAngleD) * Matrix4x4d::CreateRotationAroundZ(zAngleD));
			Matrix4x4d transformationInvD(Matrix4x4d::GetFastInverse(rotationXYZd * translationD));

			Matrix4x4d translationNegD;
			translationNegD(4, 1) = -xTranslationD;
			translationNegD(4, 2) = -yTranslationD;
			translationNegD(4, 3) = -zTranslationD;

			Matrix4x4d transformationNegD(translationNegD *
				(Matrix4x4d::CreateRotationAroundZ(-zAngleD) *
				(Matrix4x4d::CreateRotationAroundY(-yAngleD) * Matrix4x4d::CreateRotationAroundX(-xAngleD))));

			for (unsigned int col = 1; col <= ourColumnCount; ++col)
			{
				for (unsigned int row = 1; row <= ourRowCount; ++row)
				{
					Assert::AreEqual(transformationNegD(row, col), transformationInvD(row, col), L"Matrix4x4<float>::GetFastInverse() of the matrices\n" \
						"CreateRotationAroundX(xAngle) * CreateRotationAroundY(yAngle) * CreateRotationAroundZ(zAngle) * Translation(position) should equal\n" \
						"Translation(-position) * CreateRotationAroundZ(-zAngle) * (CreateRotationAroundY(-yAngle) * CreateRotationAroundX(-xAngle))");
				}
			}
		}

	private:
		static const unsigned int ourRowCount = 4;
		static const unsigned int ourColumnCount = 4;
	};
}