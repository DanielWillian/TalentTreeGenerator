#pragma once

enum class GenerationType
{
	NONE, TALENT_TREE, BRANCH
};

class ProgramOptions
{
public:
	ProgramOptions();

	ProgramOptions& withIterations(const unsigned int iterations);
	ProgramOptions& withSeed(const unsigned int seed);
	ProgramOptions& withGenerationType(const GenerationType generationType);

	bool getHasSeed() const;
	unsigned int getIterations() const;
	unsigned int getSeed() const;
	GenerationType getGenerationType() const;

private:
	bool hasSeed;
	unsigned int iterations;
	unsigned int seed;
	GenerationType generationType;
};

