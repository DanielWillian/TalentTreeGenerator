#include "Talent.h"

std::string Talent::toString() const
{
	std::string out = "{ ";
	for (auto it = talentEntries.begin(); it != talentEntries.end(); it++)
	{
		if (it != talentEntries.begin())
		{
			out += ", ";
		}
		out += it->toString();
	}
	out += " }";
	return out;
}

