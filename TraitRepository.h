#pragma once

#include "Trait.h"
#include "TraitConstants.h"

class TraitRepository
{
public:
	TraitRepository();

	TraitChild direct;
	TraitChild damage;
	TraitChild healing;

	TraitParent directAffectType1;
	TraitParent directAffectType;

	TraitParent damageDamage;

	TraitParent healingHealing;

	TraitParent directDamageAffect;

	TraitParent directHealingAffect;
};

