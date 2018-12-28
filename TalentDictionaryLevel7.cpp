#include "stdafx.h"
#include "TalentDictionaryLevel7.h"

TalentDictionaryLevel7::TalentDictionaryLevel7()
{
	level = 7;
	std::vector<TalentDictEntry*> dictEntries;
	dictEntries.push_back(new TalentDictEntry{"direct", "*", BASE, {1.2f, 1.3f}});
	dictEntries.push_back(new TalentDictEntry{"duration", "*", BASE, {1.2f, 1.3f}});
	dictEntries.push_back(new TalentDictEntry{"potency", "*", BASE, {1.2f, 1.3f}});
	dictEntries.push_back(new TalentDictEntry{"urgency", "*", BASE, {1.2f, 1.3f}});
	dictEntries.push_back(new TalentDictEntry{"singleTarget", "*", BASE, {1.2f, 1.3f}});
	dictEntries.push_back(new TalentDictEntry{"radius", "*", BASE, {1.2f, 1.35f}});
	dictEntries.push_back(new TalentDictEntry{"power", "*", BASE, {1.2f, 1.3f}});
	dictEntries.push_back(new TalentDictEntry{"attackSpeed", "*", BASE, {1.1f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"castSpeed", "*", BASE, {1.1f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"allCriticalChance", "*", BASE, {1.05f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"allCriticalEffect", "*", BASE, {1.05f, 1.3f}});
	dictEntries.push_back(new TalentDictEntry{"specCriticalChance", "*", BASE, {1.05f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"specCriticalEffect", "*", BASE, {1.05f, 1.3f}});
	dictEntries.push_back(new TalentDictEntry{"allHitChance", "*", BASE, {1.05f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"specHitChance", "*", BASE, {1.05f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"allEvasionChance", "*", BASE, {1.05f, 1.35f}});
	dictEntries.push_back(new TalentDictEntry{"specEvasionChance", "*", BASE, {1.05f, 1.35f}});
	dictEntries.push_back(new TalentDictEntry{"allDodgeChance", "*", BASE, {1.05f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"specDodgeChance", "*", BASE, {1.05f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"allDodgeReduction", "*", BASE, {1.05f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"specDodgeReduction", "*", BASE, {1.05f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"allBlockChance", "*", BASE, {1.05f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"specBlockChance", "*", BASE, {1.05f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"allBlockReduction", "*", BASE, {1.05f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"specBlockReduction", "*", BASE, {1.05f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"allArmour", "*", BASE, {1.05f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"specArmour", "*", BASE, {1.05f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"movementSpeed", "*", BASE, {1.05f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"cooldown", "*", BASE, {1.1f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"health", "*", BASE, {1.05f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"mana", "*", BASE, {1.05f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"shield", "*", BASE, {1.05f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"healthRegen", "*", BASE, {1.05f, 1.3f}});
	dictEntries.push_back(new TalentDictEntry{"manaRegen", "*", BASE, {1.05f, 1.3f}});
	dictEntries.push_back(new TalentDictEntry{"shieldRegen", "*", BASE, {1.05f, 1.3f}});
	dictEntries.push_back(new TalentDictEntry{"healthVamp", "*", BASE, {1.05f, 1.3f}});
	dictEntries.push_back(new TalentDictEntry{"manaVamp", "*", BASE, {1.05f, 1.3f}});
	dictEntries.push_back(new TalentDictEntry{"shieldVamp", "*", BASE, {1.05f, 1.3f}});
	dictEntries.push_back(new TalentDictEntry{"physical", "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{"supernatural", "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{"fire", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"frost", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"lightning", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"psychic", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"sound", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"kinetic", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"acid", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"bleed", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"necrotic", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"holy", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"unhallow", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"restoration", "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{"absorption", "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{"oneHanded", "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{"twoHanded", "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{"axe", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"sword", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"mace", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"polearm", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"dagger", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"scythe", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"fist", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"staff", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"wand", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"card", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"bow", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"crossbow", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"thrown", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"shield", "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"relic", "-", MODIFIER, {2.0f, 2.5f}});

	for (auto* e : dictEntries)
	{
		entries.push_back(std::unique_ptr<TalentDictEntry>(e));
	}
}

