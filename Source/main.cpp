// TalentTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BranchGenerator.h"
#include "PropertyDistance.h"
#include "PropertyRepository.h"
#include "TalentTreeGenerator.h"
#include "Dictionaries/BranchDictionary.h"
#include "Dictionaries/TalentDictionaryLevel1.h"
#include "Dictionaries/TalentDictionaryLevel2.h"
#include "Dictionaries/TalentDictionaryLevel3.h"
#include "Dictionaries/TalentDictionaryLevel4.h"
#include "Dictionaries/TalentDictionaryLevel5.h"
#include "Dictionaries/TalentDictionaryLevel6.h"
#include "Dictionaries/TalentDictionaryLevel7.h"
#include "Dictionaries/TalentDictionaryLevel8.h"
#include "Dictionaries/TalentDictionaryLevel9.h"
#include "Models/TalentTree.h"
#include "Utils/Random.h"
#include <iostream>
#include <random>
#include <sstream>

int main(int argc, char **argv)
{
	std::random_device rd;
	unsigned int seed = rd();
	if (argc >= 2)
	{
		std::istringstream iss(argv[1]);

		if (!(iss >> seed))
		{
			std::random_device rd;
			seed = rd();
		}
	}

	Random& random = Random::GetInstance();
	random.gen.seed(seed);

	std::cout << "Seed: " << seed << std::endl << std::endl;

	const PropertyRepository& propertyRep = PropertyRepository::GetInstance();

	TalentDictionaryLevel1 talentDictionary1;
	TalentDictionaryLevel3 talentDictionary3;
	BranchGenerator pathGenerator1(propertyRep.level1Properties, &talentDictionary1,
			propertyRep.level3Properties, &talentDictionary3);

	TalentDictionaryLevel2 talentDictionary2;
	BranchGenerator pathGenerator2(propertyRep.level2Properties, &talentDictionary2,
			propertyRep.level2Properties, &talentDictionary2);

	TalentDictionaryLevel4 talentDictionary4;
	TalentDictionaryLevel6 talentDictionary6;
	BranchGenerator pathGenerator4(propertyRep.level4Properties, &talentDictionary4,
			propertyRep.level6Properties, &talentDictionary6);

	TalentDictionaryLevel5 talentDictionary5;
	BranchGenerator pathGenerator5(propertyRep.level5Properties, &talentDictionary5,
			propertyRep.level5Properties, &talentDictionary5);

	TalentDictionaryLevel7 talentDictionary7;
	TalentDictionaryLevel8 talentDictionary8;
	BranchGenerator pathGenerator7(propertyRep.level7Properties, &talentDictionary7,
			propertyRep.level8Properties, &talentDictionary8);

	TalentDictionaryLevel9 talentDictionary9;
	BranchGenerator pathGenerator9(propertyRep.level9Properties, &talentDictionary9,
			propertyRep.level9Properties, &talentDictionary9);

	std::vector<BranchGenerator*> pathGenerators = {&pathGenerator1, &pathGenerator2, &pathGenerator4,
			&pathGenerator5, &pathGenerator7, &pathGenerator9};

	BranchDictionary branchDictionary;

	TalentTreeGenerator talentTreeGenerator(pathGenerators, branchDictionary.talentBranches);

	auto talentTree = talentTreeGenerator.GenerateTalentTree();

	for (auto& talentBranch : branchDictionary.talentBranches)
	{
		for (auto& talentName : talentBranch.second)
		{
			std::cout << talentName << ": " << talentTree->talents[talentName]->toString() << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << talentTree->talents.size() << std::endl << std::endl;

	for (int i = 0; i < 30; i++)
	{
		auto talentBranch = pathGenerator4.GenerateBranchWithTraits({"Acid"}, 4, 1);
		for (auto& talent : talentBranch)
		{
			std::cout << talent->toString() << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (int i = 0; i < 30; i++)
	{
		auto talentBranch = pathGenerator7.GenerateBranchWithTraits({"Acid"}, 4, 1);
		for (auto& talent : talentBranch)
		{
			std::cout << talent->toString() << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (int i = 0; i < 30; i++)
	{
		auto talentBranch = pathGenerator9.GenerateBranch(1, 0);
		for (auto& talent : talentBranch)
		{
			std::cout << talent->toString() << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	return 0;
}

