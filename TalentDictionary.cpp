#include "stdafx.h"
#include "TalentDictionary.h"

std::vector<TalentDictEntry*> TalentDictionary::GetDictEntries(const std::string& key) const
{
	std::vector<TalentDictEntry*> result;
	for (const auto& entry : entries)
	{
		if (entry->key == key)
		{
			result.push_back(entry.get());
		}
	}
	return result;
}

std::vector<TalentDictEntry*> TalentDictionary::GetModifierEntries() const
{
	std::vector<TalentDictEntry*> result;
	for (const auto& entry : entries)
	{
		if (entry->type == MODIFIER)
		{
			result.push_back(entry.get());
		}
	}
	return result;
}

