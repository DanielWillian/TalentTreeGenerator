#pragma once

#include "Trait.h"
#include "TraitConstants.h"

class TraitNode
{
public:
	TraitNode(const int inId, const std::vector<std::vector<TraitNode*>>& inTraitSubOptions)
	{
		id = inId;
		propertySubOptions = inTraitSubOptions;
	}
	TraitNode() {}

	int id;
	std::vector<std::vector<TraitNode*>> propertySubOptions;
};

class TraitRepository
{
public:
	TraitRepository();

private:
	std::vector<Trait*> GenerateTraitFromTraitNode(TraitNode* propertyNode);

	template<class T>
	std::vector<std::vector<T*>> PermuteLists(const std::vector<std::vector<T*>>& listOfLists);

	template<class T>
	std::vector<std::vector<T>> PermuteLists(const std::vector<std::vector<T>>& listOfLists);

	TraitNode masterNode;

public:
	std::vector<TraitParent*> possibleTraits;
};

