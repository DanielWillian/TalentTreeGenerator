#pragma once

#include "Trait.h"
#include "TraitDictionary.h"
#include <memory>

class Trait;
class TraitParent;

class TraitRepository
{
public:
	static TraitRepository& GetInstance()
	{
		static TraitRepository instance;
		return instance;
	}

	TraitRepository(TraitRepository const&) = delete;
	void operator=(TraitRepository const&) = delete;

	std::vector<TraitParent*> GetTraitsWithIds(const std::vector<std::string>& ids);

private:
	std::vector<Trait*> GenerateTraitsFromDictEntry(const TraitDictEntry& dictEntry);

	template<class T>
	std::vector<std::vector<T*>> PermuteLists(const std::vector<std::vector<T*>>& listOfLists);

	inline Trait* GetTrait(std::unique_ptr<Trait>& trait);

	inline int GetNextIndex() const;

private:
	TraitRepository();

public:
	std::vector<TraitParent*> possibleTraits;

	std::vector<Trait*> allTraits;

	std::vector<std::vector<std::string>> allTraitsIds;

	TraitDictionary traitDictionary;

private:
	std::vector<std::unique_ptr<Trait>> allTraitsSaved;
};

