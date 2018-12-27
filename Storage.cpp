#include "stdafx.h"
#include "Storage.h"
#include <fstream>

void Storage::SavePropertiesDist(const std::unordered_map<int, std::unordered_map<int, int>>& propertiesDist) const
{
	std::ofstream outFile("dists.txt");
	for (const auto& lhsDistList : propertiesDist)
	{
		outFile << lhsDistList.first << " " << static_cast<int>(lhsDistList.second.size()) << " ";
		for (const auto& rhsDist : lhsDistList.second)
		{
			outFile << rhsDist.first << " " << rhsDist.second << " ";
		}
	}
}

std::unordered_map<int, std::unordered_map<int, int>> Storage::LoadPropertiesDist() const
{
	std::unordered_map<int, std::unordered_map<int, int>> result;

	std::ifstream inFile("dists.txt");

	while (!inFile.eof())
	{
		int lhsIndex, lhsListSize;
		inFile >> lhsIndex >> lhsListSize;
		if (inFile.eof())
		{
			break;
		}
		std::unordered_map<int, int> lhsDistList;
		for (int i = 0; i < lhsListSize; i++)
		{
			int rhsIndex, dist;
			inFile >> rhsIndex >> dist;
			lhsDistList[rhsIndex] = dist;
		}
		result[lhsIndex] = std::move(lhsDistList);
	}

	return std::move(result);
}

