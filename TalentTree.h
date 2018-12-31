#pragma once

#include "Talent.h"
#include <vector>
#include <memory>

class TalentTree
{
public:
	TalentTree(std::vector<std::vector<std::unique_ptr<Talent>>>& inOutTalentPaths)
	{
		talentPaths = std::move(inOutTalentPaths);
	}

public:
	std::vector<std::vector<std::unique_ptr<Talent>>> talentPaths;
};

