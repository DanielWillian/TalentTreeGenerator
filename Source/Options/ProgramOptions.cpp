#include "ProgramOptions.h"

ProgramOptions::ProgramOptions() :
	hasSeed(false),
	iterations(0),
	seed(0),
	generationType(GenerationType::NONE),
	useRandomProperty(true),
	property(""),
	measureTime(false) {}

ProgramOptions& ProgramOptions::withIterations(const unsigned int newIterations)
{
	this->iterations = newIterations;
	return *this;
}

ProgramOptions& ProgramOptions::withSeed(const unsigned int newSeed)
{
	this->seed = newSeed;
	this->hasSeed = true;
	return *this;
}

ProgramOptions& ProgramOptions::withGenerationType(const GenerationType newGenerationType)
{
	this->generationType = newGenerationType;
	return *this;
}

ProgramOptions& ProgramOptions::withProperty(const std::string& newProperty)
{
	this->property = newProperty;
	this->useRandomProperty = false;
	return *this;
}

ProgramOptions& ProgramOptions::withMeasureTime(const bool newMeasureTime)
{
	this->measureTime = newMeasureTime;
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

