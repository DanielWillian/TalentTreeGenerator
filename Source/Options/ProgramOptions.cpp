#include "ProgramOptions.h"

ProgramOptions::ProgramOptions() : hasSeed(false), seed(0), generationType(GenerationType::NONE) {}

ProgramOptions& ProgramOptions::withSeed(const unsigned int seed)
{
	this->seed = seed;
	this->hasSeed = true;
	return *this;
}

ProgramOptions& ProgramOptions::withGenerationType(const GenerationType generationType)
{
	this->generationType = generationType;
	return *this;
}

bool ProgramOptions::getHasSeed() const
{
	return hasSeed;
}

unsigned int ProgramOptions::getSeed() const
{
	return seed;
}

GenerationType ProgramOptions::getGenerationType() const
{
	return generationType;
}
