#pragma once

#include "Trait.h"

class Property
{
public:
	Property(TraitParent* inTrait)
	{
		trait = inTrait;
	}

	bool operator==(const Property& other) const
	{
		return trait == other.trait;
	}

public:
	TraitParent* trait;
};

