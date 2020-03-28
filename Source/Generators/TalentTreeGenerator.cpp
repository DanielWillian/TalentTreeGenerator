#include "TalentTreeGenerator.h"
#include <stdexcept>

TalentTreeGenerator::TalentTreeGenerator(const std::vector<BranchGenerator*>& inBranchGenerators,
		const std::unordered_map<std::string, std::vector<std::string>>& inTalentBranchesNames)
{
	pathGenerators = inBranchGenerators;

	for (const auto& pathName : inTalentBranchesNames)
	{
		const int generatorIndex = GetGeneratorIndexFromTalentBranchName(pathName.first);
		int lesserCount = 0;
		int greaterCount = 0;
		for (const auto& talentName : pathName.second)
		{
			if (IsGreaterTalent(talentName))
			{
				greaterCount++;
			}
			else
			{
				lesserCount++;
			}
		}
		talentBranchesData[pathName.first] = {generatorIndex, {lesserCount, greaterCount}, pathName.second};
	}
}

std::unique_ptr<TalentTree> TalentTreeGenerator::GenerateTalentTree()
{
	std::unordered_map<std::string, std::unique_ptr<Talent>> talentNames;
	for (const auto& pathData : talentBranchesData)
	{
		for (auto& talentName : GenerateBranch(pathData.first))
		{
			talentNames[talentName.first] = std::move(talentName.second);
		}
	}
	return std::unique_ptr<TalentTree>(new TalentTree(talentNames));
}

std::unordered_map<std::string, std::unique_ptr<Talent>> TalentTreeGenerator::GenerateBranch(const std::string& pathName)
{
	auto& data = talentBranchesData[pathName];
	std::unordered_map<std::string, std::unique_ptr<Talent>> talentNames;
	auto talentBranch = pathGenerators[data.generatorIndex]->GenerateBranch(
			data.talentCount.first, data.talentCount.second);
	for (size_t i = 0; i < data.talentNames.size(); i++)
	{
		talentNames[data.talentNames[i]] = std::move(talentBranch[i]);
	}
	return talentNames;
}

bool TalentTreeGenerator::IsGreaterTalent(const std::string name)
{
	const char index = name[0];
	return index == '3' || index == '6' || index == '8';
}

int TalentTreeGenerator::GetGeneratorIndexFromTalentBranchName(const std::string name)
{
	switch (name[0])
	{
		case '1': return 0;
		case '2': return 1;
		case '4': return 2;
		case '5': return 3;
		case '7': return 4;
		case '9': return 5;
		default: throw std::invalid_argument("invalid talent path name: " + name);
	}
}

