#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <utility>

class TalentDictEntry
{
public:
	TalentDictEntry(const std::string& inKey,
			const std::string& inModifier,
			const int inType,
			const std::pair<float, float>& inValues)
		: key(inKey), modifier(inModifier), type(inType), values(inValues)
	{
	}

public:
	std::string key;
	std::string modifier;
	int type;
	std::pair<float, float> values;
};

class TalentDictionary
{
public:
	virtual TalentDictEntry GetDictEntry(const std::string& key) const
	{
		return *std::find_if(entries.begin(), entries.end(), [&key](const auto e) { return e.key == key; });
	}

	virtual std::vector<TalentDictEntry> GetDictEntries(const std::string& key) const;

	virtual std::vector<TalentDictEntry> GetModifierEntries() const;

	virtual std::pair<int, int> GetPropertiesNumberRange() const { return {1, 1}; }

public:
	static const int BASE = 0;
	static const int MODIFIER = 1;

public:
	std::vector<TalentDictEntry> entries;
	int level;
};

