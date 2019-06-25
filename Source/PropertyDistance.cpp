#include "stdafx.h"
#include "PropertyDistance.h"
#include "PropertyRepository.h"
#include "Utils/Constants.h"
#include <algorithm>

const int PropertyDistance::NOT_SIMILAR = 20;
const int PropertyDistance::SOMEWHAT_SIMILAR = 5;
const int PropertyDistance::SIMILAR = 0;

const int PropertyDistance::NO_TYPE = 0;
const int PropertyDistance::DAMAGE_TYPE1 = 1;
const int PropertyDistance::DAMAGE_TYPE2 = 2;
const int PropertyDistance::WEAPON_TYPE1 = 1;
const int PropertyDistance::WEAPON_TYPE2 = 2;

PropertyDistance::PropertyDistance()
{
	PropertyRepository& rep = PropertyRepository::GetInstance();

	for (auto lhsIt = rep.baseProperties.begin(); lhsIt != rep.baseProperties.end(); lhsIt++)
	{
		for (auto rhsIt = lhsIt; rhsIt != rep.baseProperties.end(); rhsIt++)
		{
			const int baseDistance = DistanceBetweenBaseProperties(*lhsIt, *rhsIt);
			basePropertyDistances[*lhsIt][*rhsIt] = baseDistance;
			basePropertyDistances[*rhsIt][*lhsIt] = baseDistance;
		}
	}

	for (auto lhsIt = rep.damageTypes.begin(); lhsIt != rep.damageTypes.end(); lhsIt++)
	{
		for (auto rhsIt = lhsIt; rhsIt != rep.damageTypes.end(); rhsIt++)
		{
			const int damageDistance = DistanceBetweenDamageTypes(*lhsIt, *rhsIt);
			damageTypeDistances[*lhsIt][*rhsIt] = damageDistance;
			damageTypeDistances[*rhsIt][*lhsIt] = damageDistance;
		}
	}

	for (auto lhsIt = rep.weaponTypes.begin(); lhsIt != rep.weaponTypes.end(); lhsIt++)
	{
		for (auto rhsIt = lhsIt; rhsIt != rep.weaponTypes.end(); rhsIt++)
		{
			const int weaponDistance = DistanceBetweenWeaponTypes(*lhsIt, *rhsIt);
			weaponTypeDistances[*lhsIt][*rhsIt] = weaponDistance;
			weaponTypeDistances[*rhsIt][*lhsIt] = weaponDistance;
		}
	}
}

int PropertyDistance::DistanceBetweenProperties(const Property& lhs, const Property& rhs)
{
	int dist = 0;
	dist += basePropertyDistances[lhs.ids[0]][rhs.ids[0]];
	dist += damageTypeDistances[lhs.ids[1]][rhs.ids[1]];
	dist += weaponTypeDistances[lhs.ids[2]][rhs.ids[2]];
	return dist;
}

int PropertyDistance::DistanceBetweenBaseProperties(const std::string& lhs, const std::string& rhs)
{
	if (lhs == rhs)
	{
		return 0;
	}

	const PropertyRepository& rep = PropertyRepository::GetInstance();
	auto lhsIt = std::find(rep.baseProperties.begin(), rep.baseProperties.end(), lhs);
	auto rhsIt = std::find(rep.baseProperties.begin(), rep.baseProperties.end(), rhs);

	std::string lower = std::distance(lhsIt, rhsIt) > 0 ? lhs : rhs;
	std::string higher = lower == lhs ? rhs : lhs;

	std::vector<std::string> similar;

	if (lower == HEALTH || lower == HEALTH_REGEN)
	{
		similar = { HEALTH, HEALTH_REGEN, DODGE_CHANCE, RESISTANCE, MANA, MANA_REGEN };
	}
	else if (lower == MANA || lower == MANA_REGEN)
	{
		similar = { HEALTH_REGEN, MANA, MANA_REGEN, ATTACK_SPEED, CAST_SPEED, HIT_CHANCE,
				CRITICAL_CHANCE, CRITICAL_AMP, SINGLE_TARGET_DAMAGE, AREA_OF_EFFECT_SIZE,
				AREA_OF_EFFECT_DAMAGE, DIRECT_DAMAGE, DAMAGE_OVER_TIME, DURATION_OF_DOT };
	}
	else if (lower == ATTACK_SPEED)
	{
		similar = { ATTACK_SPEED, HIT_CHANCE, CRITICAL_CHANCE, CRITICAL_AMP, SINGLE_TARGET_DAMAGE,
				AREA_OF_EFFECT_SIZE, AREA_OF_EFFECT_DAMAGE, DIRECT_DAMAGE, DAMAGE_OVER_TIME, DURATION_OF_DOT };
	}
	else if (lower == CAST_SPEED)
	{
		similar = { CAST_SPEED, HIT_CHANCE, CRITICAL_CHANCE, CRITICAL_AMP, SINGLE_TARGET_DAMAGE,
				AREA_OF_EFFECT_SIZE, AREA_OF_EFFECT_DAMAGE, DIRECT_DAMAGE, DAMAGE_OVER_TIME, DURATION_OF_DOT };
	}
	else if (lower == DODGE_CHANCE || lower == RESISTANCE)
	{
		similar = { DODGE_CHANCE, RESISTANCE };
	}
	else if (lower == HIT_CHANCE || lower == CRITICAL_CHANCE || lower == CRITICAL_AMP)
	{
		similar = { HIT_CHANCE, CRITICAL_CHANCE, CRITICAL_AMP, SINGLE_TARGET_DAMAGE,
				AREA_OF_EFFECT_SIZE, AREA_OF_EFFECT_DAMAGE, DIRECT_DAMAGE, DAMAGE_OVER_TIME, DURATION_OF_DOT };
	}
	else if (lower == SINGLE_TARGET_DAMAGE)
	{
		similar = { SINGLE_TARGET_DAMAGE, DIRECT_DAMAGE, DAMAGE_OVER_TIME, DURATION_OF_DOT };
	}
	else if (lower == AREA_OF_EFFECT_SIZE || lower == AREA_OF_EFFECT_DAMAGE)
	{
		similar = { AREA_OF_EFFECT_SIZE, AREA_OF_EFFECT_DAMAGE, DIRECT_DAMAGE, DAMAGE_OVER_TIME, DURATION_OF_DOT };
	}
	else if (lower == DIRECT_DAMAGE)
	{
		similar = { DIRECT_DAMAGE };
	}
	else if (lower == DAMAGE_OVER_TIME || lower == DURATION_OF_DOT)
	{
		similar = { DAMAGE_OVER_TIME, DURATION_OF_DOT };
	}

	if (std::find(similar.begin(), similar.end(), higher) != similar.end())
	{
		return SIMILAR;
	}

	return NOT_SIMILAR;
}

int PropertyDistance::DistanceBetweenDamageTypes(const std::string& lhs, const std::string& rhs)
{
	if (lhs == rhs)
	{
		return SIMILAR;
	}

	if (lhs == NO_DAMAGE_TYPE || rhs == NO_DAMAGE_TYPE)
	{
		return SOMEWHAT_SIMILAR;
	}
	else if (GetTypeOfDamageType(lhs) == GetTypeOfDamageType(rhs))
	{
		return lhs == rhs ? SIMILAR : NOT_SIMILAR;
	}

	return SIMILAR;
}

int PropertyDistance::GetTypeOfDamageType(const std::string& damageType)
{
	if (damageType == NO_DAMAGE_TYPE)
	{
		return NO_TYPE;
	}
	else if (damageType == PHYSICAL || damageType == MAGICAL)
	{
		return DAMAGE_TYPE1;
	}

	return DAMAGE_TYPE2;
}

int PropertyDistance::DistanceBetweenWeaponTypes(const std::string& lhs, const std::string& rhs)
{
	if (lhs == rhs)
	{
		return SIMILAR;
	}

	if (lhs == NO_WEAPON_TYPE || rhs == NO_WEAPON_TYPE)
	{
		return SOMEWHAT_SIMILAR;
	}
	else if (GetTypeOfWeaponType(lhs) == GetTypeOfWeaponType(rhs))
	{
		return lhs == rhs ? SIMILAR : NOT_SIMILAR;
	}
	else
	{
		auto& type1 = GetTypeOfWeaponType(lhs) == WEAPON_TYPE1 ? lhs : rhs;
		auto& type2 = type1 == lhs ? rhs : lhs;

		std::vector<std::string> similar;

		if (type1 == ONE_HANDED)
		{
			similar = { AXE, DAGGER, FIST_WEAPON, GUN, MACE, SWORD, THROWN, WAND };
		}
		else
		{
			similar = { AXE, BOW, CROSSBOW, GUN, MACE, POLEARM, STAFF, SWORD };
		}

		if (std::find(similar.begin(), similar.end(), type2) != similar.end())
		{
			return SIMILAR;
		}
	}

	return NOT_SIMILAR;
}

int PropertyDistance::GetTypeOfWeaponType(const std::string& weaponType)
{
	if (weaponType == NO_WEAPON_TYPE)
	{
		return NO_TYPE;
	}
	else if (weaponType == ONE_HANDED || weaponType == TWO_HANDED)
	{
		return WEAPON_TYPE1;
	}
	return WEAPON_TYPE2;
}

