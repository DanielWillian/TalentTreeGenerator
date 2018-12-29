#include "stdafx.h"
#include "TalentDictionaryLevel2.h"

TalentDictionaryLevel2::TalentDictionaryLevel2()
{
	level = 2;
	std::vector<TalentDictEntry*> dictEntries;
	dictEntries.push_back(new TalentDictEntry{"attributes", "+", BASE, {10.0f, 15.0f}});

	for (auto* e : dictEntries)
	{
		entries.push_back(std::unique_ptr<TalentDictEntry>(e));
	}
}

