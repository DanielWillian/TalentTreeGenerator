#include "stdafx.h"
#include "PropertyDistance.h"
#include "Statics.h"
#include "Trait.h"
#include "TraitRepository.h"
#include <algorithm>

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

	if (std::find(lesserIds.begin(), lesserIds.end(), "affect") != lesserIds.end())
	{
		return DistLhsAffect(*lesserProperty, *otherProperty) + weaponDist;
	}
	else if (std::find(lesserIds.begin(), lesserIds.end(), "stats") != lesserIds.end())
	{
		return DistLhsStats(*lesserProperty, *otherProperty) + weaponDist;
	}
	else if (std::find(lesserIds.begin(), lesserIds.end(), "resourceRelated") != lesserIds.end())
	{
		return DistLhsResourceRelated(*lesserProperty, *otherProperty) + weaponDist;
	}
	else if (std::find(lesserIds.begin(), lesserIds.end(), "alteration") != lesserIds.end())
	{
		return DistLhsAlteration(*lesserProperty, *otherProperty) + weaponDist;
	}

	return 0;
}

const Property* PropertyDistance::GetLesserProperty(const Property& lhs, const Property& rhs)
{
	std::vector<std::string>& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs.trait->index];
	std::vector<std::string>& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs.trait->index];

	if (std::find(lhsIds.begin(), lhsIds.end(), "affect") != lhsIds.end())
	{
		return &lhs;
	}
	else if (std::find(rhsIds.begin(), rhsIds.end(), "affect") != rhsIds.end())
	{
		return &rhs;
	}
	else if (std::find(lhsIds.begin(), lhsIds.end(), "stats") != lhsIds.end())
	{
		return &lhs;
	}
	else if (std::find(rhsIds.begin(), rhsIds.end(), "stats") != rhsIds.end())
	{
		return &rhs;
	}
	else if (std::find(lhsIds.begin(), lhsIds.end(), "resourceRelated") != lhsIds.end())
	{
		return &lhs;
	}
	else if (std::find(rhsIds.begin(), rhsIds.end(), "resourceRelated") != rhsIds.end())
	{
		return &rhs;
	}
	return &lhs;
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

std::string PropertyDistance::GetGeneralType(const Property& property)
{
	std::vector<std::string>& propertyIds = TraitRepository::GetInstance().allTraitsIds[property.trait->index];

	if (Statics::Contain(propertyIds, std::string("affect")))
	{
		return "affect";
	}
	else if (Statics::Contain(propertyIds, std::string("stats")))
	{
		return "stats";
	}
	else if (Statics::Contain(propertyIds, std::string("resourceRelated")))
	{
		return "resourceRelated";
	}
	else if (Statics::Contain(propertyIds, std::string("alteration")))
	{
		return "alteration";
	}
	return "";
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

	const bool bRhsContainCritical = std::find(rhsIds.begin(), rhsIds.end(), "critical") != rhsIds.end();
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

int PropertyDistance::DistLhsAffect(const Property& lhs, const Property& rhs)
{
	auto& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs.trait->index];
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs.trait->index];

	if (std::find(rhsIds.begin(), rhsIds.end(), "affect") != rhsIds.end())
	{
		return DistAffectAffect(lhs.trait->GetTraitWithId("affect"), rhs.trait->GetTraitWithId("affect"));
	}
	else if (std::find(rhsIds.begin(), rhsIds.end(), "stats") != rhsIds.end())
	{
		return DistAffectStats(lhs.trait->GetTraitWithId("affect"), rhs.trait->GetTraitWithId("stats"));
	}
	else if (std::find(rhsIds.begin(), rhsIds.end(), "resourceRelated") != rhsIds.end())
	{
		return DistAffectResourceRelated(lhs.trait->GetTraitWithId("affect"),
				rhs.trait->GetTraitWithId("resourceRelated"));
	}
	else if (std::find(rhsIds.begin(), rhsIds.end(), "alteration") != rhsIds.end())
	{
		return DistAffectAlteration(lhs.trait->GetTraitWithId("affect"), rhs.trait->GetTraitWithId("alteration"));
	}

	return 0;
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

int PropertyDistance::DistLhsStats(const Property& lhs, const Property& rhs)
{
	auto& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs.trait->index];
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs.trait->index];

	if (std::find(rhsIds.begin(), rhsIds.end(), "stats") != rhsIds.end())
	{
		return DistStatsStats(lhs.trait->GetTraitWithId("stats"), rhs.trait->GetTraitWithId("stats"));
	}
	else if (std::find(rhsIds.begin(), rhsIds.end(), "resourceRelated") != rhsIds.end())
	{
		return DistStatsResourceRelated(lhs.trait->GetTraitWithId("stats"), rhs.trait->GetTraitWithId("resourceRelated"));
	}
	else if (std::find(rhsIds.begin(), rhsIds.end(), "alteration") != rhsIds.end())
	{
		return DistStatsAlteration(lhs.trait->GetTraitWithId("stats"), rhs.trait->GetTraitWithId("alteration"));
	}

	return 0;
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

int PropertyDistance::DistLhsResourceRelated(const Property& lhs, const Property& rhs)
{
	auto& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs.trait->index];
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs.trait->index];

	if (std::find(rhsIds.begin(), rhsIds.end(), "resourceRelated") != rhsIds.end())
	{
		return DistResourceRelatedResourceRelated(lhs.trait->GetTraitWithId("resourceRelated"),
				rhs.trait->GetTraitWithId("resourceRelated"));
	}
	else if (std::find(rhsIds.begin(), rhsIds.end(), "alteration") != rhsIds.end())
	{
		return DistResourceRelatedAlteration(lhs.trait->GetTraitWithId("resourceRelated"),
				rhs.trait->GetTraitWithId("alteration"));
	}

	return 0;
}

int PropertyDistance::DistAlterationAlteration(const Trait* lhs, const Trait* rhs)
{
	return 1;
}

int PropertyDistance::DistLhsAlteration(const Property& lhs, const Property& rhs)
{
	return DistAlterationAlteration(lhs.trait->GetTraitWithId("alteration"), rhs.trait->GetTraitWithId("alteration"));
}

int PropertyDistance::DistForDamageOrHealing(const Trait* lhs, const Trait* rhs)
{
	auto& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs->index];
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs->index];

	const bool bLhsContainDamage = std::find(lhsIds.begin(), lhsIds.end(), "damage") != lhsIds.end();
	const bool bRhsContainDamage = std::find(rhsIds.begin(), rhsIds.end(), "damage") != rhsIds.end();
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
			if (std::find(lhsIds.begin(), lhsIds.end(), "allDamage") == lhsIds.end() &&
					std::find(rhsIds.begin(), rhsIds.end(), "allDamage") == rhsIds.end())
			{
				const bool bLhsDamageType1 = std::find(lhsIds.begin(), lhsIds.end(), "damageType1") != lhsIds.end();
				const bool bRhsDamageType1 = std::find(rhsIds.begin(), rhsIds.end(), "damageType1") != rhsIds.end();
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
			if (std::find(lhsIds.begin(), lhsIds.end(), "allHealing") == lhsIds.end() &&
					std::find(rhsIds.begin(), rhsIds.end(), "allHealing") == rhsIds.end())
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

	const bool bLhsContainDamageType = std::find(lhsIds.begin(), lhsIds.end(), "damageType1") != lhsIds.end();
	const bool bRhsContainDamageType = std::find(rhsIds.begin(), rhsIds.end(), "damageType1") != rhsIds.end();
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

