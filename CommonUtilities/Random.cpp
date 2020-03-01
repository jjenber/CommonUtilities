#include "Random.h"

static std::default_random_engine generator;
static unsigned int ourSeed = generator.default_seed;

unsigned int Random::GetSeed()
{
	return ourSeed;
}

void Random::SetSeed(unsigned int aSeed)
{
	ourSeed = aSeed;
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
