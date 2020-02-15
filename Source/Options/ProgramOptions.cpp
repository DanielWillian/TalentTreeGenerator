#include "ProgramOptions.h"

ProgramOptions::ProgramOptions() : hasSeed(false), seed(0) {}

ProgramOptions& ProgramOptions::withSeed(const unsigned int seed)
{
	this->seed = seed;
	this->hasSeed = true;
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
