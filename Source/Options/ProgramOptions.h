#pragma once

class ProgramOptions
{
public:
	ProgramOptions();

	ProgramOptions& withSeed(const unsigned int seed);

	bool getHasSeed() const;
	unsigned int getSeed() const;

private:
	bool hasSeed;
	unsigned int seed;
};

