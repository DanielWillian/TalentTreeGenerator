#include "TalentTree.h"

TalentTree::TalentTree(std::unordered_map<std::string, std::unique_ptr<Talent>>& inOutTalents)
{
	talents = std::move(inOutTalents);
}

