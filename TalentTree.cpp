// TalentTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PathGenerator.h"
#include "PropertyRepository.h"
#include "Property.h"
#include "TalentDictionaryLevel1.h"
#include "TalentDictionaryLevel3.h"
#include <iostream>

int main()
{
	PropertyRepository propertyRep;

	Property property1 = *propertyRep.GetPropertiesWithIds({ "allDamage", "singleTarget" })[0];
	Property property2 = *propertyRep.GetPropertiesWithIds({ "allHealing", "singleTarget" })[0];
	std::cout << Property::DistanceBetweenProperties(property1, property2) << std::endl;

	TalentDictionaryLevel1 talentDictionary1;
	TalentDictionaryLevel3 talentDictionary3;

	PathGenerator pathGenerator(propertyRep.level1Properties, &talentDictionary1,
			propertyRep.level3Properties, &talentDictionary3);

	for (auto* property : pathGenerator.GetAllRelatedProperties(&property1, pathGenerator.lesserProperties))
	{
		std::cout << property->trait->toString() << std::endl;
	}

	for (int i = 0; i < 30; i++)
	{
		std::cout << pathGenerator.GenerateRandomTalent(true).toString() << std::endl;
	}

	std::cout << std::endl << std::endl;

	for (int i = 0; i < 30; i++)
	{
		for (auto& talent : pathGenerator.GeneratePath(4, 1))
		{
			std::cout << talent.toString() << std::endl;
		}
		std::cout << std::endl;
	}

	system("pause");
	return 0;
}

