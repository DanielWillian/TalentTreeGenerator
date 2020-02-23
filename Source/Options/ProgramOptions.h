#pragma once

enum class GenerationType
{
	NONE, TALENT_TREE, BRANCH
};

class ProgramOptions
{
public:
	ProgramOptions();

	ProgramOptions& withSeed(const unsigned int seed);
	ProgramOptions& withGenerationType(const GenerationType generationType);

	bool getHasSeed() const;
	unsigned int getSeed() const;
	GenerationType getGenerationType() const;

private:
	bool hasSeed;
	unsigned int seed;
	GenerationType generationType;
};

