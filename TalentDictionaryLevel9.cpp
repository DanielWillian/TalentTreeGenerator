#include "stdafx.h"
#include "TalentDictionaryLevel9.h"

TalentDictionaryLevel9::TalentDictionaryLevel9()
{
	level = 9;
	std::vector<TalentDictEntry*> dictEntries;
	dictEntries.push_back(new TalentDictEntry{"direct", "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"duration", "+", BASE, {5.0f, 7.5f}});
	dictEntries.push_back(new TalentDictEntry{"potency", "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"urgency", "+", BASE, {5.0f, 7.5f}});
	dictEntries.push_back(new TalentDictEntry{"singleTarget", "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"radius", "+", BASE, {10.0f, 15.0f}});
	dictEntries.push_back(new TalentDictEntry{"power", "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"attackSpeed", "+", BASE, {0.1f, 0.15f}});
	dictEntries.push_back(new TalentDictEntry{"castSpeed", "+", BASE, {1.0f, 2.0f}});
	dictEntries.push_back(new TalentDictEntry{"allCriticalChance", "+", BASE, {10.0f, 12.5f}});
	dictEntries.push_back(new TalentDictEntry{"allCriticalEffect", "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allHitChance", "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allEvasionChance", "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allDodgeChance", "+", BASE, {5.0f, 7.5f}});
	dictEntries.push_back(new TalentDictEntry{"allDodgeReduction", "+", BASE, {5.0f, 7.5f}});
	dictEntries.push_back(new TalentDictEntry{"allBlockChance", "+", BASE, {5.0f, 7.5f}});
	dictEntries.push_back(new TalentDictEntry{"allBlockReduction", "*", BASE, {5.0f, 7.5f}});
	dictEntries.push_back(new TalentDictEntry{"allArmour", "+", BASE, {5.0f, 7.5f}});
	dictEntries.push_back(new TalentDictEntry{"movementSpeed", "+", BASE, {10.0f, 15.0f}});
	dictEntries.push_back(new TalentDictEntry{"cooldown", "+", BASE, {5.0f, 7.5f}});
	dictEntries.push_back(new TalentDictEntry{"health", "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"mana", "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"shield", "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"healthRegen", "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"manaRegen", "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"shieldRegen", "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"healthVamp", "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"manaVamp", "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"shieldVamp", "*", BASE, {2.0f, 2.5f}});

	for (auto* e : dictEntries)
	{
		entries.push_back(std::unique_ptr<TalentDictEntry>(e));
	}
}

