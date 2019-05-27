#include "stdafx.h"
#include "PropertyDictionary.h"

PropertyDictionary::PropertyDictionary()
{
	std::vector<std::string> noDamageType = { "NoDamageType" };
	std::vector<std::string> onlyDamageType1 = { "Physical", "Magical" };
	std::vector<std::string> onlyDamageType2 = { "Acid", "Bludgening", "Cold", "Fire", "Force", "Lightning",
			"Necrotic", "Piercing", "Poison", "Psychic", "Radiant", "Slashing", "Thunder" };
	std::vector<std::string> damageType1(noDamageType);
	std::copy(onlyDamageType1.begin(), onlyDamageType1.end(), std::back_inserter(damageType1));
	std::vector<std::string> allDamageType(noDamageType);
	std::copy(onlyDamageType1.begin(), onlyDamageType1.end(), std::back_inserter(allDamageType));
	std::copy(onlyDamageType2.begin(), onlyDamageType2.end(), std::back_inserter(allDamageType));

	std::vector<std::string> weaponType = { "NoWeaponType", "OneHanded", "TwoHanded", "Axe", "Bow", "Crossbow",
			"Dagger", "FistWeapon", "Gun", "Mace", "Polearm", "Staff", "Sword", "Thrown", "Wand" };
	dictEntries.push_back(new PropertyDictEntry{ "Health", noDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ "Mana", noDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ "HealthRegen", noDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ "ManaRegen", noDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ "AttackSpeed", noDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ "CastSpeed", noDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ "DodgeChance", damageType1, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ "Resistance", damageType1, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ "HitChance", allDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ "CriticalChance", allDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ "CriticalAmp", allDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ "SingleTargetDamage", allDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ "AreaOfEffectSize", allDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ "AreaOfEffectDamage", allDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ "DirectDamage", allDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ "OvertimeDamage", allDamageType, weaponType });
	dictEntries.push_back(new PropertyDictEntry{ "DurationOfDot", allDamageType, weaponType });

	std::vector<PropertyDictEntry*> dictEntries;
	for (auto* e : dictEntries)
	{
		entries.push_back(std::unique_ptr<PropertyDictEntry>(e));
	}
}

