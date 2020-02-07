#pragma once

class ProgramOptions
{
public:
	ProgramOptions();

	ProgramOptions& withNeedHelp(const bool needHelp);
	ProgramOptions& withSeed(const long seed);

	bool needHelp() const;
	bool hasSeed() const;
	long getSeed() const;

private:
	bool needHelp;
	bool hasSeed;
	long seed;
};

