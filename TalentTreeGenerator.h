#pragma once

#include "TalentTree.h"
#include "PathGenerator.h"
#include <vector>
#include <unordered_map>

class TalentTreePathGenerationData
{
public:
	TalentTreePathGenerationData() {}

	TalentTreePathGenerationData(
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
	TalentTreeGenerator(const std::vector<PathGenerator*>& inPathGenerators,
			const std::unordered_map<std::string, std::vector<std::string>>& inTalentPathsNames);

	virtual std::unique_ptr<TalentTree> GenerateTalentTree();

private:
	std::unordered_map<std::string, std::unique_ptr<Talent>> GeneratePath(const std::string& pathName);

	bool IsGreaterTalent(const std::string name);

	int GetGeneratorIndexFromTalentPathName(const std::string name);

public:
	std::vector<PathGenerator*> pathGenerators;
	std::unordered_map<std::string, TalentTreePathGenerationData> talentPathsData;
	std::vector<std::vector<std::pair<int, std::pair<int, int>>>> pathCounts;
};

