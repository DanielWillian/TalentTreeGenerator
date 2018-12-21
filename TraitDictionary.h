#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <memory>

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

	const TraitDictEntry& GetDictEntry(const std::string& key)
	{
		return **std::find_if(entries.begin(), entries.end(), [&key](const auto& e) { return e->key == key; });
	}

public:
	static const int TERMINAL = 0;
	static const int ALTERNATIVES = 1;
	static const int CONCATENATIONS = 2;

private:
	std::vector<std::unique_ptr<TraitDictEntry>> entries;
};

