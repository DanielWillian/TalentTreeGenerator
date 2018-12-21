#pragma once

#include "Trait.h"
#include "TraitDictionary.h"
#include <memory>

class TraitRepository
{
public:
	TraitRepository();

	std::vector<TraitParent*> GetTraitsWithIds(const std::vector<std::string>& ids);

private:
	std::vector<Trait*> GenerateTraitsFromDictEntry(const TraitDictEntry& dictEntry);

	template<class T>
	std::vector<std::vector<T*>> PermuteLists(const std::vector<std::vector<T*>>& listOfLists);

	inline Trait* GetTrait(std::unique_ptr<Trait>& trait);

public:
	std::vector<TraitParent*> possibleTraits;

	TraitDictionary traitDictionary;

private:
	std::vector<std::unique_ptr<Trait>> allTraits;
};

