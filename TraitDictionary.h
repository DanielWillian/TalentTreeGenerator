#pragma once

#include <string>
#include <vector>

class TraitDictEntry
{
public:
	TraitDictEntry(const std::string& inKey, const int inType, const std::vector<std::string>& inValues)
		: key(inKey), type(inType), values(inValues)
	{
	}

public:
	std::string key;
	int type;
	std::vector<std::string> values;
};

class TraitDictionary
{
public:
	TraitDictionary();

public:
	static const int TERMINAL = 0;
	static const int ALTERNATIVES = 1;
	static const int CONCATENATIONS = 2;

public:
	std::vector<TraitDictEntry> entries;
};

