#include "stdafx.h"
#include "Constants.h"
#include "PropertyDistance.h"
#include "PropertyRepository.h"
#include <algorithm>

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
}

int PropertyDistance::DistanceBetweenProperties(const Property& lhs, const Property& rhs)
{
	return 0;
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
				AREA_OF_EFFECT_DAMAGE, DIRECT_DAMAGE, OVER_TIME_DAMAGE, DURATION_OF_DOT };
	}
	else if (lower == ATTACK_SPEED)
	{
		similar = { ATTACK_SPEED, HIT_CHANCE, CRITICAL_CHANCE, CRITICAL_AMP, SINGLE_TARGET_DAMAGE,
				AREA_OF_EFFECT_SIZE, AREA_OF_EFFECT_DAMAGE, DIRECT_DAMAGE, OVER_TIME_DAMAGE, DURATION_OF_DOT };
	}
	else if (lower == CAST_SPEED)
	{
		similar = { CAST_SPEED, HIT_CHANCE, CRITICAL_CHANCE, CRITICAL_AMP, SINGLE_TARGET_DAMAGE,
				AREA_OF_EFFECT_SIZE, AREA_OF_EFFECT_DAMAGE, DIRECT_DAMAGE, OVER_TIME_DAMAGE, DURATION_OF_DOT };
	}
	else if (lower == DODGE_CHANCE || lower == RESISTANCE)
	{
		similar = { DODGE_CHANCE, RESISTANCE };
	}
	else if (lower == HIT_CHANCE || lower == CRITICAL_CHANCE || lower == CRITICAL_AMP)
	{
		similar = { HIT_CHANCE, CRITICAL_CHANCE, CRITICAL_AMP, SINGLE_TARGET_DAMAGE,
				AREA_OF_EFFECT_SIZE, AREA_OF_EFFECT_DAMAGE, DIRECT_DAMAGE, OVER_TIME_DAMAGE, DURATION_OF_DOT };
	}
	else if (lower == SINGLE_TARGET_DAMAGE)
	{
		similar = { SINGLE_TARGET_DAMAGE, DIRECT_DAMAGE, OVER_TIME_DAMAGE, DURATION_OF_DOT };
	}
	else if (lower == AREA_OF_EFFECT_SIZE || lower == AREA_OF_EFFECT_DAMAGE)
	{
		similar = { AREA_OF_EFFECT_SIZE, AREA_OF_EFFECT_DAMAGE, DIRECT_DAMAGE, OVER_TIME_DAMAGE, DURATION_OF_DOT };
	}
	else if (lower == DIRECT_DAMAGE)
	{
		similar = { DIRECT_DAMAGE };
	}
	else if (lower == OVER_TIME_DAMAGE || lower == DURATION_OF_DOT)
	{
		similar = { OVER_TIME_DAMAGE, DURATION_OF_DOT };
	}

	if (std::find(similar.begin(), similar.end(), higher) != similar.end())
	{
		return 0;
	}

	return 20;
}

