#include "stdafx.h"
#include "Property.h"
#include "TraitConstants.h"
#include <stdexcept>
#include <algorithm>

int Property::DistanceBetweenProperties(Property& lhs, Property& rhs)
{
	Trait* lhsMasterNode = lhs.traits.front();
	auto lhsMasterNodeChild = lhsMasterNode->GetChildren().front();

	switch (lhsMasterNodeChild->id)
	{
		case TraitConstants::FIRST_LAYER_FIRST_TRAIT_AFFECT:
		{
			return DistLhsAffect(lhsMasterNodeChild, lhs, rhs);
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

	Trait* rhsMasterNode = rhs.traits.front();
	auto rhsMasterNodeChild = rhsMasterNode->GetChildren().front();
	switch (rhsMasterNodeChild->id)
	{
		case TraitConstants::FIRST_LAYER_FIRST_TRAIT_AFFECT:
		{
			std::vector<Trait*> rhsTraitChildren = rhsMasterNodeChild->GetChildren();
			Trait* rhsAffectType = rhsTraitChildren[0];
			Trait* rhsAffectTypeChild = rhsAffectType->GetChildren().front();
			std::vector<int> rhsAffectTypeIds = rhsAffectType->GetAllTraitIds();

			Trait* rhsSecondTrait = rhsTraitChildren[1];
			std::vector<int> rhsSecondTraitIds = rhsSecondTrait->GetAllTraitIds();

			// Damage to Healing
			if (lhsSecondTraitIds[0] != rhsSecondTraitIds[0])
			{
				return 20;
			}
			// If both are specifying which type of damage or healing it is
			else if (lhsSecondTraitIds.size() > 2 && rhsSecondTraitIds.size() > 2)
			{
				if (lhsSecondTraitIds.size() > rhsSecondTraitIds.size())
				{
					auto pairResult = std::mismatch(rhsSecondTraitIds.begin() + 2, rhsSecondTraitIds.end(),
							lhsSecondTraitIds.begin() + 2);
					if (pairResult.first != rhsSecondTraitIds.end() && pairResult.second != lhsSecondTraitIds.end())
					{
						return 20;
					}
				}
				else
				{
					auto pairResult = std::mismatch(lhsSecondTraitIds.begin() + 2, lhsSecondTraitIds.end(),
							rhsSecondTraitIds.begin() + 2);
					if (pairResult.first != lhsSecondTraitIds.end() && pairResult.second != rhsSecondTraitIds.end())
					{
						return 20;
					}
				}
			}

			auto it = std::find(lhsAffectTypeIds.begin(), lhsAffectTypeIds.end(), rhsAffectTypeChild->id);
			if (it != lhsAffectTypeIds.end())
			{
				Trait* rhsAffectTypeChildSpecifier = rhsAffectTypeChild->GetChildren().front();
				it = std::find(lhsAffectTypeIds.begin(), lhsAffectTypeIds.end(), rhsAffectTypeChildSpecifier->id);
				if (it == lhsAffectTypeIds.end())
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

