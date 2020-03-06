#include "Constants.h"
#include <string>
#include <vector>

const std::string HEALTH = "Health";
const std::string MANA = "Mana";
const std::string HEALTH_REGEN = "HealthRegen";
const std::string MANA_REGEN = "ManaRegen";
const std::string ATTACK_SPEED = "AttackSpeed";
const std::string CAST_SPEED = "CastSpeed";
const std::string DODGE_CHANCE = "DodgeChance";
const std::string RESISTANCE = "Resistance";
const std::string HIT_CHANCE = "HitChance";
const std::string CRITICAL_CHANCE = "CriticalChance";
const std::string CRITICAL_AMP = "CriticalAmp";
const std::string SINGLE_TARGET_DAMAGE = "SingleTargetDamage";
const std::string AREA_OF_EFFECT_SIZE = "AreaOfEffectSize";
const std::string AREA_OF_EFFECT_DAMAGE = "AreaOfEffectDamage";
const std::string DIRECT_DAMAGE = "DirectDamage";
const std::string DAMAGE_OVER_TIME = "DamageOverTime";
const std::string DURATION_OF_DOT = "DurationOfDot";

const std::string NO_DAMAGE_TYPE = "NoDamageType";
const std::string PHYSICAL = "Physical";
const std::string MAGICAL = "Magical";
const std::string ACID = "Acid";
const std::string BLUDGEONING = "Bludgeoning";
const std::string COLD = "Cold";
const std::string FIRE = "Fire";
const std::string FORCE = "Force";
const std::string LIGHTNING = "Lightning";
const std::string NECROTIC = "Necrotic";
const std::string PIERCING = "Piercing";
const std::string POISON = "Poison";
const std::string PSYCHIC = "Psychic";
const std::string RADIANT = "Radiant";
const std::string SLASHING = "Slashing";
const std::string THUNDER = "Thunder";

const std::string NO_WEAPON_TYPE = "NoWeaponType";
const std::string ONE_HANDED = "OneHanded";
const std::string TWO_HANDED = "TwoHanded";
const std::string AXE = "Axe";
const std::string BOW = "Bow";
const std::string CROSSBOW = "Crossbow";
const std::string DAGGER = "Dagger";
const std::string FIST_WEAPON = "FistWeapon";
const std::string GUN = "Gun";
const std::string MACE = "Mace";
const std::string POLEARM = "Polearm";
const std::string STAFF = "Staff";
const std::string SWORD = "Sword";
const std::string THROWN = "Thrown";
const std::string WAND = "Wand";

namespace Constants
{
std::vector<std::string> getBaseProperties()
{
	std::vector<std::string> result = { HEALTH, MANA, HEALTH_REGEN, MANA_REGEN,
			ATTACK_SPEED, CAST_SPEED,
			DODGE_CHANCE, RESISTANCE,
			HIT_CHANCE, CRITICAL_CHANCE, CRITICAL_AMP,
			SINGLE_TARGET_DAMAGE, AREA_OF_EFFECT_SIZE, AREA_OF_EFFECT_DAMAGE,
			DIRECT_DAMAGE, DAMAGE_OVER_TIME, DURATION_OF_DOT };
	return std::move(result);
}
std::vector<std::string> getDamageTypes()
{
	std::vector<std::string> result = { NO_DAMAGE_TYPE, PHYSICAL, MAGICAL,
			ACID, BLUDGEONING, COLD, FIRE, FORCE, LIGHTNING,
			NECROTIC, PIERCING, POISON, PSYCHIC, RADIANT, SLASHING, THUNDER };
	return std::move(result);
}
std::vector<std::string> getWeaponTypes()
{
	std::vector<std::string> result = { NO_WEAPON_TYPE, ONE_HANDED, TWO_HANDED,
			AXE, BOW, CROSSBOW, DAGGER, FIST_WEAPON,
			GUN, MACE, POLEARM, STAFF, SWORD, THROWN, WAND };
	return std::move(result);
}
}

