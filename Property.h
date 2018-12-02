#pragma once

#include "Trait.h"
#include <list>

class Property
{
public:
	virtual int DistanceBetweenProperties(Property& lhs, Property& rhs);

private:
	virtual int DistLhsAffect(Trait* trait, Property& lhs, Property& rhs);

private:
	std::list<TraitParent*> traits;
};

