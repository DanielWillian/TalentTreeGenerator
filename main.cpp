// TalentTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PathGenerator.h"
#include "PathGeneratorLevel9.h"
#include "PropertyDistance.h"
#include "PropertyRepository.h"
#include "Property.h"
#include "TalentDictionaryLevel1.h"
#include "TalentDictionaryLevel2.h"
#include "TalentDictionaryLevel3.h"
#include "TalentDictionaryLevel4.h"
#include "TalentDictionaryLevel5.h"
#include "TalentDictionaryLevel6.h"
#include "TalentDictionaryLevel7.h"
#include "TalentDictionaryLevel8.h"
#include "TalentDictionaryLevel9.h"
#include "TalentTree.h"
#include "TalentTreeGenerator.h"
#include "TalentTreeStructure.h"
#include <iostream>

int main()
{
	const PropertyRepository& propertyRep = PropertyRepository::GetInstance();

	const PropertyDistance& propertyDist = PropertyDistance::GetInstance();

	for (auto& innerMap : propertyDist.basePropertyDistances)
	{
		std::cout << innerMap.first << std::endl;
		for (auto& dists : innerMap.second)
		{
			std::cout << dists.first << ": " << dists.second << ", ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	for (auto& innerMap : propertyDist.damageTypeDistances)
	{
		std::cout << innerMap.first << std::endl;
		for (auto& dists : innerMap.second)
		{
			std::cout << dists.first << ": " << dists.second << ", ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	for (auto& innerMap : propertyDist.weaponTypeDistances)
	{
		std::cout << innerMap.first << std::endl;
		for (auto& dists : innerMap.second)
		{
			std::cout << dists.first << ": " << dists.second << ", ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	TalentDictionaryLevel1 talentDictionary1;
	TalentDictionaryLevel3 talentDictionary3;
	PathGenerator pathGenerator1(propertyRep.level1Properties, &talentDictionary1,
			propertyRep.level3Properties, &talentDictionary3);

	TalentDictionaryLevel2 talentDictionary2;
	PathGenerator pathGenerator2(propertyRep.level2Properties, &talentDictionary2,
			propertyRep.level2Properties, &talentDictionary2);

	TalentDictionaryLevel4 talentDictionary4;
	TalentDictionaryLevel6 talentDictionary6;
	PathGenerator pathGenerator4(propertyRep.level4Properties, &talentDictionary4,
			propertyRep.level6Properties, &talentDictionary6);

	TalentDictionaryLevel5 talentDictionary5;
	PathGenerator pathGenerator5(propertyRep.level5Properties, &talentDictionary5,
			propertyRep.level5Properties, &talentDictionary5);

	TalentDictionaryLevel7 talentDictionary7;
	TalentDictionaryLevel8 talentDictionary8;
	PathGenerator pathGenerator7(propertyRep.level7Properties, &talentDictionary7,
			propertyRep.level8Properties, &talentDictionary8);

	TalentDictionaryLevel9 talentDictionary9;
	PathGenerator pathGenerator9(propertyRep.level9Properties, &talentDictionary9,
			propertyRep.level9Properties, &talentDictionary9);

	std::vector<PathGenerator*> pathGenerators = {&pathGenerator1, &pathGenerator2, &pathGenerator4,
			&pathGenerator5, &pathGenerator7, &pathGenerator9};

	TalentTreeStructure talentTreeStructure;

	TalentTreeGenerator talentTreeGenerator(pathGenerators, talentTreeStructure.talentPaths);

	auto talentTree = talentTreeGenerator.GenerateTalentTree();

	for (auto& talentPath : talentTreeStructure.talentPaths)
	{
		for (auto& talentName : talentPath.second)
		{
			std::cout << talentName << ": " << talentTree->talents[talentName]->toString() << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << talentTree->talents.size() << std::endl << std::endl;

	for (int i = 0; i < 30; i++)
	{
		auto talentPath = pathGenerator4.GeneratePathWithTraits({"Acid"}, 4, 1);
		for (auto& talent : talentPath)
		{
			std::cout << talent->toString() << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (int i = 0; i < 30; i++)
	{
		auto talentPath = pathGenerator7.GeneratePathWithTraits({"Acid"}, 4, 1);
		for (auto& talent : talentPath)
		{
			std::cout << talent->toString() << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (int i = 0; i < 30; i++)
	{
		auto talentPath = pathGenerator9.GeneratePath(1, 0);
		for (auto& talent : talentPath)
		{
			std::cout << talent->toString() << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	system("pause");
	return 0;
}

