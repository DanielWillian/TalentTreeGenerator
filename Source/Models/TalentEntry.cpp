#include "stdafx.h"
#include "TalentEntry.h"

std::string TalentEntry::toString() const
{
	std::string out = "( ";
	out += property->toString();
	out += ", " + modifier;
	const std::string valueString = std::to_string(value);
	out += ", " + valueString.substr(0, valueString.find(".") + 3);
	out += " )";
	return out;
}

