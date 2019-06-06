#pragma once

#include "Property.h"

class TalentEntry
{
public:
	TalentEntry(Property* inProperty, const std::string& inModifier, const float inValue)
			: property(inProperty), modifier(inModifier), value(inValue)
	{
	}

	virtual std::string toString() const
	{
		std::string out = "( ";
		out += property->toString();
		out += ", " + modifier;
		out += ", " + std::to_string(value);
		out += " )";
		return out;
	}

public:
	Property* property;
	std::string modifier;
	float value;
};

