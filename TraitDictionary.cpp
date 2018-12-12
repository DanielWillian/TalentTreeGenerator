#include "stdafx.h"
#include "TraitDictionary.h"

TraitDictionary::TraitDictionary()
{
	entries.push_back({ "direct", TERMINAL, {} });
	entries.push_back({ "duration", TERMINAL, {} });
	entries.push_back({ "potency", TERMINAL, {} });
	entries.push_back({ "urgency", TERMINAL, {} });
	entries.push_back({ "alterationType", ALTERNATIVES, { "duration", "potency", "urgency" } });
	entries.push_back({ "affectType1", ALTERNATIVES, { "direct", "alterationType" } });

	entries.push_back({ "singleTarget", TERMINAL, {} });
	entries.push_back({ "radius", TERMINAL, {} });
	entries.push_back({ "power", TERMINAL, {} });
	entries.push_back({ "areaOfEffect", ALTERNATIVES, { "radius", "power" } });
	entries.push_back({ "affectType2", ALTERNATIVES, { "singleTarget", "areaOfEffect" } });
	entries.push_back({ "affectType", ALTERNATIVES, { "affectType1", "affectType2" } });

	entries.push_back({ "physical", TERMINAL, {} });
	entries.push_back({ "supernatural", TERMINAL, {} });
	entries.push_back({ "damageType1", ALTERNATIVES, { "physical", "supernatural" } });

	entries.push_back({ "fire", TERMINAL, {} });
	entries.push_back({ "frost", TERMINAL, {} });
	entries.push_back({ "lightning", TERMINAL, {} });
	entries.push_back({ "elemental", ALTERNATIVES, { "fire", "frost", "lightning" } });
	entries.push_back({ "psychic", TERMINAL, {} });
	entries.push_back({ "sound", TERMINAL, {} });
	entries.push_back({ "kinetic", TERMINAL, {} });
	entries.push_back({ "acid", TERMINAL, {} });
	entries.push_back({ "bleed", TERMINAL, {} });
	entries.push_back({ "necrotic", TERMINAL, {} });
	entries.push_back({ "holy", TERMINAL, {} });
	entries.push_back({ "unhallow", TERMINAL, {} });
	entries.push_back({ "damageType2", ALTERNATIVES,
			{ "elemental", "psychic", "sound", "kinetic", "acid", "bleed", "necrotic", "holy", "unhallow" } });
	entries.push_back({ "damageType", ALTERNATIVES, { "damageType1", "damageType2" } });

	entries.push_back({ "allDamage", TERMINAL, {} });
	entries.push_back({ "damage", ALTERNATIVES, { "allDamage", "damageType" } });

	entries.push_back({ "restoration", TERMINAL, {} });
	entries.push_back({ "absorption", TERMINAL, {} });
	entries.push_back({ "healingType", ALTERNATIVES, { "restoration", "absorption" } });
	entries.push_back({ "allHealing", TERMINAL, {} });
	entries.push_back({ "healing", ALTERNATIVES, { "allHealing", "healingType" } });

	entries.push_back({ "affect1", CONCATENATIONS, { "affectType", "damage" } });
	entries.push_back({ "affect2", CONCATENATIONS, { "affectType", "healing" } });
	entries.push_back({ "affect", ALTERNATIVES, { "affect1", "affect2" } });



	entries.push_back({ "attackSpeed", TERMINAL, {} });
	entries.push_back({ "castSpeed", TERMINAL, {} });

	entries.push_back({ "allCriticalChance", TERMINAL, {} });
	entries.push_back({ "specCriticalChance", TERMINAL, {} });
	entries.push_back({ "criticalChanceDamage", CONCATENATIONS, { "specCriticalChance", "damage" } });
	entries.push_back({ "criticalChanceHealing", CONCATENATIONS, { "specCriticalChance", "healing" } });
	entries.push_back({ "criticalChance", ALTERNATIVES,
			{ "allCriticalChance", "criticalChanceDamage", "criticalChanceHealing" } });

	entries.push_back({ "allCriticalEffect", TERMINAL, {} });
	entries.push_back({ "specCriticalEffect", TERMINAL, {} });
	entries.push_back({ "criticalEffectDamage", CONCATENATIONS, { "specCriticalEffect", "damage" } });
	entries.push_back({ "criticalEffectHealing", CONCATENATIONS, { "specCriticalEffect", "healing" } });
	entries.push_back({ "criticalEffect", ALTERNATIVES,
			{ "allCriticalEffect", "criticalEffectDamage", "criticalEffectHealing" } });
	entries.push_back({ "critical", ALTERNATIVES, { "criticalChance", "criticalEffect" } });

	entries.push_back({ "allHitChance", TERMINAL, {} });
	entries.push_back({ "specHitChance", TERMINAL, {} });
	entries.push_back({ "hitChanceDamage", CONCATENATIONS, { "specHitChance", "damageType1" } });
	entries.push_back({ "hitChance", ALTERNATIVES, { "allHitChance", "hitChanceDamage" } });
	entries.push_back({ "offensive", ALTERNATIVES, { "attackSpeed", "castSpeed", "critical", "hitChance" } });

	entries.push_back({ "allEvasionChance", TERMINAL, {} });
	entries.push_back({ "specEvasionChance", TERMINAL, {} });
	entries.push_back({ "evasionChanceDamage", CONCATENATIONS, { "specEvasionChance", "damageType1" } });
	entries.push_back({ "evasion", ALTERNATIVES, { "allEvasionChance", "evasionChanceDamage" } });

	entries.push_back({ "allDodgeChance", TERMINAL, {} });
	entries.push_back({ "specDodgeChance", TERMINAL, {} });
	entries.push_back({ "dodgeChanceDamage", CONCATENATIONS, { "specDodgeChance", "damageType1" } });
	entries.push_back({ "allDodgeReduction", TERMINAL, {} });
	entries.push_back({ "specDodgeReduction", TERMINAL, {} });
	entries.push_back({ "dodgeReductionDamage", CONCATENATIONS, { "specDodgeReduction", "damageType1" } });
	entries.push_back({ "dodge", ALTERNATIVES,
			{ "allDodgeChance", "dodgeChanceDamage", "allDodgeReduction", "dodgeReductionDamage" } });

	entries.push_back({ "allBlockChance", TERMINAL, {} });
	entries.push_back({ "specBlockChance", TERMINAL, {} });
	entries.push_back({ "blockChanceDamage", CONCATENATIONS, { "specBlockChance", "damageType1" } });
	entries.push_back({ "allBlockReduction", TERMINAL, {} });
	entries.push_back({ "specBlockReduction", TERMINAL, {} });
	entries.push_back({ "blockReductionDamage", CONCATENATIONS, { "specBlockReduction", "damageType1" } });
	entries.push_back({ "block", ALTERNATIVES,
			{ "allBlockChance", "blockChanceDamage", "allBlockReduction", "blockReductionDamage" } });

	entries.push_back({ "allArmour", TERMINAL, {} });
	entries.push_back({ "specArmour", TERMINAL, {} });
	entries.push_back({ "armourDamage", CONCATENATIONS, { "specArmour", "damageType1" } });
	entries.push_back({ "armour", ALTERNATIVES, { "allArmour", "armourDamage" } });
	entries.push_back({ "defensive", ALTERNATIVES, { "evasion", "dodge", "block", "armour" } });

	entries.push_back({ "movementSpeed", TERMINAL, {} });
	entries.push_back({ "cooldown", TERMINAL, {} });
	entries.push_back({ "stats", ALTERNATIVES, { "offensive", "defensive", "movementSpeed", "cooldown" } });



	entries.push_back({ "health", TERMINAL, {} });
	entries.push_back({ "mana", TERMINAL, {} });
	entries.push_back({ "shield", TERMINAL, {} });
	entries.push_back({ "resource", ALTERNATIVES, { "health", "mana", "shield" } });

	entries.push_back({ "healthRegen", TERMINAL, {} });
	entries.push_back({ "manaRegen", TERMINAL, {} });
	entries.push_back({ "shieldRegen", TERMINAL, {} });
	entries.push_back({ "regen", ALTERNATIVES, { "healthRegen", "manaRegen", "shieldRegen" } });

	entries.push_back({ "healthVamp", TERMINAL, {} });
	entries.push_back({ "manaVamp", TERMINAL, {} });
	entries.push_back({ "shieldVamp", TERMINAL, {} });
	entries.push_back({ "vampirism", ALTERNATIVES, { "healthVamp", "manaVamp", "shieldVamp" } });
	entries.push_back({ "resourceRecovery", ALTERNATIVES, { "regen", "vampirism" } });
	entries.push_back({ "resourceRelated", ALTERNATIVES, { "resource", "resourceRecovery" } });



	entries.push_back({ "beneficial", TERMINAL, {} });
	entries.push_back({ "alterationBeneficial", CONCATENATIONS, { "alterationType", "beneficial" } });

	entries.push_back({ "detrimental", TERMINAL, {} });
	entries.push_back({ "alterationDetrimental", CONCATENATIONS, { "alterationType", "detrimental" } });
	entries.push_back({ "alteration", ALTERNATIVES, { "alterationBeneficial", "alterationDetrimental" } });

	entries.push_back({ "property", ALTERNATIVES, { "affect", "stats", "resourceRelated", "alteration" } });
}

