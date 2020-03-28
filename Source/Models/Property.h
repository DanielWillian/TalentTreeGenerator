#pragma once

#include <string>
#include <vector>

class Property
{
public:
	Property() {}

	Property(const int inIndex, const std::vector<std::string>& inIds)
			: index(inIndex), ids(inIds)
	{
	}

	bool operator==(const Property& other) const;

	bool operator<(const Property& other) const;

	std::string toString() const;

public:
	int index;
	std::vector<std::string> ids;
};

