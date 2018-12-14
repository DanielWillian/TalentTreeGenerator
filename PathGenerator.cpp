#include "stdafx.h"
#include "PathGenerator.h"

std::unordered_set<Property*> PathGenerator::GetAllRelatedProperties(
		const Property* property,
		std::unordered_set<Property*> properties) const
{
	std::unordered_set<Property*> result;

	for (auto* otherProperty : properties)
	{
		if (Property::DistanceBetweenProperties(*property, *otherProperty) <= 5)
		{
			result.insert(otherProperty);
		}
	}

	return result;
}

