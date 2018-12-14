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

	static int DistanceBetweenProperties(const Property& lhs, const Property& rhs);

	bool operator==(const Property& other) const
	{
		return trait == other.trait;
	}

private:
	static const Property* GetLesserProperty(const Property& lhs, const Property& rhs);

	static int DistLhsAffect(const Property& lhs, const Property& rhs);

	static int DistLhsStats(const Property& lhs, const Property& rhs);

	static int DistLhsResourceRelated(const Property& lhs, const Property& rhs);

	static int DistLhsAlteration(const Property& lhs, const Property& rhs);

	static int DistForDamageOrHealing(const Property& lhs, const Property& rhs);

	static int DistForDamageType1(const Property& lhs, const Property& rhs);

public:
	TraitParent* trait;
};

