#pragma once

#include <random>

class Random
{
public:
	static Random& GetInstance()
	{
		static Random instance;
		return instance;
	}

	Random(Random const&) = delete;
	void operator=(Random const&) = delete;

	int GetRandomInt(const int min, const int max);

	float GetRandomFloat(const float min, const float max);

private:
	Random() {}

public:
	std::mt19937 gen;
};

