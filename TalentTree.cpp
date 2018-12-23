// TalentTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PathGenerator.h"
#include "PropertyRepository.h"
#include "Property.h"
#include "TalentDictionaryLevel1.h"
#include "TalentDictionaryLevel2.h"
#include "TalentDictionaryLevel3.h"
#include "TalentDictionaryLevel4.h"
#include <iostream>

int main()
{
	PropertyRepository propertyRep;

	TalentDictionaryLevel1 talentDictionary1;
	TalentDictionaryLevel3 talentDictionary3;

	PathGenerator pathGenerator1(propertyRep.level1Properties, &talentDictionary1,
			propertyRep.level3Properties, &talentDictionary3);

	for (int i = 0; i < 30; i++)
	{
		std::cout << pathGenerator1.GenerateRandomTalent(true).toString() << std::endl;
	}

	std::cout << std::endl << std::endl;

	for (int i = 0; i < 30; i++)
	{
		for (auto& talent : pathGenerator1.GeneratePath(4, 1))
		{
			std::cout << talent.toString() << std::endl;
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << std::endl;

	TalentDictionaryLevel2 talentDictionary2;
	PathGenerator pathGenerator2(propertyRep.level2Properties, &talentDictionary2,
			propertyRep.level2Properties, &talentDictionary2);
	for (int i = 0; i < 30; i++)
	{
		for (auto& talent : pathGenerator2.GeneratePath(5, 0))
		{
			std::cout << talent.toString() << std::endl;
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << std::endl;

	TalentDictionaryLevel4 talentDictionary4;
	PathGenerator pathGenerator4(propertyRep.level4Properties, &talentDictionary4,
			propertyRep.level4Properties, &talentDictionary4);
	for (int i = 0; i < 30; i++)
	{
		for (auto& talent : pathGenerator4.GeneratePath(4, 0))
		{
			std::cout << talent.toString() << std::endl;
		}
		std::cout << std::endl;
	}

	system("pause");
	return 0;
}

