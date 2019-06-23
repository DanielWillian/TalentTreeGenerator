#pragma once

#include "Talent.h"
#include <unordered_map>
#include <memory>

class TalentTree
{
public:
	TalentTree(std::unordered_map<std::string, std::unique_ptr<Talent>>& inOutTalents);

public:
	std::unordered_map<std::string, std::unique_ptr<Talent>> talents;
};

