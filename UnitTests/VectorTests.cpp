#include "pch.h"
#include "CppUnitTest.h"
#include "..//CommonUtilities/Vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CommonUtilities;

namespace MathVectors
{
	TEST_CLASS(Vector2Test)
	{
	public:
		TEST_METHOD(CopyAssignment)
		{
			Vector2<float> v(0.f, 3.f);
			Vector2<float> v2 = v;

			Assert::AreEqual(3.f, v2.y);
		}
		TEST_METHOD(Length)
		{
			Vector2<float> vPos(0.f, 3.f);
			Vector2<float> vNeg(0.f, -3.f);

			Assert::AreEqual(3.f, vPos.Length());
			Assert::AreEqual(3.f, vNeg.Length());

			Vector2<float> zero;
			Assert::AreEqual(0.f, zero.Length());
		}

		TEST_METHOD(LengthSqr)
		{
			Vector2<float> vPos(0.f, 3.f);
			Vector2<float> vNeg(0.f, -3.f);

			Assert::AreEqual(9.f, vPos.LengthSqr());
			Assert::AreEqual(9.f, vNeg.LengthSqr());
		}

		TEST_METHOD(GetNormalized)
		{
			Vector2<float> vPos(5.f, 3.f);
			Vector2<float> nPos = vPos.GetNormalized();
			Assert::AreEqual(1.f, nPos.Length());

			Vector2<float> vNeg(-5.f, -3.f);
			Vector2<float> nNeg = vNeg.GetNormalized();
			Assert::AreEqual(1.f, nNeg.Length());
		}

		TEST_METHOD(Normalize)
		{
			Vector2<float> vPos(5.f, 3.f);
			vPos.Normalize();
			Assert::AreEqual(1.f, vPos.Length());

			Vector2<float> vNeg(-5.f, -3.f);
			vNeg.Normalize();
			Assert::AreEqual(1.f, vNeg.Length());
		}

		TEST_METHOD(Dot)
		{
			Vector2<float> v1(4.f, 1.f);
			Vector2<float> v2(2.f, 4.f);
			float dot = v1.Dot(v2);
			Assert::AreEqual(12.f, dot);
		}

		TEST_METHOD(OperatorAddition)
		{
			Vector2<float> vPos(5.f, 0.f);
			Vector2<float> v2Pos(2.f, 0.f);
				  
			Vector2<float> sum = vPos + v2Pos;
			Assert::AreEqual(7.f, sum.x);
			Assert::AreEqual(0.f, sum.y);
		}

		TEST_METHOD(OperatorSubtraction)
		{
			Vector2<float> vPos(5.f, 0.f);
			Vector2<float> v2Pos(2.f, 0.f);
				  
			Vector2<float> result = vPos - v2Pos;
			Assert::AreEqual(3.f, result.x);
			Assert::AreEqual(0.f, result.y);
		}

		TEST_METHOD(OperatorMultiplication)
		{
			Vector2<float> vPos(5.f, 1.f);
			float scalar = -3;

			auto result = vPos * scalar;
			auto result2 = scalar * vPos;

			Assert::AreEqual(-15.f, result.x);
			Assert::AreEqual(-3.f, result.y);

			Assert::AreEqual(-15.f, result2.x);
			Assert::AreEqual(-3.f, result2.y);
		}

		TEST_METHOD(OperatorDivision)
		{
			const Vector2<float> v(15.f, 3.f);
			const float posScalar = 3;
			const float negScalar = -3;

			auto result = v / posScalar;
			auto result2 = v / negScalar;

			Assert::AreEqual(5.f, result.x);
			Assert::AreEqual(1.f, result.y);

			Assert::AreEqual(-5.f, result2.x);
			Assert::AreEqual(-1.f, result2.y);
		}

		TEST_METHOD(OperatorCompoundAddition)
		{
			Vector2<float> vPos(5.f, 0.f);
			Vector2<float> v2Pos(2.f, 0.f);

			vPos += v2Pos;
			Assert::AreEqual(7.f, vPos.x);
			Assert::AreEqual(0.f, vPos.y);
		}

		TEST_METHOD(OperatorCompoundSubtraction)
		{
			Vector2<float> vPos(5.f, 0.f);
			Vector2<float> v2Pos(2.f, 1.f);

			vPos -= v2Pos;
			Assert::AreEqual(3.f, vPos.x);
			Assert::AreEqual(-1.f, vPos.y);
		}

		TEST_METHOD(OperatorCompoundMultiplication)
		{
			Vector2<float> vPos(5.f, 1.f);
			float scalar = -3;

			vPos *= scalar;

			Assert::AreEqual(-15.f, vPos.x);
			Assert::AreEqual(-3.f, vPos.y);
		}

		TEST_METHOD(OperatorCompoundDivision)
		{
			Vector2<float> vPos(15.f, -3.f);
			float scalar = 3;

			vPos /= scalar;

			Assert::AreEqual(5.f, vPos.x);
			Assert::AreEqual(-1.f, vPos.y);
		}
	};

	TEST_CLASS(Vector3Test)
	{
		TEST_METHOD(CopyAssignment)
		{
			Vector3<float> v(0.f, 3.f, 0.f);
			Vector3<float> v2 = v;

			Assert::AreEqual(3.f, v2.y);
		}
		TEST_METHOD(Length)
		{
			Vector3<float> vPos(0.f, 3.f, 0.f);
			Vector3<float> vNeg(0.f, -3.f, 0.f);

			Assert::AreEqual(3.f, vPos.Length());
			Assert::AreEqual(3.f, vNeg.Length());

			Vector3<float> zero;
			Assert::AreEqual(0.f, zero.Length());
		}

		TEST_METHOD(LengthSqr)
		{
			Vector3<float> vPos(0.f, 0.f, 3.f);
			Vector3<float> vNeg(0.f, 0.f, -3.f);

			Assert::AreEqual(9.f, vPos.LengthSqr());
			Assert::AreEqual(9.f, vNeg.LengthSqr());

			Vector3<float> zero;
			Assert::AreEqual(0.f, zero.Length());
		}

		TEST_METHOD(GetNormalized)
		{
			Vector3<float> vPos(5.f, 0.f, 3.f);
			Vector3<float> nPos = vPos.GetNormalized();
			Assert::AreEqual(1.f, nPos.Length());

			Vector3<float> vNeg(-5.f, 0.f, -3.f);
			Vector3<float> nNeg = vNeg.GetNormalized();
			Assert::AreEqual(1.f, nNeg.Length());
		}

		TEST_METHOD(Normalize)
		{
			Vector3<float> vPos(5.f, 0.f, 3.f);
			vPos.Normalize();
			Assert::AreEqual(1.f, vPos.Length());

			Vector3<float> vNeg(-5.f, 0.f, -3.f);
			vNeg.Normalize();
			Assert::AreEqual(1.f, vNeg.Length());
		}

		TEST_METHOD(Cross)
		{
			Vector3<float> v1(2.f, -1.f, 3.f);
			Vector3<float> v2(5.f, 1.f, -3.f);

			auto result = v1.Cross(v2);

			Assert::AreEqual(0.f, result.x);
			Assert::AreEqual(21.f, result.y);
			Assert::AreEqual(7.f, result.z);
		}

		TEST_METHOD(Dot)
		{
			Vector3<float> v1(4.f, 1.f, -8.f);
			Vector3<float> v2(2.f, 4.f, -4.f);
			float dot = v1.Dot(v2);
			Assert::AreEqual(44.f, dot);
		}

		TEST_METHOD(OperatorAddition)
		{
			Vector3<float> vPos(5.f, 0.f, 3.f);
			Vector3<float> v2Pos(2.f, 0.f, 1.f);

			Vector3<float> sum = vPos + v2Pos;
			Assert::AreEqual(7.f, sum.x);
			Assert::AreEqual(0.f, sum.y);
			Assert::AreEqual(4.f, sum.z);
		}

		TEST_METHOD(OperatorSubtraction)
		{
			Vector3<float> vPos(5.f, 0.f, 3.f);
			Vector3<float> v2Pos(2.f, 0.f, 1.f);

			Vector3<float> result = vPos - v2Pos;
			Assert::AreEqual(3.f, result.x);
			Assert::AreEqual(0.f, result.y);
			Assert::AreEqual(2.f, result.z);
		}

		TEST_METHOD(OperatorMultiplication)
		{
			Vector3<float> vPos(5.f, 1.f, 3.f);
			float scalar = -3;

			auto result  = vPos * scalar;
			auto result2 = scalar * vPos;

			Assert::AreEqual(-15.f, result.x);
			Assert::AreEqual(-3.f,  result.y);
			Assert::AreEqual(-9.f,  result.z);

			Assert::AreEqual(-15.f, result2.x);
			Assert::AreEqual(-3.f, result2.y);
			Assert::AreEqual(-9.f, result2.z);
		}

		TEST_METHOD(OperatorDivision)
		{
			const Vector3<float> v(15.f, 3.f, 9.f);
			const float posScalar = 3;
			const float negScalar = -3;

			auto result = v / posScalar;
			auto result2 = v / negScalar;

			Assert::AreEqual(5.f, result.x);
			Assert::AreEqual(1.f, result.y);
			Assert::AreEqual(3.f, result.z);

			Assert::AreEqual(-5.f, result2.x);
			Assert::AreEqual(-1.f, result2.y);
			Assert::AreEqual(-3.f, result2.z);
		}

		TEST_METHOD(OperatorCompoundAddition)
		{
			Vector3<float> vPos(5.f, 0.f, 3.f);
			Vector3<float> v2Pos(2.f, 0.f, 1.f);

			vPos += v2Pos;
			Assert::AreEqual(7.f, vPos.x);
			Assert::AreEqual(0.f, vPos.y);
			Assert::AreEqual(4.f, vPos.z);
		}

		TEST_METHOD(OperatorCompoundSubtraction)
		{
			Vector3<float> vPos(5.f, 0.f, 3.f);
			Vector3<float> v2Pos(2.f, 1.f, 1.f);

			vPos -= v2Pos;
			Assert::AreEqual(3.f, vPos.x);
			Assert::AreEqual(-1.f, vPos.y);
			Assert::AreEqual(2.f, vPos.z);
		}

		TEST_METHOD(OperatorCompoundMultiplication)
		{
			Vector3<float> vPos(5.f, 1.f, 3.f);
			float scalar = -3;

			vPos *= scalar;

			Assert::AreEqual(-15.f, vPos.x);
			Assert::AreEqual(-3.f, vPos.y);
			Assert::AreEqual(-9.f, vPos.z);
		}

		TEST_METHOD(OperatorCompoundDivision)
		{
			Vector3<float> vPos(15.f, -3.f, 9.f);
			float scalar = 3;

			vPos /= scalar;

			Assert::AreEqual(5.f, vPos.x);
			Assert::AreEqual(-1.f, vPos.y);
			Assert::AreEqual(3.f, vPos.z);
		}
	};

	TEST_CLASS(Vector4Test)
	{
		TEST_METHOD(CopyAssignment)
		{
			Vector4<float> v(1.f, 3.f, 2.f, 4.f);
			Vector4<float> v2 = v;

			Assert::AreEqual(3.f, v2.y);
			Assert::AreEqual(4.f, v2.w);
		}
		TEST_METHOD(Length)
		{
			Vector4<float> vPos(0.f, 3.f, 0.f, 4.f);
			Vector4<float> vNeg(0.f, -3.f, 0.f, -4.f);

			Assert::AreEqual(5.f, vPos.Length());
			Assert::AreEqual(5.f, vNeg.Length());

			Vector4<float> zero;
			Assert::AreEqual(0.f, zero.Length());
		}

		TEST_METHOD(LengthSqr)
		{
			Vector4<float> vPos(0.f, 3.f, 0.f, 4.f);
			Vector4<float> vNeg(0.f, -3.f, 0.f, -4.f);

			Assert::AreEqual(25.f, vPos.LengthSqr());
			Assert::AreEqual(25.f, vNeg.LengthSqr());

			Vector4<float> zero;
			Assert::AreEqual(0.f, zero.Length());
		}

		TEST_METHOD(GetNormalized)
		{
			Vector4<float> vPos(5.f, 0.f, 0.f, 3.f);
			Vector4<float> nPos = vPos.GetNormalized();
			Assert::AreEqual(1.f, nPos.Length());

			Vector4<float> vNeg(-5.f, 0.f, -0.f, -3.f);
			Vector4<float> nNeg = vNeg.GetNormalized();
			Assert::AreEqual(1.f, nNeg.Length());
		}

		TEST_METHOD(Normalize)
		{
			Vector4<float> vPos(5.f, 0.f, 0.f, 3.f);
			vPos.Normalize();
			Assert::AreEqual(1.f, vPos.Length());

			Vector4<float> vNeg(-5.f, 0.f, 0.f, -3.f);
			vNeg.Normalize();
			Assert::AreEqual(1.f, vNeg.Length());
		}

		TEST_METHOD(Dot)
		{
			Vector4<float> v1(4.f, 1.f, 1.f, -8.f);
			Vector4<float> v2(2.f, 4.f, 1.f, -4.f);
			float dot = v1.Dot(v2);
			Assert::AreEqual(45.f, dot);
		}

		TEST_METHOD(OperatorAddition)
		{
			Vector4<float> vPos(5.f, 0.f, 1.f, 2.f);
			Vector4<float> v2Pos(2.f, 0.f, 3.f, 3.f);

			Vector4<float> sum = vPos + v2Pos;
			Assert::AreEqual(7.f, sum.x);
			Assert::AreEqual(0.f, sum.y);
			Assert::AreEqual(4.f, sum.z);
			Assert::AreEqual(5.f, sum.w);
		}

		TEST_METHOD(OperatorSubtraction)
		{
			Vector4<float> vPos(5.f, 0.f, 1.f, 2.f);
			Vector4<float> v2Pos(2.f, 0.f, 3.f, 3.f);

			Vector4<float> result = vPos - v2Pos;
			Assert::AreEqual(3.f, result.x);
			Assert::AreEqual(0.f, result.y);
			Assert::AreEqual(-2.f, result.z);
			Assert::AreEqual(-1.f, result.w);
		}

		TEST_METHOD(OperatorMultiplication)
		{
			Vector4<float> vPos(5.f, 0.f, 1.f, 2.f);
			float scalar = -3;

			auto result = vPos * scalar;
			auto result2 = scalar * vPos;

			Assert::AreEqual(-15.f, result.x);
			Assert::AreEqual(0.f, result.y);
			Assert::AreEqual(-3.f, result.z);
			Assert::AreEqual(-6.f, result.w);

			Assert::AreEqual(-15.f, result2.x);
			Assert::AreEqual(0.f, result2.y);
			Assert::AreEqual(-3.f, result2.z);
			Assert::AreEqual(-6.f, result2.w);
		}

		TEST_METHOD(OperatorDivision)
		{
			const Vector4<float> v(15.f, 3.f, 9.f, 6.f);
			const float posScalar = 3;
			const float negScalar = -3;

			auto result = v / posScalar;
			auto result2 = v / negScalar;

			Assert::AreEqual(5.f, result.x);
			Assert::AreEqual(1.f, result.y);
			Assert::AreEqual(3.f, result.z);
			Assert::AreEqual(2.f, result.w);

			Assert::AreEqual(-5.f, result2.x);
			Assert::AreEqual(-1.f, result2.y);
			Assert::AreEqual(-3.f, result2.z);
			Assert::AreEqual(-2.f, result2.w);
		}

		TEST_METHOD(OperatorCompoundAddition)
		{
			Vector4<float> vPos(5.f, 0.f, 3.f, 4.f);
			Vector4<float> v2Pos(2.f, 0.f, 1.f, 6.f);

			vPos += v2Pos;
			Assert::AreEqual(7.f, vPos.x);
			Assert::AreEqual(0.f, vPos.y);
			Assert::AreEqual(4.f, vPos.z);
			Assert::AreEqual(10.f, vPos.w);
		}

		TEST_METHOD(OperatorCompoundSubtraction)
		{
			Vector4<float> vPos(5.f, 0.f, 3.f, 4.f);
			Vector4<float> v2Pos(2.f, 0.f, 1.f, 6.f);

			vPos -= v2Pos;
			Assert::AreEqual(3.f, vPos.x);
			Assert::AreEqual(0.f, vPos.y);
			Assert::AreEqual(2.f, vPos.z);
			Assert::AreEqual(-2.f, vPos.w);
		}

		TEST_METHOD(OperatorCompoundMultiplication)
		{
			Vector4<float> vPos(5.f, 1.f, 3.f, 6.f);
			float scalar = -3;

			vPos *= scalar;

			Assert::AreEqual(-15.f, vPos.x);
			Assert::AreEqual(-3.f, vPos.y);
			Assert::AreEqual(-9.f, vPos.z);
			Assert::AreEqual(-18.f, vPos.w);
		}

		TEST_METHOD(OperatorCompoundDivision)
		{
			Vector4<float> vPos(15.f, -3.f, 9.f, 18.f);
			float scalar = 3;

			vPos /= scalar;

			Assert::AreEqual(5.f, vPos.x);
			Assert::AreEqual(-1.f, vPos.y);
			Assert::AreEqual(3.f, vPos.z);
			Assert::AreEqual(6.f, vPos.w);
		}
	};
}