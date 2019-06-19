#include "stdafx.h"
#include "TalentDictionaryLevel3.h"
#include "Constants.h"

TalentDictionaryLevel3::TalentDictionaryLevel3()
{
	level = 3;
	std::vector<TalentDictEntry*> dictEntries;
	dictEntries.push_back(new TalentDictEntry{HEALTH, "*", BASE, {1.03f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{MANA, "*", BASE, {1.03f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{HEALTH_REGEN, "*", BASE, {1.04f, 1.15f}});
	dictEntries.push_back(new TalentDictEntry{MANA_REGEN, "*", BASE, {1.04f, 1.15f}});
	dictEntries.push_back(new TalentDictEntry{ATTACK_SPEED, "*", BASE, {1.05f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{CAST_SPEED, "*", BASE, {1.05f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{DODGE_CHANCE, "*", BASE, {1.03f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{RESISTANCE, "*", BASE, {1.03f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{HIT_CHANCE, "*", BASE, {1.03f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{CRITICAL_CHANCE, "*", BASE, {1.03f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{CRITICAL_AMP, "*", BASE, {1.04f, 1.15f}});
	dictEntries.push_back(new TalentDictEntry{SINGLE_TARGET_DAMAGE, "*", BASE, {1.1f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{AREA_OF_EFFECT_SIZE, "*", BASE, {1.1f, 1.25f}});
	dictEntries.push_back(new TalentDictEntry{AREA_OF_EFFECT_DAMAGE, "*", BASE, {1.1f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{DIRECT_DAMAGE, "*", BASE, {1.1f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{OVER_TIME_DAMAGE, "*", BASE, {1.1f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{DURATION_OF_DOT, "*", BASE, {1.05f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{NO_DAMAGE_TYPE, "-", MODIFIER, {1.0f, 1.0f}});
	dictEntries.push_back(new TalentDictEntry{NO_WEAPON_TYPE, "-", MODIFIER, {1.0f, 1.0f}});

	for (auto* e : dictEntries)
	{
		entries.push_back(std::unique_ptr<TalentDictEntry>(e));
	}
}

