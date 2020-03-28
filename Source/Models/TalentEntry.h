#pragma once

#include "Property.h"

class TalentEntry
{
public:
	TalentEntry(Property* inProperty, const std::string& inModifier, const float inValue)
			: property(inProperty), modifier(inModifier), value(inValue)
	{
	}

	std::string toString() const;

public:
	Property* property;
	std::string modifier;
	float value;
};

