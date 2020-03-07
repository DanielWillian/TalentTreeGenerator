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
#include "Options/Options.h"
#include "Options/ProgramOptions.h"
#include "Utils/Random.h"
#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <vector>

const int TALENT_LEVEL1_INDEX = 0;
const int TALENT_LEVEL2_INDEX = 1;
const int TALENT_LEVEL3_INDEX = 2;
const int TALENT_LEVEL4_INDEX = 3;
const int TALENT_LEVEL5_INDEX = 4;
const int TALENT_LEVEL6_INDEX = 5;
const int TALENT_LEVEL7_INDEX = 6;
const int TALENT_LEVEL8_INDEX = 7;
const int TALENT_LEVEL9_INDEX = 8;

const int BRANCH_LEVEL1_INDEX = 0;
const int BRANCH_LEVEL2_INDEX = 1;
const int BRANCH_LEVEL4_INDEX = 2;
const int BRANCH_LEVEL5_INDEX = 3;
const int BRANCH_LEVEL7_INDEX = 4;
const int BRANCH_LEVEL9_INDEX = 5;

std::vector<std::unique_ptr<TalentDictionary>> createTalentDictionaries();
std::vector<std::unique_ptr<BranchGenerator>> createBranchGenerators(
		const std::vector<TalentDictionary*>& dictionaries);
template <typename T>
std::vector<T*> mapToRawPointers(const std::vector<std::unique_ptr<T>>& dictionaries);

void generateArtifact(const ProgramOptions& programOptions);
void generateTalentTree(const unsigned int iterations);
void generateBranches(const unsigned int iterations);
void generateBranch(const std::vector<std::string>& propertyNames,
		const BranchGenerator& branchGenerator,
		const int numLesserTalents,
		const int numGreaterTalents,
		const unsigned int iterations);

int main(int argc, char **argv)
{
	std::vector<std::string> args;
	for (int i = 1; i < argc; i++) {
		args.push_back(std::string(argv[i]));
	}

	std::unique_ptr<ProgramOptions> programOptions = Options::parseArgs(std::move(args));

	if (!programOptions->getHasSeed())
	{
		std::cerr << "Could not retrieve seed!";
		exit(1);
	}

	std::cout << "---------- Seed: " << programOptions->getSeed() << " ----------" << std::endl << std::endl;

	Random& random = Random::GetInstance();
	random.gen.seed(programOptions->getSeed());

	generateArtifact(*programOptions);

	return 0;
}

std::vector<std::unique_ptr<TalentDictionary>> createTalentDictionaries()
{
	std::vector<std::unique_ptr<TalentDictionary>> dictionaries;
	dictionaries.emplace_back(std::make_unique<TalentDictionaryLevel1>());
	dictionaries.emplace_back(std::make_unique<TalentDictionaryLevel2>());
	dictionaries.emplace_back(std::make_unique<TalentDictionaryLevel3>());
	dictionaries.emplace_back(std::make_unique<TalentDictionaryLevel4>());
	dictionaries.emplace_back(std::make_unique<TalentDictionaryLevel5>());
	dictionaries.emplace_back(std::make_unique<TalentDictionaryLevel6>());
	dictionaries.emplace_back(std::make_unique<TalentDictionaryLevel7>());
	dictionaries.emplace_back(std::make_unique<TalentDictionaryLevel8>());
	dictionaries.emplace_back(std::make_unique<TalentDictionaryLevel9>());
	return std::move(dictionaries);
}

std::vector<std::unique_ptr<BranchGenerator>> createBranchGenerators(const std::vector<TalentDictionary*>& dictionaries)
{
	const PropertyRepository& propertyRep = PropertyRepository::GetInstance();

	std::unique_ptr<BranchGenerator> branchGenerator1 = std::make_unique<BranchGenerator>(
			propertyRep.level1Properties,
			dictionaries[TALENT_LEVEL1_INDEX],
			propertyRep.level3Properties,
			dictionaries[TALENT_LEVEL3_INDEX]);

	std::unique_ptr<BranchGenerator> branchGenerator2 = std::make_unique<BranchGenerator>(
			propertyRep.level2Properties,
			dictionaries[TALENT_LEVEL2_INDEX],
			propertyRep.level2Properties,
			dictionaries[TALENT_LEVEL2_INDEX]);

	std::unique_ptr<BranchGenerator> branchGenerator4 = std::make_unique<BranchGenerator>(
			propertyRep.level4Properties,
			dictionaries[TALENT_LEVEL4_INDEX],
			propertyRep.level6Properties,
			dictionaries[TALENT_LEVEL6_INDEX]);

	std::unique_ptr<BranchGenerator> branchGenerator5 = std::make_unique<BranchGenerator>(
			propertyRep.level5Properties,
			dictionaries[TALENT_LEVEL5_INDEX],
			propertyRep.level5Properties,
			dictionaries[TALENT_LEVEL5_INDEX]);

	std::unique_ptr<BranchGenerator> branchGenerator7 = std::make_unique<BranchGenerator>(
			propertyRep.level7Properties,
			dictionaries[TALENT_LEVEL7_INDEX],
			propertyRep.level8Properties,
			dictionaries[TALENT_LEVEL8_INDEX]);

	std::unique_ptr<BranchGenerator> branchGenerator9 = std::make_unique<BranchGenerator>(
			propertyRep.level9Properties,
			dictionaries[TALENT_LEVEL9_INDEX],
			propertyRep.level9Properties,
			dictionaries[TALENT_LEVEL9_INDEX]);

	std::vector<std::unique_ptr<BranchGenerator>> branchGenerators;
	branchGenerators.push_back(std::move(branchGenerator1));
	branchGenerators.push_back(std::move(branchGenerator2));
	branchGenerators.push_back(std::move(branchGenerator4));
	branchGenerators.push_back(std::move(branchGenerator5));
	branchGenerators.push_back(std::move(branchGenerator7));
	branchGenerators.push_back(std::move(branchGenerator9));

	return std::move(branchGenerators);
}

template <typename T>
std::vector<T*> mapToRawPointers(const std::vector<std::unique_ptr<T>>& dictionaries)
{
	std::vector<T*> rawPointers;
	for (const auto& dict : dictionaries) rawPointers.push_back(&(*dict));
	return std::move(rawPointers);
}

void generateArtifact(const ProgramOptions& programOptions)
{
	if (programOptions.getGenerationType() == GenerationType::TALENT_TREE)
	{
		std::cout << "---------- Generating talent tree ----------" << std::endl <<
				"---------- Number of iterations: " << programOptions.getIterations() <<
				" ----------" << std::endl;
		generateTalentTree(programOptions.getIterations());
	}
	else if (programOptions.getGenerationType() == GenerationType::BRANCHES)
	{
		std::cout << "---------- Generating branches ----------" << std::endl <<
				"---------- Number of iterations: " << programOptions.getIterations() <<
				" ----------" << std::endl;
		generateBranches(programOptions.getIterations());
	}
	else
	{
		std::cerr << "Could not generate anything." << std::endl;
		exit(1);
	}
}

void generateTalentTree(const unsigned int iterations)
{
	std::cout << "---------- Initializing generator ----------" << std::endl << std::endl;

	const std::vector<std::unique_ptr<TalentDictionary>> dictionaries = createTalentDictionaries();
	const std::vector<TalentDictionary*> dictionariesRaw = mapToRawPointers(dictionaries);
	std::vector<std::unique_ptr<BranchGenerator>> branchGenerators = createBranchGenerators(dictionariesRaw);
	const std::vector<BranchGenerator*> branchGeneratorsRaw = mapToRawPointers(branchGenerators);

	BranchDictionary branchDictionary;

	TalentTreeGenerator talentTreeGenerator(branchGeneratorsRaw, branchDictionary.talentBranches);

	for (unsigned int i = 0; i < iterations; i++)
	{
		std::cout << "---------- Iteration: " << i << " ----------" << std::endl << std::endl;

		auto talentTree = talentTreeGenerator.GenerateTalentTree();

		for (auto& talentBranch : branchDictionary.talentBranches)
		{
			for (auto& talentName : talentBranch.second)
			{
				std::cout << talentName << ": " << talentTree->talents[talentName]->toString() << std::endl;
			}
			std::cout << std::endl;
		}
	}
}

void generateBranches(const unsigned int iterations)
{
	std::cout << "---------- Initializing generator ----------" << std::endl << std::endl;

	const std::vector<std::unique_ptr<TalentDictionary>> dictionaries = createTalentDictionaries();
	const std::vector<TalentDictionary*> dictionariesRaw = mapToRawPointers(dictionaries);
	std::vector<std::unique_ptr<BranchGenerator>> branchGenerators = createBranchGenerators(dictionariesRaw);
	const std::vector<BranchGenerator*> branchGeneratorsRaw = mapToRawPointers(branchGenerators);

	const PropertyRepository& propertyRep = PropertyRepository::GetInstance();

	std::vector<std::string> level1PropertyNames(propertyRep.baseProperties);
	std::vector<std::string> level4PropertyNames(level1PropertyNames);
	std::copy(propertyRep.damageTypes.begin(), propertyRep.damageTypes.end(), std::back_inserter(level4PropertyNames));
	std::vector<std::string> level7PropertyNames(level4PropertyNames);
	std::copy(propertyRep.weaponTypes.begin(), propertyRep.weaponTypes.end(), std::back_inserter(level7PropertyNames));

	std::cout << "------- Biased level 1 branches -------" << std::endl << std::endl;
	generateBranch(level1PropertyNames, *branchGenerators[BRANCH_LEVEL1_INDEX], 4, 1, iterations);
	std::cout << std::endl;

	std::cout << "------- Biased level 4 branches -------" << std::endl << std::endl;
	generateBranch(level4PropertyNames, *branchGenerators[BRANCH_LEVEL4_INDEX], 4, 1, iterations);
	std::cout << std::endl;

	std::cout << "------- Biased level 7 branches -------" << std::endl << std::endl;
	generateBranch(level7PropertyNames, *branchGenerators[BRANCH_LEVEL7_INDEX], 7, 2, iterations);
	std::cout << std::endl;
}

void generateBranch(const std::vector<std::string>& propertyNames,
		const BranchGenerator& branchGenerator,
		const int numLesserTalents,
		const int numGreaterTalents,
		const unsigned int iterations)
{
	Random& random = Random::GetInstance();

	for (unsigned int i = 0; i < iterations; i++)
	{
		std::cout << "---------- Iteration: " << i << " ----------" << std::endl << std::endl;

		const int randomInt = random.GetRandomInt(0, (int) propertyNames.size() - 1);
		std::string randomBias = propertyNames[randomInt];
		std::cout << "Bias: " << randomBias << std::endl;
		auto talentBranch = branchGenerator.GenerateBranchWithTraits({ randomBias },
				numLesserTalents,
				numGreaterTalents);
		for (auto& talent : talentBranch)
		{
			std::cout << talent->toString() << std::endl;
		}
		std::cout << std::endl;
	}
}

