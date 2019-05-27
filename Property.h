#pragma once

#include <string>
#include <vector>

class Property
{
public:
	Property() {}

	Property(const int inIndex, const std::vector<std::string>& inIds)
	{
		index = inIndex;
		ids = inIds;
	}

	bool operator==(const Property& other) const
	{
		return index == other.index;
	}

	bool operator<(const Property& other) const
	{
		return index < other.index;
	}

public:
	int index;
	std::vector<std::string> ids;
};

