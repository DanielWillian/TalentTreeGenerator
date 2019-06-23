#pragma once

#include "Property.h"

class TalentEntry
{
public:
	TalentEntry(Property* inProperty, const std::string& inModifier, const float inValue)
			: property(inProperty), modifier(inModifier), value(inValue)
	{
	}

	virtual std::string toString() const;

public:
	Property* property;
	std::string modifier;
	float value;
};

