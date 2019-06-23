#include "stdafx.h"
#include "Utils/Constants.h"
#include "PropertyDictionary.h"

PropertyDictionary::PropertyDictionary()
{
	std::vector<std::string> noDamageType = { NO_DAMAGE_TYPE };
	std::vector<std::string> onlyDamageType1 = { PHYSICAL, MAGICAL};
	std::vector<std::string> onlyDamageType2 = { ACID, BLUDGEONING, COLD, FIRE, FORCE, LIGHTNING,
			NECROTIC, PIERCING, POISON, PSYCHIC, RADIANT, SLASHING, THUNDER };
	std::vector<std::string> damageType1(noDamageType);
	std::copy(onlyDamageType1.begin(), onlyDamageType1.end(), std::back_inserter(damageType1));
	std::vector<std::string> allDamageType(noDamageType);
	std::copy(onlyDamageType1.begin(), onlyDamageType1.end(), std::back_inserter(allDamageType));
	std::copy(onlyDamageType2.begin(), onlyDamageType2.end(), std::back_inserter(allDamageType));

	std::vector<std::string> weaponType = { NO_WEAPON_TYPE, ONE_HANDED, TWO_HANDED, AXE, BOW, CROSSBOW,
			DAGGER, FIST_WEAPON, GUN, MACE, POLEARM, STAFF, SWORD, THROWN, WAND };

	std::vector<PropertyDictEntry*> dictEntries;
	dictEntries.push_back(new PropertyDictEntry{ HEALTH, noDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ MANA, noDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ HEALTH_REGEN, noDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ MANA_REGEN, noDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ ATTACK_SPEED, noDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ CAST_SPEED, noDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ DODGE_CHANCE, damageType1, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ RESISTANCE, damageType1, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ HIT_CHANCE, allDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ CRITICAL_CHANCE, allDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ CRITICAL_AMP, allDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ SINGLE_TARGET_DAMAGE, allDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ AREA_OF_EFFECT_SIZE, allDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ AREA_OF_EFFECT_DAMAGE, allDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ DIRECT_DAMAGE, allDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ OVER_TIME_DAMAGE, allDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ DURATION_OF_DOT, allDamageType, weaponType });

	for (auto* e : dictEntries)
	{
		managedEntries.push_back(std::unique_ptr<PropertyDictEntry>(e));
		entries.push_back(e);
	}
}

