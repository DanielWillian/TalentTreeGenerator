#include "stdafx.h"
#include "TalentDictionaryLevel5.h"
#include "Utils/Constants.h"

TalentDictionaryLevel5::TalentDictionaryLevel5()
{
	level = 5;
	std::vector<TalentDictEntry*> dictEntries;
	dictEntries.push_back(new TalentDictEntry{HEALTH, "+", BASE, {35.0f, 40.0f}});
	dictEntries.push_back(new TalentDictEntry{NO_DAMAGE_TYPE, "-", MODIFIER, {1.0f, 1.0f}});
	dictEntries.push_back(new TalentDictEntry{NO_WEAPON_TYPE, "-", MODIFIER, {1.0f, 1.0f}});

	for (auto* e : dictEntries)
	{
		entries.push_back(std::unique_ptr<TalentDictEntry>(e));
	}
}

