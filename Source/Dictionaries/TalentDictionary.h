#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <memory>

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
	virtual const TalentDictEntry& GetDictEntry(const std::string& key) const
	{
		return **std::find_if(entries.begin(), entries.end(), [&key](const auto& e) { return e->key == key; });
	}

	virtual std::vector<TalentDictEntry*> GetDictEntries(const std::string& key) const;

	virtual std::vector<TalentDictEntry*> GetModifierEntries() const;

	virtual std::pair<int, int> GetPropertiesNumberRange() const { return {1, 1}; }

	virtual int GetFloatPrecision() const { return 100; }

public:
	static const int BASE = 0;
	static const int MODIFIER = 1;
	static const int BENEFICIAL = 2;
	static const int DETRIMENTAL = 3;

public:
	std::vector<std::unique_ptr<TalentDictEntry>> entries;
	int level;
};

