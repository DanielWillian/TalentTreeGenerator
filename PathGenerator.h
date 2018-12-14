#pragma once

#include "Property.h"
#include <unordered_set>

class PathGenerator
{
public:
	PathGenerator(const std::unordered_set<Property*>& inLesserProperties,
			const std::unordered_set<Property*>& inGreaterProperties)
			: lesserProperties(inLesserProperties),
			greaterProperties(inGreaterProperties)
	{
	}

	std::unordered_set<Property*> GetAllRelatedProperties(const Property* property,
			std::unordered_set<Property*> properties) const;

public:
	std::unordered_set<Property*> lesserProperties;

	std::unordered_set<Property*> greaterProperties;
};

