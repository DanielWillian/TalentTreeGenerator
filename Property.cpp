#include "stdafx.h"
#include "Property.h"

bool Property::operator==(const Property& other) const
{
	return index == other.index;
}

bool Property::operator<(const Property& other) const
{
	return index < other.index;
}

std::string Property::toString() const
{
	std::string out = "{ ";
	for (auto it = ids.begin(); it != ids.end(); it++)
	{
		if (it != ids.begin())
		{
			out += ", ";
		}
		out += *it;
	}
	out += " }";
	return out;
}

