#include "stdafx.h"
#include "TraitRepository.h"
#include "TraitConstants.h"
#include <iostream>

TraitRepository::TraitRepository()
{
	std::vector<std::vector<TraitNode*>> aux = { {} };
	TraitNode direct = TraitNode(TraitConstants::FOURTH_LAYER_FIRST_TRAIT_DIRECT, aux);
	TraitNode durationAlt = TraitNode(TraitConstants::THIRD_LAYER_FIRST_TRAIT_DURATION, aux);
	TraitNode potencyAlt = TraitNode(TraitConstants::THIRD_LAYER_FIRST_TRAIT_POTENCY, aux);
	TraitNode urgencyAlt = TraitNode(TraitConstants::THIRD_LAYER_FIRST_TRAIT_URGENCY, aux);
	TraitNode alterationType = TraitNode(TraitConstants::SECOND_LAYER_FIRST_TRAIT_ALTERATION_TYPE,
			std::vector<std::vector<TraitNode*>>({ { &durationAlt, &potencyAlt, &urgencyAlt } }));
	TraitNode affectType1 = TraitNode(TraitConstants::THIRD_LAYER_FIRST_TRAIT_AFFECT_TYPE1,
			std::vector<std::vector<TraitNode*>>({ { &direct, &alterationType } }));
	TraitNode singleTarget = TraitNode(TraitConstants::FOURTH_LAYER_FIRST_TRAIT_SINGLE_TARGET, aux);
	TraitNode radiusAoe = TraitNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_RADIUS, aux);
	TraitNode powerAoe = TraitNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_POWER, aux);
	TraitNode areaOfEffect = TraitNode(TraitConstants::FOURTH_LAYER_FIRST_TRAIT_AREA_OF_EFFECT,
			std::vector<std::vector<TraitNode*>>({ { &radiusAoe, &powerAoe } }));
	TraitNode affectType2 = TraitNode(TraitConstants::THIRD_LAYER_FIRST_TRAIT_AFFECT_TYPE2,
			std::vector<std::vector<TraitNode*>>({ { &singleTarget, &areaOfEffect } }));
	TraitNode affectType = TraitNode(TraitConstants::SECOND_LAYER_FIRST_TRAIT_AFFECT_TYPE,
			std::vector<std::vector<TraitNode*>>({ { &affectType1, &affectType2 } }));

	TraitNode damageDamage = TraitNode(TraitConstants::THIRD_LAYER_FIRST_TRAIT_DAMAGE, aux);
	TraitNode physical = TraitNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_PHYSICAL, aux);
	TraitNode supernatural = TraitNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_SUPERNATURAL, aux);
	TraitNode damageType1 = TraitNode(TraitConstants::FOURTH_LAYER_FIRST_TRAIT_DAMAGE_TYPE1,
			std::vector<std::vector<TraitNode*>>({ { &physical, &supernatural } }));
	TraitNode fire = TraitNode(TraitConstants::SIXTH_LAYER_FIRST_TRAIT_FIRE, aux);
	TraitNode frost = TraitNode(TraitConstants::SIXTH_LAYER_FIRST_TRAIT_FROST, aux);
	TraitNode lightning = TraitNode(TraitConstants::SIXTH_LAYER_FIRST_TRAIT_LIGHTNING, aux);
	TraitNode elemental = TraitNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_ELEMENTAL,
			std::vector<std::vector<TraitNode*>>({ { &fire, &frost, &lightning } }));
	TraitNode psychic = TraitNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_PSYCHIC, aux);
	TraitNode sound = TraitNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_SOUND, aux);
	TraitNode kinetic = TraitNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_KINETIC, aux);
	TraitNode acid = TraitNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_ACID, aux);
	TraitNode bleed = TraitNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_BLEED, aux);
	TraitNode necrotic = TraitNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_NECROTIC, aux);
	TraitNode holy = TraitNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_HOLY, aux);
	TraitNode unhallow = TraitNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_UNHALLOW, aux);
	TraitNode damageType2 = TraitNode(TraitConstants::FOURTH_LAYER_FIRST_TRAIT_DAMAGE_TYPE2,
			std::vector<std::vector<TraitNode*>>({
					{ &elemental, &psychic, &sound, &kinetic, &acid, &bleed, &necrotic, &holy, &unhallow} }));
	TraitNode damageType = TraitNode(TraitConstants::THIRD_LAYER_FIRST_TRAIT_DAMAGE_TYPE,
			std::vector<std::vector<TraitNode*>>({ { &damageType1, &damageType2 } }));
	TraitNode damage = TraitNode(TraitConstants::SECOND_LAYER_SECOND_TRAIT_DAMAGE,
			std::vector<std::vector<TraitNode*>>({ { &damageDamage, &damageType } }));

	TraitNode healingHealing = TraitNode(TraitConstants::THIRD_LAYER_FIRST_TRAIT_HEALING, aux);
	TraitNode restoration = TraitNode(TraitConstants::FOURTH_LAYER_FIRST_TRAIT_RESTORATION, aux);
	TraitNode absorption = TraitNode(TraitConstants::FOURTH_LAYER_FIRST_TRAIT_ABSORPTION, aux);
	TraitNode healingType = TraitNode(TraitConstants::THIRD_LAYER_FIRST_TRAIT_HEALING_TYPE,
			std::vector<std::vector<TraitNode*>>({ { &restoration, &absorption } }));
	TraitNode healing = TraitNode(TraitConstants::SECOND_LAYER_SECOND_TRAIT_HEALING,
			std::vector<std::vector<TraitNode*>>({ { &healingHealing, &healingType } }));

	TraitNode affect = TraitNode(TraitConstants::FIRST_LAYER_FIRST_TRAIT_AFFECT,
			std::vector<std::vector<TraitNode*>>({ { &affectType }, { &damage, &healing } }));

	masterNode = TraitNode(TraitConstants::MASTER_LAYER,
			std::vector<std::vector<TraitNode*>>({ { &affect } }));

	auto aux1 = GenerateTraitFromTraitNode(&affectType);
	auto aux2 = GenerateTraitFromTraitNode(&damage);
	auto aux3 = GenerateTraitFromTraitNode(&healing);
	auto aux4 = GenerateTraitFromTraitNode(&affect);

	auto allPossibleTraits = GenerateTraitFromTraitNode(&masterNode);
	for (auto trait : allPossibleTraits)
	{
		possibleTraits.push_back(static_cast<TraitParent*>(trait));
	}
}

std::vector<Trait*> TraitRepository::GenerateTraitFromTraitNode(TraitNode* propertyNode)
{
	if (propertyNode->propertySubOptions.size() <= 1 && propertyNode->propertySubOptions[0].empty())
	{
		return { new TraitChild(propertyNode->id) };
	}
	else
	{
		std::vector<std::vector<std::vector<Trait*>>> allPossibleTraits;
		for (auto propertyNodeList : propertyNode->propertySubOptions)
		{
			std::vector<std::vector<Trait*>> childrenTraits;
			for (TraitNode* childTraitNode : propertyNodeList)
			{
				childrenTraits.push_back(GenerateTraitFromTraitNode(childTraitNode));
			}
			allPossibleTraits.push_back(childrenTraits);
		}
		auto allPossiblePermutedTraits = PermuteLists(allPossibleTraits);
		std::vector<Trait*> result;
		for (auto traitListList : allPossiblePermutedTraits)
		{
			auto permutedTraitListList = PermuteLists(traitListList);
			for (auto traitList : permutedTraitListList)
			{
				result.push_back(new TraitParent(propertyNode->id, traitList));
			}
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

template<class T>
std::vector<std::vector<T>> TraitRepository::PermuteLists(const std::vector<std::vector<T>>& listOfLists)
{
	std::vector<std::vector<T>> listPermutation = { { T() } };
	for (std::vector<T> list : listOfLists)
	{
		size_t listSize = list.size();
		for (auto it = listPermutation.begin(); it != listPermutation.end();)
		{
			std::vector<T> listToCopy = *it;
			it = listPermutation.insert(it, listSize - 1, listToCopy);
			std::advance(it, listSize);
		}
		for (auto it = listPermutation.begin(); it != listPermutation.end();)
		{
			for (T t : list)
			{
				it->push_back(t);
				it++;
			}
		}
	}
	for (std::vector<T>& list : listPermutation)
	{
		list.erase(list.begin());
	}

	return listPermutation;
}

