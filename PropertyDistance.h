#pragma once

#include "Property.h"
#include "Trait.h"

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

private:
	PropertyDistance() {}

	const Property* GetLesserProperty(const Property& lhs, const Property& rhs);

	int DistWeapon(const Trait* lhs, const Trait* rhs);

	std::string GetGeneralType(const Property& property);

	int DistAffectAffect(const Trait* lhs, const Trait* rhs);

	int DistAffectStats(const Trait* lhs, const Trait* rhs);

	int DistAffectResourceRelated(const Trait* lhs, const Trait* rhs);

	int DistAffectAlteration(const Trait* lhs, const Trait* rhs);

	int DistLhsAffect(const Property& lhs, const Property& rhs);

	int DistStatsStats(const Trait* lhs, const Trait* rhs);

	int DistStatsResourceRelated(const Trait* lhs, const Trait* rhs);

	int DistStatsAlteration(const Trait* lhs, const Trait* rhs);

	int DistLhsStats(const Property& lhs, const Property& rhs);

	int DistResourceRelatedResourceRelated(const Trait* lhs, const Trait* rhs);

	int DistResourceRelatedAlteration(const Trait* lhs, const Trait* rhs);

	int DistLhsResourceRelated(const Property& lhs, const Property& rhs);

	int DistAlterationAlteration(const Trait* lhs, const Trait* rhs);

	int DistLhsAlteration(const Property& lhs, const Property& rhs);

	int DistForDamageOrHealing(const Trait* lhs, const Trait* rhs);

	int DistForDamageType1(const Trait* lhs, const Trait* rhs);
};

