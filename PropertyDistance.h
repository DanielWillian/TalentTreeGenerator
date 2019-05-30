#pragma once

#include "Property.h"
#include "Trait.h"
#include <unordered_map>

class PropertyDistance
{
public:
	static PropertyDistance& GetInstance()
	{
		static PropertyDistance instance;
		return instance;
	}

	PropertyDistance(PropertyDistance const&) = delete;
	void operator=(PropertyDistance const&) = delete;

	int DistanceBetweenProperties(const Property& lhs, const Property& rhs);

public:
	std::unordered_map<std::string, std::unordered_map<std::string, int>> basePropertyDistances;

	std::unordered_map<std::string, std::unordered_map<std::string, int>> damageTypeDistances;

	std::unordered_map<std::string, std::unordered_map<std::string, int>> weaponTypeDistances;

private:
	PropertyDistance();

	int DistanceBetweenBaseProperties(const std::string& lhs, const std::string& rhs);
};

