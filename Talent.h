#pragma once

#include "TalentEntry.h"
#include <vector>

class Talent
{
public:
	Talent(const std::vector<TalentEntry>& inTalentEntries)
			: talentEntries(inTalentEntries)
	{
	}

public:
	std::vector<TalentEntry> talentEntries;
};

