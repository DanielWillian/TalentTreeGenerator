#pragma once

#include "Property.h"

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

	int DistWeapon(const Property& lhs, const Property& rhs);

	int DistLhsAffect(const Property& lhs, const Property& rhs);

	int DistLhsStats(const Property& lhs, const Property& rhs);

	int DistLhsResourceRelated(const Property& lhs, const Property& rhs);

	int DistLhsAlteration(const Property& lhs, const Property& rhs);

	int DistForDamageOrHealing(const Property& lhs, const Property& rhs);

	int DistForDamageType1(const Property& lhs, const Property& rhs);
};

