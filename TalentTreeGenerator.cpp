#include "stdafx.h"
#include "TalentTreeGenerator.h"

TalentTreeGenerator::TalentTreeGenerator(const std::vector<PathGenerator*>& inPathGenerators)
{
	pathGenerators = inPathGenerators;

	std::vector<std::pair<int, std::pair<int, int>>> pathCountsLevel1;
	pathCountsLevel1.push_back({8, {4, 1}});
	pathCountsLevel1.push_back({4, {4, 0}});
	pathCountsLevel1.push_back({8, {2, 1}});
	std::vector<std::pair<int, std::pair<int, int>>> pathCountsLevel2;
	pathCountsLevel2.push_back({4, {5, 0}});
	std::vector<std::pair<int, std::pair<int, int>>> pathCountsLevel4;
	pathCountsLevel4.push_back({32, {4, 1}});
	pathCountsLevel4.push_back({16, {3, 1}});
	pathCountsLevel4.push_back({16, {5, 1}});
	std::vector<std::pair<int, std::pair<int, int>>> pathCountsLevel5;
	pathCountsLevel5.push_back({8, {7, 0}});
	std::vector<std::pair<int, std::pair<int, int>>> pathCountsLevel7;
	pathCountsLevel7.push_back({16, {7, 2}});
	std::vector<std::pair<int, std::pair<int, int>>> pathCountsLevel9;
	pathCountsLevel9.push_back({8, {1, 0}});
	pathCounts = {pathCountsLevel1, pathCountsLevel2, pathCountsLevel4,
			pathCountsLevel5, pathCountsLevel7, pathCountsLevel9};
}

std::unique_ptr<TalentTree> TalentTreeGenerator::GenerateTalentTree()
{
	std::vector<std::vector<std::unique_ptr<Talent>>> talentPaths;
	for (size_t i = 0; i < pathGenerators.size(); i++)
	{
		for (auto& talentCount : pathCounts[i])
		{
			for (int j = 0; j < talentCount.first; j++)
			{
				talentPaths.push_back(std::move(pathGenerators[i]->GeneratePath(
						talentCount.second.first, talentCount.second.second)));
			}
		}
	}
	return std::move(std::unique_ptr<TalentTree>(new TalentTree(talentPaths)));
}
