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
#include "Time/TimeRepository.h"
#include "Utils/Random.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <vector>

const int TALENT_LEVEL_1_INDEX = 0;
const int TALENT_LEVEL_2_INDEX = 1;
const int TALENT_LEVEL_3_INDEX = 2;
const int TALENT_LEVEL_4_INDEX = 3;
const int TALENT_LEVEL_5_INDEX = 4;
const int TALENT_LEVEL_6_INDEX = 5;
const int TALENT_LEVEL_7_INDEX = 6;
const int TALENT_LEVEL_8_INDEX = 7;
const int TALENT_LEVEL_9_INDEX = 8;

const int BRANCH_LEVEL_1_INDEX = 0;
const int BRANCH_LEVEL_2_INDEX = 1;
const int BRANCH_LEVEL_4_INDEX = 2;
const int BRANCH_LEVEL_5_INDEX = 3;
const int BRANCH_LEVEL_7_INDEX = 4;
const int BRANCH_LEVEL_9_INDEX = 5;

const int LEVEL_1_LESSER_TALENTS = 4;
const int LEVEL_1_GREATER_TALENTS = 1;
const int LEVEL_4_LESSER_TALENTS = 4;
const int LEVEL_4_GREATER_TALENTS = 1;
const int LEVEL_7_LESSER_TALENTS = 7;
const int LEVEL_7_GREATER_TALENTS = 2;

std::vector<std::unique_ptr<TalentDictionary>> createTalentDictionaries();
std::vector<std::unique_ptr<BranchGenerator>> createBranchGenerators(
		const std::vector<TalentDictionary*>& dictionaries);
template <typename T>
std::vector<T*> mapToRawPointers(const std::vector<std::unique_ptr<T>>& dictionaries);

void generateArtifact(const ProgramOptions& programOptions);
void generateTalentTree(const ProgramOptions& programOptions);
void generateBranches(const ProgramOptions& programOptions);
void generateBranch1(const ProgramOptions& programOptions,
		const std::vector<std::string>& propertyNames,
		const BranchGenerator& branchGenerator);
void generateBranch4(const ProgramOptions& programOptions,
		const std::vector<std::string>& propertyNames,
		const BranchGenerator& branchGenerator);
void generateBranch7(const ProgramOptions& programOptions,
		const std::vector<std::string>& propertyNames,
		const BranchGenerator& branchGenerator);
void generateBranch(const ProgramOptions& programOptions,
		const std::vector<std::string>& propertyNames,
		const BranchGenerator& branchGenerator,
		const int numLesserTalents,
		const int numGreaterTalents);
std::string getBias(const ProgramOptions& programOptions,
		const std::vector<std::string>& propertyNames);
void generateTimeReport(const ProgramOptions& programOptions);
void printArtifactTimes(const std::vector<std::chrono::milliseconds>& artifactTimes);

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
	if (programOptions->getMeasureTime()) generateTimeReport(*programOptions);

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
			dictionaries[TALENT_LEVEL_1_INDEX],
			propertyRep.level3Properties,
			dictionaries[TALENT_LEVEL_3_INDEX]);

	std::unique_ptr<BranchGenerator> branchGenerator2 = std::make_unique<BranchGenerator>(
			propertyRep.level2Properties,
			dictionaries[TALENT_LEVEL_2_INDEX],
			propertyRep.level2Properties,
			dictionaries[TALENT_LEVEL_2_INDEX]);

	std::unique_ptr<BranchGenerator> branchGenerator4 = std::make_unique<BranchGenerator>(
			propertyRep.level4Properties,
			dictionaries[TALENT_LEVEL_4_INDEX],
			propertyRep.level6Properties,
			dictionaries[TALENT_LEVEL_6_INDEX]);

	std::unique_ptr<BranchGenerator> branchGenerator5 = std::make_unique<BranchGenerator>(
			propertyRep.level5Properties,
			dictionaries[TALENT_LEVEL_5_INDEX],
			propertyRep.level5Properties,
			dictionaries[TALENT_LEVEL_5_INDEX]);

	std::unique_ptr<BranchGenerator> branchGenerator7 = std::make_unique<BranchGenerator>(
			propertyRep.level7Properties,
			dictionaries[TALENT_LEVEL_7_INDEX],
			propertyRep.level8Properties,
			dictionaries[TALENT_LEVEL_8_INDEX]);

	std::unique_ptr<BranchGenerator> branchGenerator9 = std::make_unique<BranchGenerator>(
			propertyRep.level9Properties,
			dictionaries[TALENT_LEVEL_9_INDEX],
			propertyRep.level9Properties,
			dictionaries[TALENT_LEVEL_9_INDEX]);

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
	const GenerationType generationType = programOptions.getGenerationType();
	const unsigned int iterations = programOptions.getIterations();
	std::cout << "---------- Generating " << Options::getGenerationTypeName(generationType) <<
			" ----------" << std::endl <<
			"---------- Number of iterations: " << iterations <<
			" ----------" << std::endl;
	if (generationType == GenerationType::TALENT_TREE)
	{
		generateTalentTree(programOptions);
	}
	else if (generationType == GenerationType::BRANCHES ||
			generationType == GenerationType::BRANCH_1 ||
			generationType == GenerationType::BRANCH_4 ||
			generationType == GenerationType::BRANCH_7)
	{
		generateBranches(programOptions);
	}
	else
	{
		std::cerr << "Could not generate anything." << std::endl;
		exit(1);
	}
}

void generateTalentTree(const ProgramOptions& programOptions)
{
	std::cout << "---------- Initializing generator ----------" << std::endl << std::endl;

	const bool measureTime = programOptions.getMeasureTime();

	TimeRepository& timeRepository = TimeRepository::getInstance();
	std::chrono::time_point<std::chrono::steady_clock> startInitialization, endInitialization;
	if (measureTime) startInitialization = std::chrono::steady_clock::now();

	const std::vector<std::unique_ptr<TalentDictionary>> dictionaries = createTalentDictionaries();
	const std::vector<TalentDictionary*> dictionariesRaw = mapToRawPointers(dictionaries);
	std::vector<std::unique_ptr<BranchGenerator>> branchGenerators = createBranchGenerators(dictionariesRaw);
	const std::vector<BranchGenerator*> branchGeneratorsRaw = mapToRawPointers(branchGenerators);

	BranchDictionary branchDictionary;

	TalentTreeGenerator talentTreeGenerator(branchGeneratorsRaw, branchDictionary.talentBranches);

	if (measureTime)
	{
		endInitialization = std::chrono::steady_clock::now();
		const auto initializationTime = std::chrono::duration_cast<std::chrono::milliseconds>(
				endInitialization - startInitialization);
		timeRepository.setInitializationTime(initializationTime);
	}

	for (unsigned int i = 0; i < programOptions.getIterations(); i++)
	{
		std::cout << "---------- Iteration: " << i << " ----------" << std::endl << std::endl;

		std::chrono::time_point<std::chrono::steady_clock> startGeneration, endGeneration;
		if (measureTime) startGeneration = std::chrono::steady_clock::now();

		auto talentTree = talentTreeGenerator.GenerateTalentTree();

		if (measureTime)
		{
			endGeneration = std::chrono::steady_clock::now();
			const auto talentTreeTime = std::chrono::duration_cast<std::chrono::milliseconds>(
					endGeneration - startGeneration);
			timeRepository.addTalentTreeTime(talentTreeTime);
		}

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

void generateBranches(const ProgramOptions& programOptions)
{
	std::cout << "---------- Initializing generator ----------" << std::endl << std::endl;

	const GenerationType generationType = programOptions.getGenerationType();

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

	if (generationType == GenerationType::BRANCHES)
	{
		generateBranch1(programOptions, level1PropertyNames, *branchGenerators[BRANCH_LEVEL_1_INDEX]);
		generateBranch4(programOptions, level4PropertyNames, *branchGenerators[BRANCH_LEVEL_4_INDEX]);
		generateBranch7(programOptions, level7PropertyNames, *branchGenerators[BRANCH_LEVEL_7_INDEX]);
	}
	else if (generationType == GenerationType::BRANCH_1)
	{
		generateBranch1(programOptions, level1PropertyNames, *branchGenerators[BRANCH_LEVEL_1_INDEX]);
	}
	else if (generationType == GenerationType::BRANCH_4)
	{
		generateBranch4(programOptions, level4PropertyNames, *branchGenerators[BRANCH_LEVEL_4_INDEX]);
	}
	else if (generationType == GenerationType::BRANCH_7)
	{
		generateBranch7(programOptions, level7PropertyNames, *branchGenerators[BRANCH_LEVEL_7_INDEX]);
	}
}

void generateBranch1(const ProgramOptions& programOptions,
		const std::vector<std::string>& propertyNames,
		const BranchGenerator& branchGenerator)
{
	std::cout << "---------- Biased level 1 branches ----------" << std::endl << std::endl;
	generateBranch(programOptions,
			propertyNames,
			branchGenerator,
			LEVEL_1_LESSER_TALENTS,
			LEVEL_1_GREATER_TALENTS);
	std::cout << std::endl;
}

void generateBranch4(const ProgramOptions& programOptions,
		const std::vector<std::string>& propertyNames,
		const BranchGenerator& branchGenerator)
{
	std::cout << "---------- Biased level 4 branches ----------" << std::endl << std::endl;
	generateBranch(programOptions,
			propertyNames,
			branchGenerator,
			LEVEL_4_LESSER_TALENTS,
			LEVEL_4_GREATER_TALENTS);
	std::cout << std::endl;
}

void generateBranch7(const ProgramOptions& programOptions,
		const std::vector<std::string>& propertyNames,
		const BranchGenerator& branchGenerator)
{
	std::cout << "---------- Biased level 7 branches ----------" << std::endl << std::endl;
	generateBranch(programOptions,
			propertyNames,
			branchGenerator,
			LEVEL_7_LESSER_TALENTS,
			LEVEL_7_GREATER_TALENTS);
	std::cout << std::endl;
}

void generateBranch(const ProgramOptions& programOptions,
		const std::vector<std::string>& propertyNames,
		const BranchGenerator& branchGenerator,
		const int numLesserTalents,
		const int numGreaterTalents)
{
	const unsigned int iterations = programOptions.getIterations();

	for (unsigned int i = 0; i < iterations; i++)
	{
		std::cout << "---------- Iteration: " << i << " ----------" << std::endl << std::endl;

		const std::string bias = getBias(programOptions, propertyNames);
		std::cout << "Bias: " << bias << std::endl;
		auto talentBranch = branchGenerator.GenerateBranchWithTraits({ bias },
				numLesserTalents,
				numGreaterTalents);
		for (auto& talent : talentBranch)
		{
			std::cout << talent->toString() << std::endl;
		}
		std::cout << std::endl;
	}
}

std::string getBias(const ProgramOptions& programOptions,
		const std::vector<std::string>& propertyNames)
{
	if (programOptions.getUseRandomProperty())
	{
		Random& random = Random::GetInstance();
		const int randomInt = random.GetRandomInt(0, (int) propertyNames.size() - 1);
		return propertyNames[randomInt];
	}
	return programOptions.getProperty();
}

void generateTimeReport(const ProgramOptions& programOptions)
{
	const TimeRepository& timeRepository = TimeRepository::getInstance();
	const GenerationType generationType = programOptions.getGenerationType();

	std::cout << "---------- Time report ----------" << std::endl << std::endl;

	std::chrono::milliseconds initializationTime = timeRepository.getInitializationTime();
	std::cout << "---------- Time to initialize: " << initializationTime.count() <<
			" ms ----------" << std::endl;


	if (generationType == GenerationType::TALENT_TREE)
	{
		std::cout << "---------- Talent tree generation ----------" << std::endl;
		printArtifactTimes(timeRepository.getTalentTreeTimes());
	}
}

void printArtifactTimes(const std::vector<std::chrono::milliseconds>& artifactTimes)
{
	std::chrono::milliseconds::rep totalTime = 0;
	for (size_t i = 0; i < artifactTimes.size(); i++)
	{
		const auto artifactTimeCount = artifactTimes[i].count();
		totalTime += artifactTimeCount;
		std::cout << "---------- Iteration " << i << ": " <<
				artifactTimeCount << " ms ----------" << std::endl;
	}
	std::cout << "---------- Total time: " << totalTime << " ms ----------" << std::endl;
	std::cout << "---------- Average time: " << totalTime / artifactTimes.size() <<
			" ms ----------" << std::endl;
}

