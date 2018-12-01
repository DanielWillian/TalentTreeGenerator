#pragma once

#include "Trait.h"
#include <list>

class Property
{
public:
	virtual int DistanceBetweenProperties(const Property& lhs, const Property& rhs);

private:
	std::list<TraitParent*> traits;
};

