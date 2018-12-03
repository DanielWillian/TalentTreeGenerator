#include "stdafx.h"
#include "PropertyRepository.h"
#include "TraitConstants.h"
#include <iostream>

PropertyRepository::PropertyRepository()
{
	std::vector<std::vector<PropertyNode*>> aux = { {} };
	PropertyNode direct = PropertyNode(TraitConstants::FOURTH_LAYER_FIRST_TRAIT_DIRECT, aux);
	PropertyNode durationAlt = PropertyNode(TraitConstants::THIRD_LAYER_FIRST_TRAIT_DURATION, aux);
	PropertyNode potencyAlt = PropertyNode(TraitConstants::THIRD_LAYER_FIRST_TRAIT_POTENCY, aux);
	PropertyNode urgencyAlt = PropertyNode(TraitConstants::THIRD_LAYER_FIRST_TRAIT_URGENCY, aux);
	PropertyNode alterationType = PropertyNode(TraitConstants::SECOND_LAYER_FIRST_TRAIT_ALTERATION_TYPE,
			std::vector<std::vector<PropertyNode*>>({ { &durationAlt, &potencyAlt, &urgencyAlt } }));
	PropertyNode affectType1 = PropertyNode(TraitConstants::THIRD_LAYER_FIRST_TRAIT_AFFECT_TYPE1,
			std::vector<std::vector<PropertyNode*>>({ { &direct, &alterationType } }));
	PropertyNode singleTarget = PropertyNode(TraitConstants::FOURTH_LAYER_FIRST_TRAIT_SINGLE_TARGET, aux);
	PropertyNode radiusAoe = PropertyNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_RADIUS, aux);
	PropertyNode powerAoe = PropertyNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_POWER, aux);
	PropertyNode areaOfEffect = PropertyNode(TraitConstants::FOURTH_LAYER_FIRST_TRAIT_AREA_OF_EFFECT,
			std::vector<std::vector<PropertyNode*>>({ { &radiusAoe, &powerAoe } }));
	PropertyNode affectType2 = PropertyNode(TraitConstants::THIRD_LAYER_FIRST_TRAIT_AFFECT_TYPE2,
			std::vector<std::vector<PropertyNode*>>({ { &singleTarget, &areaOfEffect } }));
	PropertyNode affectType = PropertyNode(TraitConstants::SECOND_LAYER_FIRST_TRAIT_AFFECT_TYPE,
			std::vector<std::vector<PropertyNode*>>({ { &affectType1, &affectType2 } }));

	PropertyNode damageDamage = PropertyNode(TraitConstants::THIRD_LAYER_FIRST_TRAIT_DAMAGE, aux);
	PropertyNode physical = PropertyNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_PHYSICAL, aux);
	PropertyNode supernatural = PropertyNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_SUPERNATURAL, aux);
	PropertyNode damageType1 = PropertyNode(TraitConstants::FOURTH_LAYER_FIRST_TRAIT_DAMAGE_TYPE1,
			std::vector<std::vector<PropertyNode*>>({ { &physical, &supernatural } }));
	PropertyNode fire = PropertyNode(TraitConstants::SIXTH_LAYER_FIRST_TRAIT_FIRE, aux);
	PropertyNode frost = PropertyNode(TraitConstants::SIXTH_LAYER_FIRST_TRAIT_FROST, aux);
	PropertyNode lightning = PropertyNode(TraitConstants::SIXTH_LAYER_FIRST_TRAIT_LIGHTNING, aux);
	PropertyNode elemental = PropertyNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_ELEMENTAL,
			std::vector<std::vector<PropertyNode*>>({ { &fire, &frost, &lightning } }));
	PropertyNode psychic = PropertyNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_PSYCHIC, aux);
	PropertyNode sound = PropertyNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_SOUND, aux);
	PropertyNode kinetic = PropertyNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_KINETIC, aux);
	PropertyNode acid = PropertyNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_ACID, aux);
	PropertyNode bleed = PropertyNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_BLEED, aux);
	PropertyNode necrotic = PropertyNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_NECROTIC, aux);
	PropertyNode holy = PropertyNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_HOLY, aux);
	PropertyNode unhallow = PropertyNode(TraitConstants::FIFTH_LAYER_FIRST_TRAIT_UNHALLOW, aux);
	PropertyNode damageType2 = PropertyNode(TraitConstants::FOURTH_LAYER_FIRST_TRAIT_DAMAGE_TYPE2,
			std::vector<std::vector<PropertyNode*>>({
					{ &elemental, &psychic, &sound, &kinetic, &acid, &bleed, &necrotic, &holy, &unhallow} }));
	PropertyNode damageType = PropertyNode(TraitConstants::THIRD_LAYER_FIRST_TRAIT_DAMAGE_TYPE,
			std::vector<std::vector<PropertyNode*>>({ { &damageType1, &damageType2 } }));
	PropertyNode damage = PropertyNode(TraitConstants::SECOND_LAYER_SECOND_TRAIT_DAMAGE,
			std::vector<std::vector<PropertyNode*>>({ { &damageDamage, &damageType } }));

	PropertyNode healingHealing = PropertyNode(TraitConstants::THIRD_LAYER_FIRST_TRAIT_HEALING, aux);
	PropertyNode restoration = PropertyNode(TraitConstants::FOURTH_LAYER_FIRST_TRAIT_RESTORATION, aux);
	PropertyNode absorption = PropertyNode(TraitConstants::FOURTH_LAYER_FIRST_TRAIT_ABSORPTION, aux);
	PropertyNode healingType = PropertyNode(TraitConstants::THIRD_LAYER_FIRST_TRAIT_HEALING_TYPE,
			std::vector<std::vector<PropertyNode*>>({ { &restoration, &absorption } }));
	PropertyNode healing = PropertyNode(TraitConstants::SECOND_LAYER_SECOND_TRAIT_HEALING,
			std::vector<std::vector<PropertyNode*>>({ { &healingHealing, &healingType } }));

	PropertyNode affect = PropertyNode(TraitConstants::FIRST_LAYER_FIRST_TRAIT_AFFECT,
			std::vector<std::vector<PropertyNode*>>({ { &affectType }, { &damage, &healing } }));

	masterNode = PropertyNode(TraitConstants::MASTER_LAYER,
			std::vector<std::vector<PropertyNode*>>({ { &affect } }));

	auto aux1 = GenerateTraitFromPropertyNode(&affectType);
	auto aux2 = GenerateTraitFromPropertyNode(&damage);
	auto aux3 = GenerateTraitFromPropertyNode(&healing);
	auto aux4 = GenerateTraitFromPropertyNode(&affect);

	auto allPossibleTraits = GenerateTraitFromPropertyNode(&masterNode);
	for (auto trait : allPossibleTraits)
	{
		possibleTraits.push_back(static_cast<TraitParent*>(trait));
	}
}

std::vector<Trait*> PropertyRepository::GenerateTraitFromPropertyNode(PropertyNode* propertyNode)
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
			for (PropertyNode* childPropertyNode : propertyNodeList)
			{
				childrenTraits.push_back(GenerateTraitFromPropertyNode(childPropertyNode));
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
std::vector<std::vector<T*>> PropertyRepository::PermuteLists(const std::vector<std::vector<T*>>& listOfLists)
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
std::vector<std::vector<T>> PropertyRepository::PermuteLists(const std::vector<std::vector<T>>& listOfLists)
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

