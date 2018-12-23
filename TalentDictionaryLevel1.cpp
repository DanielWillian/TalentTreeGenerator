#include "stdafx.h"
#include "TalentDictionaryLevel1.h"

TalentDictionaryLevel1::TalentDictionaryLevel1()
{
	level = 1;
	std::vector<TalentDictEntry*> dictEntries;
	dictEntries.push_back(new TalentDictEntry{"direct", "*", BASE, {1.05f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"duration", "*", BASE, {1.05f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{"potency", "*", BASE, {1.05f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"urgency", "*", BASE, {1.05f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"singleTarget", "*", BASE, {1.05f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"radius", "*", BASE, {1.05f, 1.15f}});
	dictEntries.push_back(new TalentDictEntry{"power", "*", BASE, {1.05f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"attackSpeed", "*", BASE, {1.01f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{"castSpeed", "*", BASE, {1.01f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{"allCriticalChance", "*", BASE, {1.01f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{"allCriticalEffect", "*", BASE, {1.01f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"specCriticalChance", "*", BASE, {1.01f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{"specCriticalEffect", "*", BASE, {1.01f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"allHitChance", "*", BASE, {1.01f, 1.03f}});
	dictEntries.push_back(new TalentDictEntry{"allEvasionChance", "*", BASE, {1.01f, 1.15f}});
	dictEntries.push_back(new TalentDictEntry{"allDodgeChance", "*", BASE, {1.01f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{"allDodgeReduction", "*", BASE, {1.01f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{"allBlockChance", "*", BASE, {1.01f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{"allBlockReduction", "*", BASE, {1.01f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{"allArmour", "*", BASE, {1.01f, 1.03f}});
	dictEntries.push_back(new TalentDictEntry{"movementSpeed", "*", BASE, {1.01f, 1.03f}});
	dictEntries.push_back(new TalentDictEntry{"cooldown", "*", BASE, {1.01f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{"health", "*", BASE, {1.01f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{"mana", "*", BASE, {1.01f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{"shield", "*", BASE, {1.01f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{"healthRegen", "*", BASE, {1.01f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"manaRegen", "*", BASE, {1.01f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"shieldRegen", "*", BASE, {1.01f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"healthVamp", "*", BASE, {1.01f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"manaVamp", "*", BASE, {1.01f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{"shieldVamp", "*", BASE, {1.01f, 1.1f}});

	for (auto* e : dictEntries)
	{
		entries.push_back(std::unique_ptr<TalentDictEntry>(e));
	}
}

