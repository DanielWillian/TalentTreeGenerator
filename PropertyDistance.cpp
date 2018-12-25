#include "stdafx.h"
#include "PropertyDistance.h"
#include "Statics.h"
#include "Trait.h"
#include "TraitRepository.h"
#include <algorithm>

PropertyDistance::PropertyDistance()
{
	auto& allTraits = TraitRepository::GetInstance().allTraits;
	std::vector<Trait*> weaponTraits;
	for (auto* trait : allTraits)
	{
		if (trait->id == "weapon")
		{
			weaponTraits.push_back(trait);
		}
	}

	for (auto* lhs : weaponTraits)
	{
		std::unordered_map<int, int> lhsDists(weaponTraits.size());
		for (auto* rhs : weaponTraits)
		{
			lhsDists[rhs->index] = DistWeapon(lhs, rhs);
		}
		weaponDistances[lhs->index] = lhsDists;
	}

	std::vector<Trait*> affectTraits;
	for (auto* trait : allTraits)
	{
		if (trait->id == "affect")
		{
			affectTraits.push_back(trait);
		}
	}

	std::vector<Trait*> statsTraits;
	for (auto* trait : allTraits)
	{
		if (trait->id == "stats")
		{
			statsTraits.push_back(trait);
		}
	}

	std::vector<Trait*> resourceRelatedTraits;
	for (auto* trait : allTraits)
	{
		if (trait->id == "resourceRelated")
		{
			resourceRelatedTraits.push_back(trait);
		}
	}

	std::vector<Trait*> alterationTraits;
	for (auto* trait : allTraits)
	{
		if (trait->id == "alteration")
		{
			alterationTraits.push_back(trait);
		}
	}

	for (auto* lhs : affectTraits)
	{
		std::unordered_map<int, int> lhsDists;
		for (auto* rhs : affectTraits)
		{
			lhsDists[rhs->index] = DistAffectAffect(lhs, rhs);
		}
		for (auto* rhs : statsTraits)
		{
			lhsDists[rhs->index] = DistAffectStats(lhs, rhs);
		}
		for (auto* rhs : resourceRelatedTraits)
		{
			lhsDists[rhs->index] = DistAffectResourceRelated(lhs, rhs);
		}
		for (auto* rhs : alterationTraits)
		{
			lhsDists[rhs->index] = DistAffectAlteration(lhs, rhs);
		}
		affectDistances[lhs->index] = lhsDists;
	}

	for (auto* lhs : statsTraits)
	{
		std::unordered_map<int, int> lhsDists;
		for (auto* rhs : statsTraits)
		{
			lhsDists[rhs->index] = DistStatsStats(lhs, rhs);
		}
		for (auto* rhs : resourceRelatedTraits)
		{
			lhsDists[rhs->index] = DistStatsResourceRelated(lhs, rhs);
		}
		for (auto* rhs : alterationTraits)
		{
			lhsDists[rhs->index] = DistStatsAlteration(lhs, rhs);
		}
		statsDistances[lhs->index] = lhsDists;
	}

	for (auto* lhs : resourceRelatedTraits)
	{
		std::unordered_map<int, int> lhsDists;
		for (auto* rhs : resourceRelatedTraits)
		{
			lhsDists[rhs->index] = DistResourceRelatedResourceRelated(lhs, rhs);
		}
		for (auto* rhs : alterationTraits)
		{
			lhsDists[rhs->index] = DistResourceRelatedAlteration(lhs, rhs);
		}
		resourceRelatedDistances[lhs->index] = lhsDists;
	}

	for (auto* lhs : alterationTraits)
	{
		std::unordered_map<int, int> lhsDists;
		for (auto* rhs : alterationTraits)
		{
			lhsDists[rhs->index] = DistAlterationAlteration(lhs, rhs);
		}
		alterationDistances[lhs->index] = lhsDists;
	}
}

int PropertyDistance::DistanceBetweenProperties(const Property& lhs, const Property& rhs)
{
	const Property* lesserProperty = GetLesserProperty(lhs, rhs);
	const Property* otherProperty = *lesserProperty == lhs ? &rhs : &lhs;
	std::vector<std::string>& lesserIds = TraitRepository::GetInstance().allTraitsIds[lesserProperty->trait->index];
	std::vector<std::string>& otherIds = TraitRepository::GetInstance().allTraitsIds[otherProperty->trait->index];

	const bool bLesserAttri = Statics::Contain(lesserIds, std::string("attributes"));
	const bool bOtherAttri = Statics::Contain(otherIds, std::string("attributes"));
	if (bLesserAttri || bOtherAttri)
	{
		return !bLesserAttri || !bOtherAttri ? 20 : 0;
	}

	const int weaponDist = DistWeapon(lhs.trait->GetTraitWithId("weapon"), rhs.trait->GetTraitWithId("weapon"));

	if (Statics::Contain(lesserIds, std::string("affect")))
	{
		return DistLhsAffect(lesserProperty->trait->GetTraitWithId("affect"), *otherProperty) + weaponDist;
	}
	else if (Statics::Contain(lesserIds, std::string("stats")))
	{
		return DistLhsStats(lesserProperty->trait->GetTraitWithId("stats"), *otherProperty) + weaponDist;
	}
	else if (Statics::Contain(lesserIds, std::string("resourceRelated")))
	{
		return DistLhsResourceRelated(lesserProperty->trait->GetTraitWithId("resourceRelated"),
				*otherProperty) + weaponDist;
	}
	else if (Statics::Contain(lesserIds, std::string("alteration")))
	{
		return DistLhsAlteration(lesserProperty->trait->GetTraitWithId("alteration"), *otherProperty) + weaponDist;
	}

	return 0;
}

const Property* PropertyDistance::GetLesserProperty(const Property& lhs, const Property& rhs)
{
	std::vector<std::string>& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs.trait->index];
	std::vector<std::string>& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs.trait->index];

	if (Statics::Contain(lhsIds, std::string("affect")))
	{
		return &lhs;
	}
	else if (Statics::Contain(rhsIds, std::string("affect")))
	{
		return &rhs;
	}
	else if (Statics::Contain(lhsIds, std::string("stats")))
	{
		return &lhs;
	}
	else if (Statics::Contain(rhsIds, std::string("stats")))
	{
		return &rhs;
	}
	else if (Statics::Contain(lhsIds, std::string("resourceRelated")))
	{
		return &lhs;
	}
	else if (Statics::Contain(rhsIds, std::string("resourceRelated")))
	{
		return &rhs;
	}
	return &lhs;
}

int PropertyDistance::DistLhsAffect(const Trait* lhs, const Property& rhs)
{
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs.trait->index];
	const Trait* rhsTrait = nullptr;

	if (Statics::Contain(rhsIds, std::string("affect")))
	{
		rhsTrait = rhs.trait->GetTraitWithId("affect");
	}
	else if (Statics::Contain(rhsIds, std::string("stats")))
	{
		rhsTrait = rhs.trait->GetTraitWithId("stats");
	}
	else if (Statics::Contain(rhsIds, std::string("resourceRelated")))
	{
		rhsTrait = rhs.trait->GetTraitWithId("resourceRelated");
	}
	else if (Statics::Contain(rhsIds, std::string("alteration")))
	{
		rhsTrait = rhs.trait->GetTraitWithId("alteration");
	}

	return affectDistances[lhs->index][rhsTrait->index];
}

int PropertyDistance::DistLhsStats(const Trait* lhs, const Property& rhs)
{
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs.trait->index];
	const Trait* rhsTrait = nullptr;

	if (Statics::Contain(rhsIds, std::string("stats")))
	{
		rhsTrait = rhs.trait->GetTraitWithId("stats");
	}
	else if (Statics::Contain(rhsIds, std::string("resourceRelated")))
	{
		rhsTrait = rhs.trait->GetTraitWithId("resourceRelated");
	}
	else if (Statics::Contain(rhsIds, std::string("alteration")))
	{
		rhsTrait = rhs.trait->GetTraitWithId("alteration");
	}

	return statsDistances[lhs->index][rhsTrait->index];
}

int PropertyDistance::DistLhsResourceRelated(const Trait* lhs, const Property& rhs)
{
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs.trait->index];
	const Trait* rhsTrait = nullptr;

	if (Statics::Contain(rhsIds, std::string("resourceRelated")))
	{
		rhsTrait = rhs.trait->GetTraitWithId("resourceRelated");
	}
	else if (Statics::Contain(rhsIds, std::string("alteration")))
	{
		rhsTrait = rhs.trait->GetTraitWithId("alteration");
	}

	return resourceRelatedDistances[lhs->index][rhsTrait->index];
}

int PropertyDistance::DistLhsAlteration(const Trait* lhs, const Property& rhs)
{
	const Trait* rhsTrait = rhs.trait->GetTraitWithId("alteration");

	return affectDistances[lhs->index][rhsTrait->index];
}

int PropertyDistance::DistWeapon(const Trait* lhs, const Trait* rhs)
{
	auto& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs->index];
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs->index];

	if (Statics::Contain(lhsIds, std::string("allWeapon")) ||
			Statics::Contain(rhsIds, std::string("allWeapon")))
	{
		return 0;
	}
	else
	{
		const bool bLhsType1 = Statics::Contain(lhsIds, std::string("weaponType1"));
		const bool bRhsType1 = Statics::Contain(rhsIds, std::string("weaponType1"));
		if (bLhsType1 == bRhsType1)
		{
			const auto matchPair = std::mismatch(lhsIds.begin(), lhsIds.end(), rhsIds.begin(), rhsIds.end());
			if (matchPair.first != lhsIds.end() || matchPair.second != rhsIds.end())
			{
				return 20;
			}
		}
		else
		{
			const auto type1Ids = bLhsType1 ? lhsIds : rhsIds;
			const auto type2Ids = bLhsType1 ? rhsIds : lhsIds;
			if (Statics::Contain(type1Ids, std::string("oneHanded")))
			{
				if (!Statics::ContainAny(type2Ids, {"axe", "sword", "mace", "dagger", "scythe", "fist", "wand",
							"card", "crossbow", "thrown", "shield", "relic"}))
				{
					return 20;
				}
			}
			else
			{
				if (!Statics::ContainAny(type2Ids, {"axe", "sword", "mace", "polearm", "scythe", "bow"}))
				{
					return 20;
				}
			}
		}
	}

	return 0;
}

int PropertyDistance::DistAffectAffect(const Trait* lhs, const Trait* rhs)
{
	auto& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs->index];
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs->index];

	int result = DistForDamageOrHealing(lhs, rhs);
	if (result > 5)
	{
		return result;
	}

	const bool bLhsAffectType1 = Statics::Contain(lhsIds, std::string("affectType1"));
	const bool bRhsAffectType1 = Statics::Contain(rhsIds, std::string("affectType1"));
	if (bLhsAffectType1 == bRhsAffectType1)
	{
		if (bLhsAffectType1)
		{
			const bool bLhsDirect = Statics::Contain(lhsIds, std::string("direct"));
			const bool bRhsDirect = Statics::Contain(rhsIds, std::string("direct"));
			if (bLhsDirect != bRhsDirect)
			{
				return 20;
			}
		}
		else
		{
			const bool bLhsSingle = Statics::Contain(lhsIds, std::string("singleTarget"));
			const bool bRhsSingle = Statics::Contain(rhsIds, std::string("singleTarget"));
			if (bLhsSingle != bRhsSingle)
			{
				return 20;
			}
		}
	}

	return result;
}

int PropertyDistance::DistAffectStats(const Trait* lhs, const Trait* rhs)
{
	auto& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs->index];
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs->index];

	const bool bRhsContainCritical = Statics::Contain(rhsIds, std::string("critical"));
	if (bRhsContainCritical)
	{
		const bool bRhsContainAllCritical = Statics::Contain(rhsIds, std::string("allCriticalChance")) ||
				Statics::Contain(rhsIds, std::string("allCriticalEffect"));
		if (!bRhsContainAllCritical)
		{
			return DistForDamageOrHealing(lhs, rhs);
		}
	}

	const bool bRhsContainDefensive = Statics::Contain(rhsIds, std::string("defensive"));
	if (bRhsContainDefensive)
	{
		return 20;
	}

	const bool bRhsContainHitChance = Statics::Contain(rhsIds, std::string("hitChance"));
	if (bRhsContainHitChance)
	{
		const bool bLhsContainDamageType = Statics::Contain(lhsIds, std::string("damageType1"));
		const bool bRhsContainDamageType = Statics::Contain(rhsIds, std::string("damageType1"));
		if (bLhsContainDamageType && bRhsContainDamageType)
		{
			auto& lhsDamageIds = TraitRepository::GetInstance().allTraitsIds[lhs->GetTraitWithId("damageType1")->index];
			auto& rhsDamageIds = TraitRepository::GetInstance().allTraitsIds[rhs->GetTraitWithId("damageType1")->index];
			if (lhsDamageIds != rhsDamageIds)
			{
				return 20;
			}
		}

		const bool bLhsContainHealing = Statics::Contain(lhsIds, std::string("healing"));
		if (bLhsContainHealing)
		{
			return 20;
		}
	}

	return 1;
}

int PropertyDistance::DistAffectResourceRelated(const Trait* lhs, const Trait* rhs)
{
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs->index];

	const bool bRhsContainVampirism = Statics::Contain(rhsIds, std::string("vampirism"));
	if (bRhsContainVampirism)
	{
		return 5;
	}

	return 20;
}

int PropertyDistance::DistAffectAlteration(const Trait* lhs, const Trait* rhs)
{
	return 1;
}

int PropertyDistance::DistStatsStats(const Trait* lhs, const Trait* rhs)
{
	auto& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs->index];
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs->index];

	const bool bLhsContainOffensive = Statics::Contain(lhsIds, std::string("offensive"));
	const bool bRhsContainOffensive = Statics::Contain(rhsIds, std::string("offensive"));
	const bool bLhsContainDefensive = Statics::Contain(lhsIds, std::string("defensive"));
	const bool bRhsContainDefensive = Statics::Contain(rhsIds, std::string("defensive"));

	if ((bLhsContainOffensive && bRhsContainDefensive) || (bLhsContainDefensive && bRhsContainOffensive))
	{
		return 20;
	}

	if (bLhsContainOffensive && bRhsContainOffensive)
	{
		int result = DistForDamageType1(lhs, rhs);
		if (result > 5)
		{
			return result;
		}
		const bool bLhsSpecCritical = Statics::Contain(lhsIds, std::string("specCriticalChance")) ||
				Statics::Contain(lhsIds, std::string("specCriticalEffect"));
		const bool bRhsSpecCritical = Statics::Contain(rhsIds, std::string("specCriticalChance")) ||
				Statics::Contain(rhsIds, std::string("specCriticalEffect"));
		if (bLhsSpecCritical && bRhsSpecCritical)
		{
			result = DistForDamageOrHealing(lhs, rhs);
			if (result > 5)
			{
				return result;
			}
		}
	}

	if (bLhsContainDefensive && bRhsContainDefensive)
	{
		int result = DistForDamageType1(lhs, rhs);
		if (result > 5)
		{
			return result;
		}

		for (auto& id : {"evasion", "dodge", "block", "armour"})
		{
			const bool bLhsContainId = Statics::Contain(lhsIds, std::string(id));
			const bool bRhsContainId = Statics::Contain(rhsIds, std::string(id));
			if (bLhsContainId && bRhsContainId)
			{
				return 1;
			}
		}

		return 20;
	}

	return 1;
}

int PropertyDistance::DistStatsResourceRelated(const Trait* lhs, const Trait* rhs)
{
	auto& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs->index];
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs->index];

	const bool bLhsContainOffensive = Statics::Contain(lhsIds, std::string("offensive"));
	const bool bLhsContainDefensive = Statics::Contain(lhsIds, std::string("defensive"));
	const bool bRhsContainVampirism = Statics::Contain(rhsIds, std::string("vampirism"));

	if (bLhsContainOffensive && bRhsContainVampirism)
	{
		return 5;
	}
	if (bLhsContainDefensive && !bRhsContainVampirism)
	{
		return 5;
	}

	return 20;
}

int PropertyDistance::DistStatsAlteration(const Trait* lhs, const Trait* rhs)
{
	auto& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs->index];
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs->index];

	const bool bLhsContainOffensive = Statics::Contain(lhsIds, std::string("offensive"));

	if (bLhsContainOffensive)
	{
		return 1;
	}

	return 20;
}

int PropertyDistance::DistResourceRelatedResourceRelated(const Trait* lhs, const Trait* rhs)
{
	auto& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs->index];
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs->index];

	std::vector<std::vector<std::string>> idListOfPossibleEquals = { {"mana", "manaRegen", "manaVemp"},
		{"health", "healthRegen", "healthVamp"}, {"shield", "shieldRegen", "shieldVamp"} };
	for (auto& idList : idListOfPossibleEquals)
	{
		for (auto& lhsId : idList)
		{
			const bool bLhsContainId = Statics::Contain(lhsIds, lhsId);
			for (auto& rhsId : idList)
			{
				const bool bRhsContainId = Statics::Contain(rhsIds, rhsId);
				if (bLhsContainId && bRhsContainId)
				{
					return 1;
				}
			}
		}
	}

	return 20;
}

int PropertyDistance::DistResourceRelatedAlteration(const Trait* lhs, const Trait* rhs)
{
	return 1;
}

int PropertyDistance::DistAlterationAlteration(const Trait* lhs, const Trait* rhs)
{
	return 1;
}

int PropertyDistance::DistForDamageOrHealing(const Trait* lhs, const Trait* rhs)
{
	auto& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs->index];
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs->index];

	const bool bLhsContainDamage = Statics::Contain(lhsIds, std::string("damage"));
	const bool bRhsContainDamage = Statics::Contain(rhsIds, std::string("damage"));
	// Damage to Healing
	if (bLhsContainDamage != bRhsContainDamage)
	{
		return 20;
	}
	else
	{
		if (bLhsContainDamage)
		{
			auto& lhsDamageIds = TraitRepository::GetInstance().allTraitsIds[lhs->GetTraitWithId("damage")->index];
			auto& rhsDamageIds = TraitRepository::GetInstance().allTraitsIds[rhs->GetTraitWithId("damage")->index];
			// Neither contain all damage
			if (!Statics::Contain(lhsIds, std::string("allDamage")) &&
					!Statics::Contain(rhsIds, std::string("allDamage")))
			{
				const bool bLhsDamageType1 = Statics::Contain(lhsIds, std::string("damageType1"));
				const bool bRhsDamageType1 = Statics::Contain(rhsIds, std::string("damageType1"));
				if (bLhsDamageType1 == bRhsDamageType1 && lhsDamageIds != rhsDamageIds)
				{
					return 20;
				}
			}
		}
		else
		{
			auto& lhsHealingIds = TraitRepository::GetInstance().allTraitsIds[lhs->GetTraitWithId("healing")->index];
			auto& rhsHealingIds = TraitRepository::GetInstance().allTraitsIds[rhs->GetTraitWithId("healing")->index];
			// Neither contain all healing
			if (!Statics::Contain(lhsIds, std::string("allHealing")) &&
					!Statics::Contain(rhsIds, std::string("allHealing")))
			{
				if (lhsHealingIds != rhsHealingIds)
				{
					return 20;
				}
			}
		}
	}

	return 1;
}

int PropertyDistance::DistForDamageType1(const Trait* lhs, const Trait* rhs)
{
	auto& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs->index];
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs->index];

	const bool bLhsContainDamageType = Statics::Contain(lhsIds, std::string("damageType1"));
	const bool bRhsContainDamageType = Statics::Contain(rhsIds, std::string("damageType1"));
	if (bLhsContainDamageType && bRhsContainDamageType)
	{
		auto& lhsDamageIds = TraitRepository::GetInstance().allTraitsIds[lhs->GetTraitWithId("damageType1")->index];
		auto& rhsDamageIds = TraitRepository::GetInstance().allTraitsIds[rhs->GetTraitWithId("damageType1")->index];
		if (lhsDamageIds != rhsDamageIds)
		{
			return 20;
		}
	}

	return 1;
}

