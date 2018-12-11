#pragma once

#include "Trait.h"
#include "TraitDictionary.h"

class TraitRepository
{
public:
	TraitRepository();

private:
	std::vector<Trait*> GenerateTraitsFromDictEntry(const TraitDictEntry& dictEntry);

	template<class T>
	std::vector<std::vector<T*>> PermuteLists(const std::vector<std::vector<T*>>& listOfLists);

public:
	std::vector<TraitParent*> possibleTraits;

	TraitDictionary traitDictionary;
};

