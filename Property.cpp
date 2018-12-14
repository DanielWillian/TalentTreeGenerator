#include "stdafx.h"
#include "Property.h"
#include <stdexcept>
#include <algorithm>

int Property::DistanceBetweenProperties(const Property& lhs, const Property& rhs)
{
	const Property* lesserProperty = GetLesserProperty(lhs, rhs);
	const Property* otherProperty = *lesserProperty == lhs ? &rhs : &lhs;
	std::vector<std::string> lesserIds = lesserProperty->trait->GetAllTraitIds();

	if (std::find(lesserIds.begin(), lesserIds.end(), "affect") != lesserIds.end())
	{
		return DistLhsAffect(*lesserProperty, *otherProperty);
	}
	else if (std::find(lesserIds.begin(), lesserIds.end(), "stats") != lesserIds.end())
	{
		return DistLhsStats(*lesserProperty, *otherProperty);
	}
	else if (std::find(lesserIds.begin(), lesserIds.end(), "resourceRelated") != lesserIds.end())
	{
		return DistLhsResourceRelated(*lesserProperty, *otherProperty);
	}
	else if (std::find(lesserIds.begin(), lesserIds.end(), "alteration") != lesserIds.end())
	{
		return DistLhsAlteration(*lesserProperty, *otherProperty);
	}

	return 0;
}

const Property* Property::GetLesserProperty(const Property& lhs, const Property& rhs)
{
	std::vector<std::string> lhsIds = lhs.trait->GetAllTraitIds();
	std::vector<std::string> rhsIds = rhs.trait->GetAllTraitIds();

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

int Property::DistLhsAffect(const Property& lhs, const Property& rhs)
{
	auto lhsIds = lhs.trait->GetAllTraitIds();
	auto rhsIds = rhs.trait->GetAllTraitIds();

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
			auto lhsAffectTypeIds = lhs.trait->GetTraitWithId("affectType")->GetAllTraitIds();
			auto rhsAffectTypeIds = rhs.trait->GetTraitWithId("affectType")->GetAllTraitIds();
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
				auto lhsDamageIds = lhs.trait->GetTraitWithId("damageType1")->GetAllTraitIds();
				auto rhsDamageIds = rhs.trait->GetTraitWithId("damageType1")->GetAllTraitIds();
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
	auto lhsIds = lhs.trait->GetAllTraitIds();
	auto rhsIds = rhs.trait->GetAllTraitIds();

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
	auto lhsIds = lhs.trait->GetAllTraitIds();
	auto rhsIds = rhs.trait->GetAllTraitIds();

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
	auto lhsIds = lhs.trait->GetAllTraitIds();
	auto rhsIds = rhs.trait->GetAllTraitIds();

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
			auto lhsDamageIds = lhs.trait->GetTraitWithId("damage")->GetAllTraitIds();
			auto rhsDamageIds = rhs.trait->GetTraitWithId("damage")->GetAllTraitIds();
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
			auto lhsHealingIds = lhs.trait->GetTraitWithId("healing")->GetAllTraitIds();
			auto rhsHealingIds = rhs.trait->GetTraitWithId("healing")->GetAllTraitIds();
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
	auto lhsIds = lhs.trait->GetAllTraitIds();
	auto rhsIds = rhs.trait->GetAllTraitIds();

	const bool bLhsContainDamageType = std::find(lhsIds.begin(), lhsIds.end(), "damageType1") != lhsIds.end();
	const bool bRhsContainDamageType = std::find(rhsIds.begin(), rhsIds.end(), "damageType1") != rhsIds.end();
	if (bLhsContainDamageType && bRhsContainDamageType)
	{
		auto lhsDamageIds = lhs.trait->GetTraitWithId("damageType1")->GetAllTraitIds();
		auto rhsDamageIds = rhs.trait->GetTraitWithId("damageType1")->GetAllTraitIds();
		if (lhsDamageIds != rhsDamageIds)
		{
			return 20;
		}
	}

	return 1;
}

