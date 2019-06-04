#include "stdafx.h"
#include "TalentDictionaryLevel9.h"
#include "Constants.h"

TalentDictionaryLevel9::TalentDictionaryLevel9()
{
	level = 9;
	std::vector<TalentDictEntry*> dictEntries;
	dictEntries.push_back(new TalentDictEntry{HEALTH, "*", BASE, {5.0f, 7.5f}});
	dictEntries.push_back(new TalentDictEntry{MANA, "*", BASE, {5.0f, 7.5f}});
	dictEntries.push_back(new TalentDictEntry{HEALTH_REGEN, "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{MANA_REGEN, "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{ATTACK_SPEED, "+", BASE, {0.1f, 0.15f}});
	dictEntries.push_back(new TalentDictEntry{CAST_SPEED, "*", BASE, {1.0f, 2.0f}});
	dictEntries.push_back(new TalentDictEntry{DODGE_CHANCE, "+", BASE, {5.0f, 7.5f}});
	dictEntries.push_back(new TalentDictEntry{RESISTANCE, "+", BASE, {5.0f, 7.5f}});
	dictEntries.push_back(new TalentDictEntry{HIT_CHANCE, "*", BASE, {1.05f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{CRITICAL_CHANCE, "+", BASE, {10.0f, 15.0f}});
	dictEntries.push_back(new TalentDictEntry{CRITICAL_AMP, "+", BASE, {30.0f, 40.0f}});
	dictEntries.push_back(new TalentDictEntry{SINGLE_TARGET_DAMAGE, "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{AREA_OF_EFFECT_SIZE, "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{AREA_OF_EFFECT_DAMAGE, "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{DIRECT_DAMAGE, "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{OVER_TIME_DAMAGE, "*", BASE, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{DURATION_OF_DOT, "+", BASE, {5.0f, 7.5f}});

	for (auto* e : dictEntries)
	{
		entries.push_back(std::unique_ptr<TalentDictEntry>(e));
	}
}

