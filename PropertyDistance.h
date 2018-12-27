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

	std::unordered_map<int, std::unordered_map<int, int>> GeneratePropertyDistances(const std::vector<Property*>& properties);

	int DistanceBetweenProperties(const Property& lhs, const Property& rhs);

private:
	std::unordered_map<int, std::unordered_map<int, int>> weaponDistances;

	std::unordered_map<int, std::unordered_map<int, int>> affectDistances;

	std::unordered_map<int, std::unordered_map<int, int>> statsDistances;

	std::unordered_map<int, std::unordered_map<int, int>> resourceRelatedDistances;

	std::unordered_map<int, std::unordered_map<int, int>> alterationDistances;

private:
	PropertyDistance();

	const Property* GetLesserProperty(const Property& lhs, const Property& rhs) const;

	int DistLhsAffect(const Trait* lhs, const Property& rhs);

	int DistLhsStats(const Trait* lhs, const Property& rhs);

	int DistLhsResourceRelated(const Trait* lhs, const Property& rhs);

	int DistLhsAlteration(const Trait* lhs, const Property& rhs);

	int DistWeapon(const Trait* lhs, const Trait* rhs);

	int DistAffectAffect(const Trait* lhs, const Trait* rhs);

	int DistAffectStats(const Trait* lhs, const Trait* rhs);

	int DistAffectResourceRelated(const Trait* lhs, const Trait* rhs);

	int DistAffectAlteration(const Trait* lhs, const Trait* rhs);

	int DistStatsStats(const Trait* lhs, const Trait* rhs);

	int DistStatsResourceRelated(const Trait* lhs, const Trait* rhs);

	int DistStatsAlteration(const Trait* lhs, const Trait* rhs);

	int DistResourceRelatedResourceRelated(const Trait* lhs, const Trait* rhs);

	int DistResourceRelatedAlteration(const Trait* lhs, const Trait* rhs);

	int DistAlterationAlteration(const Trait* lhs, const Trait* rhs);

	int DistForDamageOrHealing(const Trait* lhs, const Trait* rhs);

	int DistForDamageType1(const Trait* lhs, const Trait* rhs);
};

