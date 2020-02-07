#include "ProgramOptions.h"

ProgramOptions::ProgramOptions() : needHelp(false), hasSeed(false), seed(0) {}

ProgramOptions& ProgramOptions::withNeedHelp(const bool needHelp)
{
	this->needHelp = needHelp;
	return *this;
}

ProgramOptions& ProgramOptions::withSeed(const long seed)
{
	this->seed = seed;
	this->hasSeed = true;
	return *this;
}

bool ProgramOptions::needHelp() const
{
	return needHelp;
}

bool ProgramOptions::hasSeed() const
{
	return hasSeed;
}

long ProgramOptions::getSeed() const
{
	return seed;
}
