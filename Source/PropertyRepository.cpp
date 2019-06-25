#include "stdafx.h"
#include "PropertyRepository.h"
#include "Utils/Constants.h"

PropertyRepository::PropertyRepository()
{
	baseProperties = { HEALTH, MANA, HEALTH_REGEN, MANA_REGEN, ATTACK_SPEED, CAST_SPEED, DODGE_CHANCE,
			RESISTANCE, HIT_CHANCE, CRITICAL_CHANCE, CRITICAL_AMP, SINGLE_TARGET_DAMAGE,
			AREA_OF_EFFECT_SIZE, AREA_OF_EFFECT_DAMAGE, DIRECT_DAMAGE, DAMAGE_OVER_TIME, DURATION_OF_DOT };
	damageTypes = { NO_DAMAGE_TYPE, PHYSICAL, MAGICAL, ACID, BLUDGEONING, COLD, FIRE, FORCE, LIGHTNING,
			NECROTIC, PIERCING, POISON, PSYCHIC, RADIANT, SLASHING, THUNDER };
	weaponTypes = { NO_WEAPON_TYPE, ONE_HANDED, TWO_HANDED, AXE, BOW, CROSSBOW,
			DAGGER, FIST_WEAPON, GUN, MACE, POLEARM, STAFF, SWORD, THROWN, WAND };

	for (auto* p : GeneratePropertiesFromDictionary(propertyDictionary))
	{
		allProperties.push_back(std::unique_ptr<Property>(p));
	}

	std::vector<Property*> properties;
	for (const auto& ptr : allProperties)
	{
		properties.push_back(ptr.get());
	}

	auto level2 = GetPropertiesWithIds(properties, { HEALTH, NO_WEAPON_TYPE });
	auto level7 = properties;
	auto level4 = GetPropertiesWithIds(level7, { NO_WEAPON_TYPE });
	auto level1 = GetPropertiesWithIds(level4, { NO_DAMAGE_TYPE });
	auto level9 = level1;
	level1Properties.insert(std::end(level1Properties), std::begin(level1), std::end(level1));
	level3Properties.insert(std::end(level3Properties), std::begin(level1), std::end(level1));

	level2Properties.insert(std::end(level2Properties), std::begin(level2), std::end(level2));

	level4Properties.insert(std::end(level4Properties), std::begin(level4), std::end(level4));
	level6Properties.insert(std::end(level6Properties), std::begin(level4), std::end(level4));

	level5Properties.insert(std::end(level5Properties), std::begin(level2), std::end(level2));

	level7Properties.insert(std::end(level7Properties), std::begin(level7), std::end(level7));
	level8Properties.insert(std::end(level8Properties), std::begin(level7), std::end(level7));

	level9Properties.insert(std::end(level9Properties), std::begin(level9), std::end(level9));
}

std::vector<Property*> PropertyRepository::GeneratePropertiesFromDictionary(const PropertyDictionary& dict)
{
	std::vector<Property*> result;

	int index = 0;
	for (auto* e : dict.entries)
	{
		for (auto& damageType : e->damageTypes)
		{
			for (auto& weaponType : e->weaponTypes)
			{
				result.push_back(new Property(index++, { e->id, damageType, weaponType }));
			}
		}
	}

	return result;
}

std::vector<Property*> PropertyRepository::GetPropertiesWithoutIds(
		const std::vector<Property*>& properties,
		const std::vector<std::string>& ids) const
{
	auto result = properties;

	for (const auto& id : ids)
	{
		result.erase(std::remove_if(result.begin(), result.end(),
				[&](auto* p) -> bool
				{
					return std::find(p->ids.begin(), p->ids.end(), id) != p->ids.end();
				}),
				result.end());
	}
	std::sort(result.begin(), result.end());

	return result;
}

std::vector<Property*> PropertyRepository::GetPropertiesWithIds(const std::vector<Property*>& properties,
		const std::vector<std::string>& ids) const
{
	std::vector<Property*> result;

	for (auto* property : properties)
	{
		bool bFound = false;
		for (auto& id : ids)
		{
			bFound = false;
			for (auto& propertyId : property->ids)
			{
				if (id == propertyId)
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
			result.push_back(property);
		}
	}

	return result;
}

