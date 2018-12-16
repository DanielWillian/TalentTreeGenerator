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

	virtual std::string toString() const
	{
		std::string out = "{ ";
		for (auto& talentEntry : talentEntries)
		{
			out += talentEntry.toString() + ", ";
		}
		out += "}";
		return out;
	}

public:
	std::vector<TalentEntry> talentEntries;
};

