#include "Utility.hpp"
#include <random>
#include "UtilityFunctions.hpp"

namespace TestUtility
{
	std::mt19937 rEngine(6);

	float GetRandomFloat()
	{
		return GetRandomFloat(0, 1.f);
	}

	float GetRandomFloat(float aMin, float aMax)
	{
		std::uniform_real_distribution<float> rnd(aMin, aMax);
		return rnd(rEngine);
	}

	double GetRandomDouble(double aMin, double aMax)
	{
		std::uniform_real_distribution<double> rnd(aMin, aMax);
		return rnd(rEngine);
	}

	int GetRandomInt(int aMin, int aMax)
	{
		std::uniform_int_distribution<int> rnd(aMin, aMax);
		return rnd(rEngine);
	}
}