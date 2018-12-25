#include "stdafx.h"
#include "Property.h"
#include "Statics.h"
#include "TraitRepository.h"
#include <algorithm>

int Property::DistanceBetweenProperties(const Property& lhs, const Property& rhs)
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

	const int weaponDist = DistWeapon(lhs, rhs);

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

const Property* Property::GetLesserProperty(const Property& lhs, const Property& rhs)
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

int Property::DistWeapon(const Property& lhs, const Property& rhs)
{
	auto& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs.trait->GetTraitWithId("weapon")->index];
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs.trait->GetTraitWithId("weapon")->index];

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

int Property::DistLhsAffect(const Property& lhs, const Property& rhs)
{
	auto& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs.trait->index];
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs.trait->index];

	if (std::find(rhsIds.begin(), rhsIds.end(), "affect") != rhsIds.end())
	{
		int result = DistForDamageOrHealing(lhs, rhs);
		if (result > 5)
		{
			return result;
		}

		const bool bLhsAffectType1 = std::find(lhsIds.begin(), lhsIds.end(), "affectType1") != lhsIds.end();
		const bool bRhsAffectType1 = std::find(rhsIds.begin(), rhsIds.end(), "affectType1") != rhsIds.end();
		if (bLhsAffectType1 == bRhsAffectType1)
		{
			auto& lhsAffectTypeIds = TraitRepository::GetInstance().allTraitsIds[lhs.trait->GetTraitWithId("affectType")->index];
			auto& rhsAffectTypeIds = TraitRepository::GetInstance().allTraitsIds[rhs.trait->GetTraitWithId("affectType")->index];
			if (lhsAffectTypeIds != rhsAffectTypeIds)
			{
				return 20;
			}
		}

		return result;
	}
	else if (std::find(rhsIds.begin(), rhsIds.end(), "stats") != rhsIds.end())
	{
		const bool bRhsContainCritical = std::find(rhsIds.begin(), rhsIds.end(), "critical") != rhsIds.end();
		if (bRhsContainCritical)
		{
			const bool bRhsContainAllCritical =
					std::find(rhsIds.begin(), rhsIds.end(), "allCriticalChance") != rhsIds.end() ||
					std::find(rhsIds.begin(), rhsIds.end(), "allCriticalEffect") != rhsIds.end();
			if (!bRhsContainAllCritical)
			{
				return DistForDamageOrHealing(lhs, rhs);
			}
		}

		const bool bRhsContainDefensive = std::find(rhsIds.begin(), rhsIds.end(), "defensive") != rhsIds.end();
		if (bRhsContainDefensive)
		{
			return 20;
		}

		const bool bRhsContainHitChance = std::find(rhsIds.begin(), rhsIds.end(), "hitChance") != rhsIds.end();
		if (bRhsContainHitChance)
		{
			const bool bLhsContainDamageType = std::find(lhsIds.begin(), lhsIds.end(), "damageType1") != lhsIds.end();
			const bool bRhsContainDamageType = std::find(rhsIds.begin(), rhsIds.end(), "damageType1") != rhsIds.end();
			if (bLhsContainDamageType && bRhsContainDamageType)
			{
				auto& lhsDamageIds = TraitRepository::GetInstance().allTraitsIds[lhs.trait->GetTraitWithId("damageType1")->index];
				auto& rhsDamageIds = TraitRepository::GetInstance().allTraitsIds[rhs.trait->GetTraitWithId("damageType1")->index];
				if (lhsDamageIds != rhsDamageIds)
				{
					return 20;
				}
			}

			const bool bLhsContainHealing = std::find(lhsIds.begin(), lhsIds.end(), "healing") != lhsIds.end();
			if (bLhsContainHealing)
			{
				return 20;
			}
		}

		return 1;
	}
	else if (std::find(rhsIds.begin(), rhsIds.end(), "resourceRelated") != rhsIds.end())
	{
		const bool bRhsContainVampirism = std::find(rhsIds.begin(), rhsIds.end(), "vampirism") != rhsIds.end();
		if (bRhsContainVampirism)
		{
			return 5;
		}

		return 20;
	}
	else if (std::find(rhsIds.begin(), rhsIds.end(), "alteration") != rhsIds.end())
	{
		return 1;
	}

	return 0;
}

int Property::DistLhsStats(const Property& lhs, const Property& rhs)
{
	auto& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs.trait->index];
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs.trait->index];

	if (std::find(rhsIds.begin(), rhsIds.end(), "stats") != rhsIds.end())
	{
		const bool bLhsContainOffensive = std::find(lhsIds.begin(), lhsIds.end(), "offensive") != lhsIds.end();
		const bool bRhsContainOffensive = std::find(rhsIds.begin(), rhsIds.end(), "offensive") != rhsIds.end();
		const bool bLhsContainDefensive = std::find(lhsIds.begin(), lhsIds.end(), "defensive") != lhsIds.end();
		const bool bRhsContainDefensive = std::find(rhsIds.begin(), rhsIds.end(), "defensive") != rhsIds.end();

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
			const bool bLhsSpecCritical =
					std::find(lhsIds.begin(), lhsIds.end(), "specCriticalChance") != lhsIds.end() ||
					std::find(lhsIds.begin(), lhsIds.end(), "specCriticalEffect") != lhsIds.end();
			const bool bRhsSpecCritical =
					std::find(rhsIds.begin(), rhsIds.end(), "specCriticalChance") != rhsIds.end() ||
					std::find(rhsIds.begin(), rhsIds.end(), "specCriticalEffect") != rhsIds.end();
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
				const bool bLhsContainId = std::find(lhsIds.begin(), lhsIds.end(), id) != lhsIds.end();
				const bool bRhsContainId = std::find(rhsIds.begin(), rhsIds.end(), id) != rhsIds.end();
				if (bLhsContainId && bRhsContainId)
				{
					return 1;
				}
			}

			return 20;
		}

		return 1;
	}
	else if (std::find(rhsIds.begin(), rhsIds.end(), "resourceRelated") != rhsIds.end())
	{
		const bool bLhsContainOffensive = std::find(lhsIds.begin(), lhsIds.end(), "offensive") != lhsIds.end();
		const bool bLhsContainDefensive = std::find(lhsIds.begin(), lhsIds.end(), "defensive") != lhsIds.end();
		const bool bRhsContainVampirism = std::find(rhsIds.begin(), rhsIds.end(), "vampirism") != rhsIds.end();

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
	else if (std::find(rhsIds.begin(), rhsIds.end(), "alteration") != rhsIds.end())
	{
		const bool bLhsContainOffensive = std::find(lhsIds.begin(), lhsIds.end(), "offensive") != lhsIds.end();
		const bool bLhsContainDefensive = std::find(lhsIds.begin(), lhsIds.end(), "defensive") != lhsIds.end();

		if (bLhsContainOffensive)
		{
			return 1;
		}

		return 20;
	}

	return 0;
}

int Property::DistLhsResourceRelated(const Property& lhs, const Property& rhs)
{
	auto& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs.trait->index];
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs.trait->index];

	if (std::find(rhsIds.begin(), rhsIds.end(), "resourceRelated") != rhsIds.end())
	{
		std::vector<std::vector<std::string>> idListOfPossibleEquals = { {"mana", "manaRegen", "manaVemp"},
			{"health", "healthRegen", "healthVamp"}, {"shield", "shieldRegen", "shieldVamp"} };
		for (auto& idList : idListOfPossibleEquals)
		{
			for (auto& lhsId : idList)
			{
				const bool bLhsContainId = std::find(lhsIds.begin(), lhsIds.end(), lhsId) != lhsIds.end();
				for (auto& rhsId : idList)
				{
					const bool bRhsContainId = std::find(rhsIds.begin(), rhsIds.end(), rhsId) != rhsIds.end();
					if (bLhsContainId && bRhsContainId)
					{
						return 1;
					}
				}
			}
		}

		return 20;
	}
	else if (std::find(rhsIds.begin(), rhsIds.end(), "alteration") != rhsIds.end())
	{
		return 1;
	}

	return 0;
}

int Property::DistLhsAlteration(const Property& lhs, const Property& rhs)
{
	return 1;
}

int Property::DistForDamageOrHealing(const Property& lhs, const Property& rhs)
{
	auto& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs.trait->index];
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs.trait->index];

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
			auto& lhsDamageIds = TraitRepository::GetInstance().allTraitsIds[lhs.trait->GetTraitWithId("damage")->index];
			auto& rhsDamageIds = TraitRepository::GetInstance().allTraitsIds[rhs.trait->GetTraitWithId("damage")->index];
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
			auto& lhsHealingIds = TraitRepository::GetInstance().allTraitsIds[lhs.trait->GetTraitWithId("healing")->index];
			auto& rhsHealingIds = TraitRepository::GetInstance().allTraitsIds[rhs.trait->GetTraitWithId("healing")->index];
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

int Property::DistForDamageType1(const Property& lhs, const Property& rhs)
{
	auto& lhsIds = TraitRepository::GetInstance().allTraitsIds[lhs.trait->index];
	auto& rhsIds = TraitRepository::GetInstance().allTraitsIds[rhs.trait->index];

	const bool bLhsContainDamageType = std::find(lhsIds.begin(), lhsIds.end(), "damageType1") != lhsIds.end();
	const bool bRhsContainDamageType = std::find(rhsIds.begin(), rhsIds.end(), "damageType1") != rhsIds.end();
	if (bLhsContainDamageType && bRhsContainDamageType)
	{
		auto& lhsDamageIds = TraitRepository::GetInstance().allTraitsIds[lhs.trait->GetTraitWithId("damageType1")->index];
		auto& rhsDamageIds = TraitRepository::GetInstance().allTraitsIds[rhs.trait->GetTraitWithId("damageType1")->index];
		if (lhsDamageIds != rhsDamageIds)
		{
			return 20;
		}
	}

	return 1;
}

