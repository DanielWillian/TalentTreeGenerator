#include "stdafx.h"
#include "TalentDictionaryLevel5.h"

TalentDictionaryLevel5::TalentDictionaryLevel5()
{
	level = 5;
	std::vector<TalentDictEntry*> dictEntries;
	dictEntries.push_back(new TalentDictEntry{"attributes", "+", BASE, {20, 25}});

	for (auto* e : dictEntries)
	{
		entries.push_back(std::unique_ptr<TalentDictEntry>(e));
	}
}
