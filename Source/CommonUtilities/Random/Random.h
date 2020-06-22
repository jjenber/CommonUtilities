#pragma once

#include <random>
class Random
{
public:
	static unsigned int GetSeed();
	static void SetSeed(unsigned int aSeed);
	static float Range(const float aMin, const float aMax);
	static int   Range(const int aMin, const int aMax);
};
