#include "stdafx.h"
#include "TraitRepository.h"
#include <iostream>

TraitRepository::TraitRepository()
{
	auto allPossibleTraits = GenerateTraitsFromDictEntry(traitDictionary.GetDictEntry("property"));
	for (auto trait : allPossibleTraits)
	{
		possibleTraits.push_back(static_cast<TraitParent*>(trait));
	}
}


std::vector<TraitParent*> TraitRepository::GetTraitsWithIds(const std::vector<std::string>& ids)
{
	std::vector<TraitParent*> result;

	for (auto* trait : possibleTraits)
	{
		bool bFound = false;
		for (auto& id : ids)
		{
			bFound = false;
			for (auto& traitId : trait->GetAllTraitIds())
			{
				if (id == traitId)
				{
					bFound = true;
					break;
				}
			}
			if (!bFound)
			{
				break;
			}
		}
		if (bFound)
		{
			result.push_back(trait);
		}
	}

	return result;
}

std::vector<Trait*> TraitRepository::GenerateTraitsFromDictEntry(const TraitDictEntry& dictEntry)
{
	if (dictEntry.type == TraitDictionary::TERMINAL)
	{
		return { new TraitChild(dictEntry.key) };
	}
	else if (dictEntry.type == TraitDictionary::ALTERNATIVES)
	{
		std::vector<Trait*> result;
		for (auto value : dictEntry.values)
		{
			for (auto* trait : GenerateTraitsFromDictEntry(traitDictionary.GetDictEntry(value)))
			{
				result.push_back({ new TraitParent(dictEntry.key, { trait }) });
			}
		}
		return result;
	}
	else
	{
		std::vector<std::vector<Trait*>> childrenTraits;
		for (auto& value : dictEntry.values)
		{
			childrenTraits.push_back(GenerateTraitsFromDictEntry(traitDictionary.GetDictEntry(value)));
		}
		std::vector<std::vector<Trait*>> permutedTraits = PermuteLists(childrenTraits);
		std::vector<Trait*> result;
		for (auto& traitList : permutedTraits)
		{
			result.push_back({ new TraitParent(dictEntry.key, traitList) });
		}
		return result;
	}
}

template<class T>
std::vector<std::vector<T*>> TraitRepository::PermuteLists(const std::vector<std::vector<T*>>& listOfLists)
{
	std::vector<std::vector<T*>> listPermutation = { { nullptr } };
	for (std::vector<T*> list : listOfLists)
	{
		size_t listSize = list.size();
		for (auto it = listPermutation.begin(); it != listPermutation.end();)
		{
			std::vector<T*> listToCopy = *it;
			it = listPermutation.insert(it, listSize - 1, listToCopy);
			std::advance(it, listSize);
		}
		for (auto it = listPermutation.begin(); it != listPermutation.end();)
		{
			for (T* t : list)
			{
				it->push_back(t);
				it++;
			}
		}
	}
	for (std::vector<T*>& list : listPermutation)
	{
		list.erase(list.begin());
	}

	return listPermutation;
}

