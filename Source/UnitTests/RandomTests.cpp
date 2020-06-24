#include "pch.h"
#include "CppUnitTest.h"
#include <Random/Random.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace RandomTests
{
	TEST_CLASS(Class)
	{
	public:
		TEST_METHOD(RandomInt)
		{
			for (int i = 0; i < 20; i++)
			{
				Assert::AreNotEqual(2, Random::Range(2, 0));
				Assert::IsFalse(Random::Range(2, 0) < 0);
			}
		}
		TEST_METHOD(RandomFloat)
		{
			for (int i = 0; i < 20; i++)
			{
				Assert::AreNotEqual(2.1f, Random::Range(2.f, 0.f));
				Assert::IsFalse(Random::Range(2.f, 0.f) < 0);
			}
		}
		TEST_METHOD(Perlin)
		{
			float i = Random::PerlinNoise2D(0.5f, 1.f);
			float j = Random::PerlinNoise2D_0_1(0.5f, 1.f);
			float k = Random::PerlinNoise3D(0.5f, 1.f, 300.f);
			float l = Random::PerlinNoise3D_0_1(0.5f, 1.f, 300.f);
		}
	};
}
