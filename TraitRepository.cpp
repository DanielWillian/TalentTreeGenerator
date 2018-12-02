#include "stdafx.h"
#include "TraitRepository.h"
#include "TraitConstants.h"

TraitRepository::TraitRepository()
{
	direct = TraitChild(TraitConstants::FOURTH_LAYER_FIRST_TRAIT_DIRECT);
	damage = TraitChild(TraitConstants::THIRD_LAYER_FIRST_TRAIT_DAMAGE);
	healing = TraitChild(TraitConstants::THIRD_LAYER_FIRST_TRAIT_HEALING);

	directAffectType1 = TraitParent(TraitConstants::THIRD_LAYER_FIRST_TRAIT_AFFECT_TYPE1,
			std::vector<Trait*>({ &direct }));
	directAffectType = TraitParent(TraitConstants::SECOND_LAYER_FIRST_TRAIT_AFFECT_TYPE,
			std::vector<Trait*>({ &directAffectType1 }));

	damageDamage = TraitParent(TraitConstants::SECOND_LAYER_SECOND_TRAIT_DAMAGE,
			std::vector<Trait*>({ &damage }));

	healingHealing = TraitParent(TraitConstants::SECOND_LAYER_SECOND_TRAIT_HEALING,
			std::vector<Trait*>({ &healing }));

	directDamageAffect = TraitParent(TraitConstants::FIRST_LAYER_FIRST_TRAIT_AFFECT,
			std::vector<Trait*>({ &directAffectType, &damageDamage }));

	directHealingAffect = TraitParent(TraitConstants::FIRST_LAYER_FIRST_TRAIT_AFFECT,
			std::vector<Trait*>({ &directAffectType, &healingHealing }));
}

