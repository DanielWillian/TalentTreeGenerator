#include "stdafx.h"
#include "TalentDictionaryLevel8.h"
#include "Constants.h"

TalentDictionaryLevel8::TalentDictionaryLevel8()
{
	level = 8;
	std::vector<TalentDictEntry*> dictEntries;
	dictEntries.push_back(new TalentDictEntry{HEALTH, "*", BASE, {1.08f, 1.15f}});
	dictEntries.push_back(new TalentDictEntry{MANA, "*", BASE, {1.08f, 1.15f}});
	dictEntries.push_back(new TalentDictEntry{HEALTH_REGEN, "*", BASE, {1.09f, 1.24f}});
	dictEntries.push_back(new TalentDictEntry{MANA_REGEN, "*", BASE, {1.09f, 1.24f}});
	dictEntries.push_back(new TalentDictEntry{ATTACK_SPEED, "*", BASE, {1.1f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{CAST_SPEED, "*", BASE, {1.1f, 1.2f}});
	dictEntries.push_back(new TalentDictEntry{DODGE_CHANCE, "*", BASE, {1.06f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{RESISTANCE, "*", BASE, {1.06f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{HIT_CHANCE, "*", BASE, {1.06f, 1.1f}});
	dictEntries.push_back(new TalentDictEntry{CRITICAL_CHANCE, "*", BASE, {1.07f, 1.18f}});
	dictEntries.push_back(new TalentDictEntry{CRITICAL_AMP, "*", BASE, {1.07f, 1.18f}});
	dictEntries.push_back(new TalentDictEntry{SINGLE_TARGET_DAMAGE, "*", BASE, {1.15f, 1.3f}});
	dictEntries.push_back(new TalentDictEntry{AREA_OF_EFFECT_SIZE, "*", BASE, {1.15f, 1.33f}});
	dictEntries.push_back(new TalentDictEntry{AREA_OF_EFFECT_DAMAGE, "*", BASE, {1.15f, 1.3f}});
	dictEntries.push_back(new TalentDictEntry{DIRECT_DAMAGE, "*", BASE, {1.15f, 1.3f}});
	dictEntries.push_back(new TalentDictEntry{OVER_TIME_DAMAGE, "*", BASE, {1.15f, 1.3f}});
	dictEntries.push_back(new TalentDictEntry{DURATION_OF_DOT, "*", BASE, {1.1f, 1.24f}});

	dictEntries.push_back(new TalentDictEntry{NO_DAMAGE_TYPE, "-", MODIFIER, {1.0f, 1.0f}});
	dictEntries.push_back(new TalentDictEntry{NO_WEAPON_TYPE, "-", MODIFIER, {1.0f, 1.0f}});
	dictEntries.push_back(new TalentDictEntry{PHYSICAL, "-", MODIFIER, {1.25f, 1.5f}});
	dictEntries.push_back(new TalentDictEntry{MAGICAL, "-", MODIFIER, {1.25f, 1.5f}});
	dictEntries.push_back(new TalentDictEntry{ACID, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{BLUDGENING, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{COLD, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{FIRE, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{FORCE, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{LIGHTNING, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{NECROTIC, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{PIERCING, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{POISON, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{PSYCHIC, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{RADIANT, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{SLASHING, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{THUNDER, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{ONE_HANDED, "-", MODIFIER, {1.25f, 1.5f}});
	dictEntries.push_back(new TalentDictEntry{TWO_HANDED, "-", MODIFIER, {1.25f, 1.5f}});
	dictEntries.push_back(new TalentDictEntry{AXE, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{BOW, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{CROSSBOW, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{DAGGER, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{FIST_WEAPON, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{GUN, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{MACE, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{POLEARM, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{STAFF, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{SWORD, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{THROWN, "-", MODIFIER, {1.5f, 1.75f}});
	dictEntries.push_back(new TalentDictEntry{WAND, "-", MODIFIER, {1.5f, 1.75f}});

	for (auto* e : dictEntries)
	{
		entries.push_back(std::unique_ptr<TalentDictEntry>(e));
	}
}

