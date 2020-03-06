#include "ProgramOptions.h"

ProgramOptions::ProgramOptions() :
	hasSeed(false),
	seed(0),
	generationType(GenerationType::NONE),
	iterations(0),
	useRandomProperty(true),
	property("") {}

ProgramOptions& ProgramOptions::withIterations(const unsigned int iterations)
{
	this->iterations = iterations;
	return *this;
}

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

ProgramOptions& ProgramOptions::withProperty(const std::string& property)
{
	this->property = property;
	this->useRandomProperty = false;
	return *this;
}

bool ProgramOptions::getHasSeed() const
{
	return hasSeed;
}

unsigned int ProgramOptions::getIterations() const
{
	return iterations;
}

unsigned int ProgramOptions::getSeed() const
{
	return seed;
}

GenerationType ProgramOptions::getGenerationType() const
{
	return generationType;
}

bool ProgramOptions::getUseRandomProperty() const
{
	return useRandomProperty;
}

std::string ProgramOptions::getProperty() const
{
	return property;
}

