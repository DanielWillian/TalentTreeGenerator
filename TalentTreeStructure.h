#pragma once

#include <vector>
#include <unordered_map>

class TalentTreeStructure
{
public:
	TalentTreeStructure();

public:
	std::unordered_map<std::string, std::vector<std::string>> talentPaths;
	std::unordered_map<std::string, std::unordered_map<std::string, bool>> talentConnections;
};

