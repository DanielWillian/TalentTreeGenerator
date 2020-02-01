// TalentTree.cpp : Defines the entry point for the console application.
//

#include "Generators/BranchGenerator.h"
#include "Generators/PropertyDistance.h"
#include "Generators/PropertyRepository.h"
#include "Generators/TalentTreeGenerator.h"
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
	BranchGenerator branchGenerator1(propertyRep.level1Properties, &talentDictionary1,
			propertyRep.level3Properties, &talentDictionary3);

	TalentDictionaryLevel2 talentDictionary2;
	BranchGenerator branchGenerator2(propertyRep.level2Properties, &talentDictionary2,
			propertyRep.level2Properties, &talentDictionary2);

	TalentDictionaryLevel4 talentDictionary4;
	TalentDictionaryLevel6 talentDictionary6;
	BranchGenerator branchGenerator4(propertyRep.level4Properties, &talentDictionary4,
			propertyRep.level6Properties, &talentDictionary6);

	TalentDictionaryLevel5 talentDictionary5;
	BranchGenerator branchGenerator5(propertyRep.level5Properties, &talentDictionary5,
			propertyRep.level5Properties, &talentDictionary5);

	TalentDictionaryLevel7 talentDictionary7;
	TalentDictionaryLevel8 talentDictionary8;
	BranchGenerator branchGenerator7(propertyRep.level7Properties, &talentDictionary7,
			propertyRep.level8Properties, &talentDictionary8);

	TalentDictionaryLevel9 talentDictionary9;
	BranchGenerator branchGenerator9(propertyRep.level9Properties, &talentDictionary9,
			propertyRep.level9Properties, &talentDictionary9);

	std::vector<BranchGenerator*> branchGenerators = {&branchGenerator1, &branchGenerator2, &branchGenerator4,
			&branchGenerator5, &branchGenerator7, &branchGenerator9};

	BranchDictionary branchDictionary;

	TalentTreeGenerator talentTreeGenerator(branchGenerators, branchDictionary.talentBranches);

	auto talentTree = talentTreeGenerator.GenerateTalentTree();

	for (auto& talentBranch : branchDictionary.talentBranches)
	{
		for (auto& talentName : talentBranch.second)
		{
			std::cout << talentName << ": " << talentTree->talents[talentName]->toString() << std::endl;
		}
		std::cout << std::endl;
	}

	std::vector<std::string> level1PropertyNames(propertyRep.baseProperties);
	std::vector<std::string> level4PropertyNames(level1PropertyNames);
	std::copy(propertyRep.damageTypes.begin(), propertyRep.damageTypes.end(), std::back_inserter(level4PropertyNames));
	std::vector<std::string> level7PropertyNames(level4PropertyNames);
	std::copy(propertyRep.weaponTypes.begin(), propertyRep.weaponTypes.end(), std::back_inserter(level7PropertyNames));

	std::cout << "------- Biased level 1 branches -------" << std::endl << std::endl;
	for (int i = 0; i < 30; i++)
	{
		const int randomInt = random.GetRandomInt(0, (int) level1PropertyNames.size() - 1);
		std::string randomBias = level1PropertyNames[randomInt];
		std::cout << "Bias: " << randomBias << std::endl;
		auto talentBranch = branchGenerator1.GenerateBranchWithTraits({ randomBias }, 4, 1);
		for (auto& talent : talentBranch)
		{
			std::cout << talent->toString() << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "------- Biased level 4 branches -------" << std::endl << std::endl;
	for (int i = 0; i < 30; i++)
	{
		const int randomInt = random.GetRandomInt(0, (int) level4PropertyNames.size() - 1);
		std::string randomBias = level4PropertyNames[randomInt];
		std::cout << "Bias: " << randomBias << std::endl;
		auto talentBranch = branchGenerator4.GenerateBranchWithTraits({ randomBias }, 4, 1);
		for (auto& talent : talentBranch)
		{
			std::cout << talent->toString() << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "------- Biased level 7 branches -------" << std::endl << std::endl;
	for (int i = 0; i < 30; i++)
	{
		const int randomInt = random.GetRandomInt(0, (int) level7PropertyNames.size() - 1);
		std::string randomBias = level7PropertyNames[randomInt];
		std::cout << "Bias: " << randomBias << std::endl;
		auto talentBranch = branchGenerator7.GenerateBranchWithTraits({ randomBias }, 7, 2);
		for (auto& talent : talentBranch)
		{
			std::cout << talent->toString() << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	return 0;
}

