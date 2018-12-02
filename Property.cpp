#include "stdafx.h"
#include "Property.h"
#include "TraitConstants.h"
#include <stdexcept>
#include <algorithm>

int Property::DistanceBetweenProperties(Property& lhs, Property& rhs)
{
	auto lhsIterator = lhs.traits.begin();
	auto rhsIterator = rhs.traits.begin();

	switch ((*lhsIterator)->id)
	{
		case TraitConstants::FIRST_LAYER_FIRST_TRAIT_AFFECT:
		{
			return DistLhsAffect(*lhsIterator, lhs, rhs);
			break;
		}
		case TraitConstants::FIRST_LAYER_FIRST_TRAIT_STATS:
		{
			break;
		}
		case TraitConstants::FIRST_LAYER_FIRST_TRAIT_RESOURCE_RELATED:
		{
			break;
		}
		case TraitConstants::FIRST_LAYER_FIRST_TRAIT_ALTERATION:
		{
			break;
		}
		default:
			throw std::invalid_argument("Property not supported");
			break;
	}

	return 0;
}

int Property::DistLhsAffect(Trait* trait, Property& lhs, Property& rhs)
{
	std::vector<Trait*> lhsTraitChildren = trait->GetChildren();
	Trait* lhsAffectType = lhsTraitChildren[0];
	Trait* lhsAffectTypeChild = lhsAffectType->GetChildren().front();
	std::vector<int> lhsAffectTypeIds = lhsAffectType->GetAllTraitIds();

	Trait* lhsSecondTrait = lhsTraitChildren[1];
	std::vector<int> lhsSecondTraitIds = lhsSecondTrait->GetAllTraitIds();

	Trait* rhsFirstTrait = rhs.traits.front();
	switch (rhsFirstTrait->id)
	{
		case TraitConstants::FIRST_LAYER_FIRST_TRAIT_AFFECT:
		{
			std::vector<Trait*> rhsTraitChildren = rhsFirstTrait->GetChildren();
			Trait* rhsAffectType = rhsTraitChildren[0];
			Trait* rhsAffectTypeChild = rhsAffectType->GetChildren().front();
			std::vector<int> rhsAffectTypeIds = rhsAffectType->GetAllTraitIds();

			Trait* rhsSecondTrait = rhsTraitChildren[1];
			std::vector<int> rhsSecondTraitIds = rhsSecondTrait->GetAllTraitIds();

			auto pairResult = std::mismatch(lhsSecondTraitIds.begin(), lhsSecondTraitIds.end(), rhsSecondTraitIds.begin());
			if (pairResult.first != lhsSecondTraitIds.end() && pairResult.second != rhsSecondTraitIds.end())
			{
				return 20;
			}

			auto it = std::find(lhsAffectTypeIds.begin(), lhsAffectTypeIds.end(), rhsAffectTypeChild->id);
			if (it != lhsAffectTypeIds.end())
			{
				Trait* rhsAffectTypeChildSpecifier = rhsAffectTypeChild->GetChildren().front();
				it = std::find(lhsAffectTypeIds.begin(), lhsAffectTypeIds.end(), rhsAffectTypeChildSpecifier->id);
				if (it ==lhsAffectTypeIds.end())
				{
					return 20;
				}
			}

			return 1;
		}
		case TraitConstants::FIRST_LAYER_FIRST_TRAIT_STATS:
		{
			break;
		}
		case TraitConstants::FIRST_LAYER_FIRST_TRAIT_RESOURCE_RELATED:
		{
			break;
		}
		case TraitConstants::FIRST_LAYER_FIRST_TRAIT_ALTERATION:
		{
			break;
		}
		default:
			throw std::invalid_argument("Property not supported");
			break;
	}

	return 0;
}

