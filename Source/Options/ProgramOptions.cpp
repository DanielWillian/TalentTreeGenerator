#include "ProgramOptions.h"

ProgramOptions::ProgramOptions() :
	hasSeed(false),
	iterations(0),
	seed(0),
	generationType(GenerationType::NONE),
	useRandomProperty(true),
	property(""),
	measureTime(false) {}

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

ProgramOptions& ProgramOptions::withMeasureTime(const bool measureTime)
{
	this->measureTime = measureTime;
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

bool ProgramOptions::getMeasureTime() const
{
	return measureTime;
}

