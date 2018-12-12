// TalentTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PropertyRepository.h"
#include "Property.h"
#include <iostream>

int main()
{
	PropertyRepository propertyRep;
	std::vector<Property*> propertyList = propertyRep.allProperties;

	for (size_t i = 0; i < propertyList.size(); i++)
	{
		std::cout << i << " " << propertyList[i]->trait->toString() << std::endl;
	}

	Property property1 = *propertyRep.GetPropertiesWithIds({ "allDamage", "singleTarget" })[0];
	Property property2 = *propertyRep.GetPropertiesWithIds({ "allHealing", "singleTarget" })[0];
	std::cout << Property::DistanceBetweenProperties(property1, property2) << std::endl;

	system("pause");
	return 0;
}

