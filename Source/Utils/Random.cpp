#include "Random.h"

int Random::GetRandomInt(const int min, const int max)
{
	std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}

float Random::GetRandomFloat(const float min, const float max)
{
	const float nextAfter = std::nextafter(max, std::numeric_limits<float>::max());
	std::uniform_real_distribution<float> dis(min, nextAfter);
	return dis(gen);
}

