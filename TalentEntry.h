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
		std::string out = "( { ";
		for (auto& id : property->ids)
		{
			out += id + ", ";
		}
		out += "}, " + modifier;
		out += ", " + std::to_string(value);
		out += " )";
		return out;
	}

public:
	Property* property;
	std::string modifier;
	float value;
};

