#include "stdafx.h"
#include "TraitDictionary.h"

TraitDictionary::TraitDictionary()
{
	std::vector<TraitDictEntry*> dictEntries;
	dictEntries.push_back(new TraitDictEntry{ "direct", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "duration", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "potency", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "urgency", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "alterationType", ALTERNATIVES, { "duration", "potency", "urgency" } });
	dictEntries.push_back(new TraitDictEntry{ "affectType1", ALTERNATIVES, { "direct", "alterationType" } });

	dictEntries.push_back(new TraitDictEntry{ "singleTarget", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "radius", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "power", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "areaOfEffect", ALTERNATIVES, { "radius", "power" } });
	dictEntries.push_back(new TraitDictEntry{ "affectType2", ALTERNATIVES, { "singleTarget", "areaOfEffect" } });
	dictEntries.push_back(new TraitDictEntry{ "affectType", ALTERNATIVES, { "affectType1", "affectType2" } });

	dictEntries.push_back(new TraitDictEntry{ "physical", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "supernatural", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "damageType1", ALTERNATIVES, { "physical", "supernatural" } });

	dictEntries.push_back(new TraitDictEntry{ "fire", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "frost", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "lightning", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "elemental", ALTERNATIVES, { "fire", "frost", "lightning" } });
	dictEntries.push_back(new TraitDictEntry{ "psychic", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "sound", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "kinetic", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "acid", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "bleed", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "necrotic", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "holy", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "unhallow", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "damageType2", ALTERNATIVES,
			{ "elemental", "psychic", "sound", "kinetic", "acid", "bleed", "necrotic", "holy", "unhallow" } });
	dictEntries.push_back(new TraitDictEntry{ "damageType", ALTERNATIVES, { "damageType1", "damageType2" } });

	dictEntries.push_back(new TraitDictEntry{ "allDamage", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "damage", ALTERNATIVES, { "allDamage", "damageType" } });

	dictEntries.push_back(new TraitDictEntry{ "restoration", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "absorption", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "healingType", ALTERNATIVES, { "restoration", "absorption" } });
	dictEntries.push_back(new TraitDictEntry{ "allHealing", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "healing", ALTERNATIVES, { "allHealing", "healingType" } });

	dictEntries.push_back(new TraitDictEntry{ "affect1", CONCATENATIONS, { "affectType", "damage" } });
	dictEntries.push_back(new TraitDictEntry{ "affect2", CONCATENATIONS, { "affectType", "healing" } });
	dictEntries.push_back(new TraitDictEntry{ "affect", ALTERNATIVES, { "affect1", "affect2" } });



	dictEntries.push_back(new TraitDictEntry{ "attackSpeed", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "castSpeed", TERMINAL, {} });

	dictEntries.push_back(new TraitDictEntry{ "allCriticalChance", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "specCriticalChance", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "criticalChanceDamage", CONCATENATIONS,
			{ "specCriticalChance", "damage" } });
	dictEntries.push_back(new TraitDictEntry{ "criticalChanceHealing", CONCATENATIONS,
			{ "specCriticalChance", "healing" } });
	dictEntries.push_back(new TraitDictEntry{ "criticalChance", ALTERNATIVES,
			{ "allCriticalChance", "criticalChanceDamage", "criticalChanceHealing" } });

	dictEntries.push_back(new TraitDictEntry{ "allCriticalEffect", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "specCriticalEffect", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "criticalEffectDamage", CONCATENATIONS,
			{ "specCriticalEffect", "damage" } });
	dictEntries.push_back(new TraitDictEntry{ "criticalEffectHealing", CONCATENATIONS,
			{ "specCriticalEffect", "healing" } });
	dictEntries.push_back(new TraitDictEntry{ "criticalEffect", ALTERNATIVES,
			{ "allCriticalEffect", "criticalEffectDamage", "criticalEffectHealing" } });
	dictEntries.push_back(new TraitDictEntry{ "critical", ALTERNATIVES, { "criticalChance", "criticalEffect" } });

	dictEntries.push_back(new TraitDictEntry{ "allHitChance", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "specHitChance", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "hitChanceDamage", CONCATENATIONS, { "specHitChance", "damageType1" } });
	dictEntries.push_back(new TraitDictEntry{ "hitChance", ALTERNATIVES, { "allHitChance", "hitChanceDamage" } });
	dictEntries.push_back(new TraitDictEntry{ "offensive", ALTERNATIVES,
			{ "attackSpeed", "castSpeed", "critical", "hitChance" } });

	dictEntries.push_back(new TraitDictEntry{ "allEvasionChance", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "specEvasionChance", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "evasionChanceDamage", CONCATENATIONS,
			{ "specEvasionChance", "damageType1" } });
	dictEntries.push_back(new TraitDictEntry{ "evasion", ALTERNATIVES, { "allEvasionChance", "evasionChanceDamage" } });

	dictEntries.push_back(new TraitDictEntry{ "allDodgeChance", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "specDodgeChance", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "dodgeChanceDamage", CONCATENATIONS,
			{ "specDodgeChance", "damageType1" } });
	dictEntries.push_back(new TraitDictEntry{ "allDodgeReduction", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "specDodgeReduction", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "dodgeReductionDamage", CONCATENATIONS,
			{ "specDodgeReduction", "damageType1" } });
	dictEntries.push_back(new TraitDictEntry{ "dodge", ALTERNATIVES,
			{ "allDodgeChance", "dodgeChanceDamage", "allDodgeReduction", "dodgeReductionDamage" } });

	dictEntries.push_back(new TraitDictEntry{ "allBlockChance", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "specBlockChance", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "blockChanceDamage", CONCATENATIONS,
			{ "specBlockChance", "damageType1" } });
	dictEntries.push_back(new TraitDictEntry{ "allBlockReduction", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "specBlockReduction", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "blockReductionDamage", CONCATENATIONS,
			{ "specBlockReduction", "damageType1" } });
	dictEntries.push_back(new TraitDictEntry{ "block", ALTERNATIVES,
			{ "allBlockChance", "blockChanceDamage", "allBlockReduction", "blockReductionDamage" } });

	dictEntries.push_back(new TraitDictEntry{ "allArmour", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "specArmour", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "armourDamage", CONCATENATIONS, { "specArmour", "damageType1" } });
	dictEntries.push_back(new TraitDictEntry{ "armour", ALTERNATIVES, { "allArmour", "armourDamage" } });
	dictEntries.push_back(new TraitDictEntry{ "defensive", ALTERNATIVES, { "evasion", "dodge", "block", "armour" } });

	dictEntries.push_back(new TraitDictEntry{ "movementSpeed", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "cooldown", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "stats", ALTERNATIVES,
			{ "offensive", "defensive", "movementSpeed", "cooldown" } });



	dictEntries.push_back(new TraitDictEntry{ "health", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "mana", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "shield", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "resource", ALTERNATIVES, { "health", "mana", "shield" } });

	dictEntries.push_back(new TraitDictEntry{ "healthRegen", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "manaRegen", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "shieldRegen", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "regen", ALTERNATIVES, { "healthRegen", "manaRegen", "shieldRegen" } });

	dictEntries.push_back(new TraitDictEntry{ "healthVamp", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "manaVamp", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "shieldVamp", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "vampirism", ALTERNATIVES, { "healthVamp", "manaVamp", "shieldVamp" } });
	dictEntries.push_back(new TraitDictEntry{ "resourceRecovery", ALTERNATIVES, { "regen", "vampirism" } });
	dictEntries.push_back(new TraitDictEntry{ "resourceRelated", ALTERNATIVES, { "resource", "resourceRecovery" } });



	dictEntries.push_back(new TraitDictEntry{ "beneficial", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "alterationBeneficial", CONCATENATIONS,
			{ "alterationType", "beneficial" } });

	dictEntries.push_back(new TraitDictEntry{ "detrimental", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "alterationDetrimental", CONCATENATIONS,
			{ "alterationType", "detrimental" } });
	dictEntries.push_back(new TraitDictEntry{ "alteration", ALTERNATIVES,
			{ "alterationBeneficial", "alterationDetrimental" } });

	dictEntries.push_back(new TraitDictEntry{ "attributes", TERMINAL, {} });

	dictEntries.push_back(new TraitDictEntry{ "allWeapon", TERMINAL, {} });

	dictEntries.push_back(new TraitDictEntry{ "oneHanded", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "twoHanded", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "weaponType1", ALTERNATIVES,
			{"oneHanded", "twoHanded"} });

	dictEntries.push_back(new TraitDictEntry{ "axe", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "sword", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "mace", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "polearm", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "dagger", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "scythe", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "fist", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "staff", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "wand", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "card", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "bow", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "crossbow", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "thrown", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "shield", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "relic", TERMINAL, {} });
	dictEntries.push_back(new TraitDictEntry{ "weaponType2", ALTERNATIVES,
			{"axe", "sword", "mace", "polearm", "dagger", "scythe", "fist",
					"staff" ,"wand", "card", "bow", "crossbow", "thrown", "shield", "relic"} });

	dictEntries.push_back(new TraitDictEntry{ "weaponType", ALTERNATIVES,
			{"weaponType1", "weaponType2"} });

	dictEntries.push_back(new TraitDictEntry{ "weapon", ALTERNATIVES,
			{"allWeapon", "weaponType"} });

	dictEntries.push_back(new TraitDictEntry{ "affectWeapon", CONCATENATIONS,
			{ "affect", "weapon"} });
	dictEntries.push_back(new TraitDictEntry{ "statsWeapon", CONCATENATIONS,
			{ "stats", "weapon"} });
	dictEntries.push_back(new TraitDictEntry{ "resourceRelatedWeapon", CONCATENATIONS,
			{ "resourceRelated", "weapon"} });
	dictEntries.push_back(new TraitDictEntry{ "alterationWeapon", CONCATENATIONS,
			{ "alteration", "weapon"} });

	dictEntries.push_back(new TraitDictEntry{ "general", ALTERNATIVES,
			{ "affectWeapon", "statsWeapon", "resourceRelatedWeapon", "alterationWeapon" } });

	dictEntries.push_back(new TraitDictEntry{ "property", ALTERNATIVES,
			{ "attributes", "general" } });

	for (auto* e : dictEntries)
	{
		entries.push_back(std::unique_ptr<TraitDictEntry>(e));
	}
}

