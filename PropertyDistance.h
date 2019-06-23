#pragma once

#include "Property.h"
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

	static const int NOT_SIMILAR;
	static const int SOMEWHAT_SIMILAR;
	static const int SIMILAR;

private:
	static const int NO_TYPE;
	static const int DAMAGE_TYPE1;
	static const int DAMAGE_TYPE2;
	static const int WEAPON_TYPE1;
	static const int WEAPON_TYPE2;

private:
	PropertyDistance();

	int DistanceBetweenBaseProperties(const std::string& lhs, const std::string& rhs);

	int DistanceBetweenDamageTypes(const std::string& lhs, const std::string& rhs);

	int GetTypeOfDamageType(const std::string& damageType);

	int DistanceBetweenWeaponTypes(const std::string& lhs, const std::string& rhs);

	int GetTypeOfWeaponType(const std::string& weaponType);
};

