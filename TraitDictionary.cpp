#include "stdafx.h"
#include "TraitDictionary.h"

TraitDictionary::TraitDictionary()
{
	entries.push_back({ "direct", TERMINAL, {} });
	entries.push_back({ "duration", TERMINAL, {} });
	entries.push_back({ "potency", TERMINAL, {} });
	entries.push_back({ "urgency", TERMINAL, {} });
	entries.push_back({ "alterationType", ALTERNATIVES, { "duration", "potency", "urgency" } });
	entries.push_back({ "affectType1", ALTERNATIVES, { "direct", "alterationType" } });

	entries.push_back({ "singleTarget", TERMINAL, {} });
	entries.push_back({ "radius", TERMINAL, {} });
	entries.push_back({ "power", TERMINAL, {} });
	entries.push_back({ "areaOfEffect", ALTERNATIVES, { "radius", "power" } });
	entries.push_back({ "affectType2", ALTERNATIVES, { "singleTarget", "areaOfEffect" } });
	entries.push_back({ "affectType", ALTERNATIVES, { "affectType1", "affectType2" } });

	entries.push_back({ "physical", TERMINAL, {} });
	entries.push_back({ "supernatural", TERMINAL, {} });
	entries.push_back({ "damageType1", ALTERNATIVES, { "physical", "supernatural" } });

	entries.push_back({ "fire", TERMINAL, {} });
	entries.push_back({ "frost", TERMINAL, {} });
	entries.push_back({ "lightning", TERMINAL, {} });
	entries.push_back({ "elemental", ALTERNATIVES, { "fire", "frost", "lightning" } });
	entries.push_back({ "psychic", TERMINAL, {} });
	entries.push_back({ "sound", TERMINAL, {} });
	entries.push_back({ "kinetic", TERMINAL, {} });
	entries.push_back({ "acid", TERMINAL, {} });
	entries.push_back({ "bleed", TERMINAL, {} });
	entries.push_back({ "necrotic", TERMINAL, {} });
	entries.push_back({ "holy", TERMINAL, {} });
	entries.push_back({ "unhallow", TERMINAL, {} });
	entries.push_back({ "damageType2", ALTERNATIVES,
			{ "elemental", "psychic", "sound", "kinetic", "acid", "bleed", "necrotic", "holy", "unhallow" } });
	entries.push_back({ "damageType", ALTERNATIVES, { "damageType1", "damageType2" } });

	entries.push_back({ "allDamage", TERMINAL, {} });
	entries.push_back({ "damage", ALTERNATIVES, { "allDamage", "damageType" } });

	entries.push_back({ "restoration", TERMINAL, {} });
	entries.push_back({ "absorption", TERMINAL, {} });
	entries.push_back({ "healingType", ALTERNATIVES, { "restoration", "absorption" } });
	entries.push_back({ "allHealing", TERMINAL, {} });
	entries.push_back({ "healing", ALTERNATIVES, { "allHealing", "healingType" } });

	entries.push_back({ "affect1", CONCATENATIONS, { "affectType", "damage" } });
	entries.push_back({ "affect2", CONCATENATIONS, { "affectType", "healing" } });
	entries.push_back({ "affect", ALTERNATIVES, { "affect1", "affect2" } });

	entries.push_back({ "property", ALTERNATIVES, { "affect" } });
}

