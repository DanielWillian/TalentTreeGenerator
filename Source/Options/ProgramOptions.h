#pragma once

#include <string>

enum class GenerationType
{
	NONE, TALENT_TREE, BRANCHES, BRANCH_1, BRANCH_4, BRANCH_7
};

class ProgramOptions
{
public:
	ProgramOptions();

	ProgramOptions& withIterations(const unsigned int iterations);
	ProgramOptions& withSeed(const unsigned int seed);
	ProgramOptions& withGenerationType(const GenerationType generationType);
	ProgramOptions& withProperty(const std::string& property);
	ProgramOptions& withMeasureTime(const bool measureTime);

	bool getHasSeed() const;
	unsigned int getIterations() const;
	unsigned int getSeed() const;
	GenerationType getGenerationType() const;
	bool getUseRandomProperty() const;
	std::string getProperty() const;
	bool getMeasureTime() const;

private:
	bool hasSeed;
	unsigned int iterations;
	unsigned int seed;
	GenerationType generationType;
	bool useRandomProperty;
	std::string property;
	bool measureTime;
};

