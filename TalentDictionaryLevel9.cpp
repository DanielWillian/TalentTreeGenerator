#include "stdafx.h"
#include "TalentDictionaryLevel9.h"

TalentDictionaryLevel9::TalentDictionaryLevel9()
{
	level = 9;
	std::vector<TalentDictEntry*> dictEntries;
	dictEntries.push_back(new TalentDictEntry{"direct", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"duration", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"potency", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"urgency", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"singleTarget", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"radius", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"power", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"attackSpeed", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"castSpeed", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allCriticalChance", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"specCriticalChance", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allCriticalEffect", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"specCriticalEffect", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allHitChance", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allEvasionChance", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allDodgeChance", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allDodgeReduction", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allBlockChance", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allBlockReduction", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allArmour", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"movementSpeed", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"cooldown", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"health", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"mana", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"shield", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"healthRegen", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"manaRegen", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"shieldRegen", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"healthVamp", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"manaVamp", "*", BENEFICIAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"shieldVamp", "*", BENEFICIAL, {2.0f, 2.5f}});

	dictEntries.push_back(new TalentDictEntry{"direct", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"duration", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"potency", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"urgency", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"singleTarget", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"radius", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"power", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"attackSpeed", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"castSpeed", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allCriticalChance", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allCriticalEffect", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allHitChance", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allEvasionChance", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allDodgeChance", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allDodgeReduction", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allBlockChance", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allBlockReduction", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"allArmour", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"movementSpeed", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"cooldown", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"health", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"mana", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"shield", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"healthRegen", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"manaRegen", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"shieldRegen", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"healthVamp", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"manaVamp", "/", DETRIMENTAL, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{"shieldVamp", "/", DETRIMENTAL, {2.0f, 2.5f}});

	for (auto* e : dictEntries)
	{
		entries.push_back(std::unique_ptr<TalentDictEntry>(e));
	}
}

