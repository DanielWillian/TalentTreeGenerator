#include "stdafx.h"
#include "TalentDictionaryLevel4.h"
#include "Constants.h"

TalentDictionaryLevel4::TalentDictionaryLevel4()
{
	level = 4;
	std::vector<TalentDictEntry*> dictEntries;
	dictEntries.push_back(new TalentDictEntry{HEALTH, "*", BASE, {1.03f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{MANA, "*", BASE, {1.03f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{HEALTH_REGEN, "*", BASE, {1.03f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{MANA_REGEN, "*", BASE, {1.03f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{ATTACK_SPEED, "*", BASE, {1.05f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{CAST_SPEED, "*", BASE, {1.05f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{DODGE_CHANCE, "*", BASE, {1.03f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{RESISTANCE, "*", BASE, {1.03f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{HIT_CHANCE, "*", BASE, {1.03f, 1.05f}});
	dictEntries.push_back(new TalentDictEntry{CRITICAL_CHANCE, "*", BASE, {1.03f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{CRITICAL_AMP, "*", BASE, {1.03f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{SINGLE_TARGET_DAMAGE, "*", BASE, {1.1f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{AREA_OF_EFFECT_SIZE, "*", BASE, {1.1f, 1.25f}});
	dictEntries.push_back(new TalentDictEntry{AREA_OF_EFFECT_DAMAGE, "*", BASE, {1.1f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{DIRECT_DAMAGE, "*", BASE, {1.1f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{OVER_TIME_DAMAGE, "*", BASE, {1.1f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{DURATION_OF_DOT, "*", BASE, {1.1f, 1.3f}});

	dictEntries.push_back(new TalentDictEntry{NO_DAMAGE_TYPE, "-", MODIFIER, {1.0f, 1.0f}});
	dictEntries.push_back(new TalentDictEntry{NO_WEAPON_TYPE, "-", MODIFIER, {1.0f, 1.0f}});
	dictEntries.push_back(new TalentDictEntry{PHYSICAL, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{MAGICAL, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{ACID, "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{BLUDGENING, "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{COLD, "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{FIRE, "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{FORCE, "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{LIGHTNING, "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{NECROTIC, "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{PIERCING, "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{POISON, "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{PSYCHIC, "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{RADIANT, "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{SLASHING, "-", MODIFIER, {2.0f, 2.5f}});
	dictEntries.push_back(new TalentDictEntry{THUNDER, "-", MODIFIER, {2.0f, 2.5f}});

	for (auto* e : dictEntries)
	{
		entries.push_back(std::unique_ptr<TalentDictEntry>(e));
	}
}

