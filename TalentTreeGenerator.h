#pragma once

#include "TalentTree.h"
#include "PathGenerator.h"
#include <vector>

class TalentTreeGenerator
{
public:
	TalentTreeGenerator(const std::vector<PathGenerator*>& inPathGenerators);

	TalentTreeGenerator(const std::vector<PathGenerator*>& inPathGenerators,
			const std::vector<std::vector<std::pair<int, std::pair<int, int>>>>& inPathCounts)
	{
		pathGenerators = inPathGenerators;
		pathCounts = inPathCounts;
	}

	virtual std::unique_ptr<TalentTree> GenerateTalentTree();

public:
	std::vector<PathGenerator*> pathGenerators;
	std::vector<std::vector<std::pair<int, std::pair<int, int>>>> pathCounts;
};

