#include "stdafx.h"
#include "TalentDictionary.h"

TalentDictionary::TalentDictionary()
{
	level = 1;
	entries.push_back({"direct", "*", BASE, {1.05f, 1.1f}});
	entries.push_back({"duration", "*", BASE, {1.05f, 1.2f}});
	entries.push_back({"potency", "*", BASE, {1.05f, 1.1f}});
	entries.push_back({"urgency", "*", BASE, {1.05f, 1.1f}});
	entries.push_back({"singleTarget", "*", BASE, {1.05f, 1.1f}});
	entries.push_back({"radius", "*", BASE, {1.05f, 1.15f}});
	entries.push_back({"power", "*", BASE, {1.05f, 1.1f}});
	entries.push_back({"attackSpeed", "*", BASE, {0.95f, 0.99f}});
	entries.push_back({"castSpeed", "*", BASE, {0.95f, 0.99f}});
	entries.push_back({"allCriticalChance", "*", BASE, {1.01f, 1.05f}});
	entries.push_back({"allCriticalEffect", "*", BASE, {1.01f, 1.1f}});
	entries.push_back({"specCriticalChance", "*", BASE, {1.01f, 1.05f}});
	entries.push_back({"specCriticalEffect", "*", BASE, {1.01f, 1.1f}});
	entries.push_back({"allHitChance", "*", BASE, {1.01f, 1.03f}});
	entries.push_back({"allEvasionChance", "*", BASE, {1.01f, 1.15f}});
	entries.push_back({"allDodgeChance", "*", BASE, {1.01f, 1.05f}});
	entries.push_back({"allDodgeReduction", "*", BASE, {1.01f, 1.05f}});
	entries.push_back({"allBlockChance", "*", BASE, {1.01f, 1.05f}});
	entries.push_back({"allBlockReduction", "*", BASE, {1.01f, 1.05f}});
	entries.push_back({"allArmour", "*", BASE, {1.01f, 1.03f}});
	entries.push_back({"movementSpeed", "*", BASE, {1.01f, 1.03f}});
	entries.push_back({"movementSpeed", "*", BASE, {1.01f, 1.03f}});
	entries.push_back({"cooldown", "*", BASE, {0.95f, 0.99f}});
	entries.push_back({"health", "*", BASE, {1.01f, 1.05f}});
	entries.push_back({"mana", "*", BASE, {1.01f, 1.05f}});
	entries.push_back({"shield", "*", BASE, {1.01f, 1.05f}});
	entries.push_back({"healthRegen", "*", BASE, {1.01f, 1.1f}});
	entries.push_back({"manaRegen", "*", BASE, {1.01f, 1.1f}});
	entries.push_back({"shieldRegen", "*", BASE, {1.01f, 1.1f}});
	entries.push_back({"healthVamp", "*", BASE, {1.01f, 1.1f}});
	entries.push_back({"manaVamp", "*", BASE, {1.01f, 1.1f}});
	entries.push_back({"shieldVamp", "*", BASE, {1.01f, 1.1f}});
}

std::vector<TalentDictEntry> TalentDictionary::GetDictEntries(const std::string& key) const
{
	std::vector<TalentDictEntry> result;
	for (const auto& entry : entries)
	{
		if (entry.key == key)
		{
			result.push_back(entry);
		}
	}
	return result;
}

std::vector<TalentDictEntry> TalentDictionary::GetModifierEntries() const
{
	std::vector<TalentDictEntry> result;
	for (const auto& entry : entries)
	{
		if (entry.type == MODIFIER)
		{
			result.push_back(entry);
		}
	}
	return result;
}

