#include "Random.h"

static std::default_random_engine generator;

unsigned int Random::GetSeed()
{
	return generator.default_seed;
}

void Random::SetSeed(unsigned int aSeed)
{
	generator.seed(aSeed);
}

float Random::Range(const float aMin, const float aMax)
{
	std::uniform_real_distribution<float> dist(aMin, aMax);
	return dist(generator);
}

int Random::Range(const int aMin, const int aMax)
{
	std::uniform_int_distribution<int> dist(aMin, aMax);
	return dist(generator);
}
