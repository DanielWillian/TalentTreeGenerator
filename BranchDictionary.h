#pragma once

#include <vector>
#include <unordered_map>

class BranchDictionary
{
public:
	BranchDictionary();

public:
	std::unordered_map<std::string, std::vector<std::string>> talentBranches;
};

