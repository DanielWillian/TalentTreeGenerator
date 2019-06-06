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

	virtual std::string toString() const
	{
		std::string out = "{ ";
		for (auto& id : ids)
		{
			out += id + ", ";
		}
		out += "}";
		return out;
	}

public:
	int index;
	std::vector<std::string> ids;
};

