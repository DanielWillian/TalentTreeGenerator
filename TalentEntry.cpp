#include "stdafx.h"
#include "TalentEntry.h"

std::string TalentEntry::toString() const
{
	std::string out = "( ";
	out += property->toString();
	out += ", " + modifier;
	out += ", " + std::to_string(value);
	out += " )";
	return out;
}

