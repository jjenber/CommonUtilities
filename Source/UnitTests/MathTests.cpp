#include "pch.h"
#include "CppUnitTest.h"

#include <Math/Math.hpp>
#include <Math/Vector2.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<> static std::wstring ToString<CommonUtilities::Vector2f>(const class CommonUtilities::Vector2<float>& t) { return L"Vector2<float>"; }
		}
	}
}
namespace MathTests
{
	using namespace CommonUtilities;
	TEST_CLASS(Class)
	{
	public:
		TEST_METHOD(LerpFloat)
		{
			// positive
			float startPos = 0.f;
			float endPos = 10.f;
			Assert::AreEqual(5.f, Lerp(startPos, endPos, 0.5f));
			// positive reverse
			startPos = 10.f;
			endPos = 0.f;
			Assert::AreEqual(5.f, Lerp(startPos, endPos, 0.5f));

			// negative
			float startNeg = 0.f;
			float endNeg = -10.f;
			Assert::AreEqual(-5.f, Lerp(startNeg, endNeg, 0.5f));
		}
		TEST_METHOD(LerpVector)
		{
			Vector2f start = { 10.f, 10.f };
			Vector2f end = { 5.f, 5.f};
			Assert::AreEqual(Vector2f(7.5f, 7.5f), Lerp(start, end, 0.5f));
		}
		TEST_METHOD(MinValue)
		{
			Assert::AreEqual(5, Min(5, 6));
			Assert::AreNotEqual(6, Min(5, 6));
		}
		TEST_METHOD(MaxValue)
		{
			Assert::AreEqual(6, Max(5, 6));
			Assert::AreNotEqual(5, Max(5, 6));
		}
		TEST_METHOD(ClampValue)
		{
			Assert::AreEqual(10, Clamp(10, 6, 12));
			Assert::AreNotEqual(5, Clamp(5, 6, 12));
			Assert::AreNotEqual(13, Clamp(13, 6, 12));
			Assert::AreEqual(12, Clamp(23, 6, 12));
			Assert::AreEqual(6, Clamp(-12, 6, 12));
		}
		TEST_METHOD(SzudzikPairingFunctionTest)
		{
			int val = SzudzikPairingFunction(2000, 3000);
			Assert::AreEqual(36004000, val);
			int i = SzudzikPairingFunction(-2000, -3000);
			Assert::AreEqual(35992000, i);
		}
		TEST_METHOD(InvLerp)
		{
			Assert::AreEqual(0.5f, InverseLerp(0, 10, 5));
		}
	};
}