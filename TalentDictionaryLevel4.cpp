#include "stdafx.h"
#include "TalentDictionaryLevel4.h"

TalentDictionaryLevel4::TalentDictionaryLevel4()
{
	level = 4;
	std::vector<TalentDictEntry*> dictEntries;
	dictEntries.push_back(new TalentDictEntry{"direct", "*", BASE, {1.1f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"duration", "*", BASE, {1.1f, 1.3f}});
	dictEntries.push_back(new TalentDictEntry{"potency", "*", BASE, {1.1f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"urgency", "*", BASE, {1.1f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"singleTarget", "*", BASE, {1.1f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"radius", "*", BASE, {1.1f, 1.25f}});
	dictEntries.push_back(new TalentDictEntry{"power", "*", BASE, {1.1f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"attackSpeed", "*", BASE, {1.05f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"castSpeed", "*", BASE, {1.05f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"allCriticalChance", "*", BASE, {1.03f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"allCriticalEffect", "*", BASE, {1.03f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"specCriticalChance", "*", BASE, {1.03f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"specCriticalEffect", "*", BASE, {1.03f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"allHitChance", "*", BASE, {1.03f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{"specHitChance", "*", BASE, {1.03f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{"allEvasionChance", "*", BASE, {1.03f, 1.25f}});
	dictEntries.push_back(new TalentDictEntry{"specEvasionChance", "*", BASE, {1.03f, 1.25f}});
	dictEntries.push_back(new TalentDictEntry{"allDodgeChance", "*", BASE, {1.03f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"specDodgeChance", "*", BASE, {1.03f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"allDodgeReduction", "*", BASE, {1.03f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"specDodgeReduction", "*", BASE, {1.03f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"allBlockChance", "*", BASE, {1.03f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"specBlockChance", "*", BASE, {1.03f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"allBlockReduction", "*", BASE, {1.03f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"specBlockReduction", "*", BASE, {1.03f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"allArmour", "*", BASE, {1.03f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{"specArmour", "*", BASE, {1.03f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{"movementSpeed", "*", BASE, {1.03f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{"cooldown", "*", BASE, {1.05f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"health", "*", BASE, {1.03f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"mana", "*", BASE, {1.03f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"shield", "*", BASE, {1.03f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"healthRegen", "*", BASE, {1.03f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"manaRegen", "*", BASE, {1.03f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"shieldRegen", "*", BASE, {1.03f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"healthVamp", "*", BASE, {1.03f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"manaVamp", "*", BASE, {1.03f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"shieldVamp", "*", BASE, {1.03f, 1.2f}});
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

	for (auto* e : dictEntries)
	{
		entries.push_back(std::unique_ptr<TalentDictEntry>(e));
	}
}

