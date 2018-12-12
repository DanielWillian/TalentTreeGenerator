#pragma once

#include "Trait.h"
#include <vector>

class Property
{
public:
	Property(TraitParent* inTrait)
	{
		trait = inTrait;
	}

	static int DistanceBetweenProperties(Property& lhs, Property& rhs);

	bool operator==(const Property& other) const
	{
		return trait == other.trait;
	}

private:
	static Property* GetLesserProperty(Property& lhs, Property& rhs);

	static int DistLhsAffect(Property& lhs, Property& rhs);

	static int DistLhsStats(Property& lhs, Property& rhs);

	static int DistLhsResourceRelated(Property& lhs, Property& rhs);

	static int DistLhsAlteration(Property& lhs, Property& rhs);

	static int DistForDamageOrHealing(const Property& lhs, const Property& rhs);

	static int DistForDamageType1(const Property& lhs, const Property& rhs);

private:
	TraitParent* trait;
};

