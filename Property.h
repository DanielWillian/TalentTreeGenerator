#pragma once

#include "Trait.h"
#include <vector>

class Property
{
public:
	Property(const std::vector<TraitParent*>& inTraits)
	{
		traits = inTraits;
	}

	static int DistanceBetweenProperties(Property& lhs, Property& rhs);

private:
	static int DistLhsAffect(Trait* trait, Property& lhs, Property& rhs);

private:
	std::vector<TraitParent*> traits;
};

