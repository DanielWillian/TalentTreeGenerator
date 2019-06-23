#pragma once

#include "TalentTree.h"
#include "BranchGenerator.h"
#include <vector>
#include <unordered_map>

class TalentTreeBranchGenerationData
{
public:
	TalentTreeBranchGenerationData() {}

	TalentTreeBranchGenerationData(
			const int inGeneratorIndex,
			const std::pair<int, int>& inTalentCount,
			const std::vector<std::string>& inTalentNames)
			: generatorIndex(inGeneratorIndex), talentCount(inTalentCount), talentNames(inTalentNames)
	{
	}

public:
	int generatorIndex;
	std::pair<int, int> talentCount;
	std::vector<std::string> talentNames;
};

class TalentTreeGenerator
{
public:
	TalentTreeGenerator(const std::vector<BranchGenerator*>& inBranchGenerators,
			const std::unordered_map<std::string, std::vector<std::string>>& inTalentBranchesNames);

	virtual std::unique_ptr<TalentTree> GenerateTalentTree();

private:
	std::unordered_map<std::string, std::unique_ptr<Talent>> GenerateBranch(const std::string& pathName);

	bool IsGreaterTalent(const std::string name);

	int GetGeneratorIndexFromTalentBranchName(const std::string name);

public:
	std::vector<BranchGenerator*> pathGenerators;
	std::unordered_map<std::string, TalentTreeBranchGenerationData> talentBranchesData;
	std::vector<std::vector<std::pair<int, std::pair<int, int>>>> pathCounts;
};

