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
const int BRANCH_LEVEL_4_INDEX = 2;
const int BRANCH_LEVEL_7_INDEX = 4;

const int LEVEL_1_LESSER_TALENTS = 4;
const int LEVEL_1_GREATER_TALENTS = 1;
const int LEVEL_4_LESSER_TALENTS = 4;
const int LEVEL_4_GREATER_TALENTS = 1;
const int LEVEL_7_LESSER_TALENTS = 7;
const int LEVEL_7_GREATER_TALENTS = 2;

const std::string HEADER = "-----";

std::stringstream Stream();
void printlnWithHeader(const std::ostream& message, unsigned int lines);

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
template <typename Duration, typename Rep = typename Duration::rep>
void printArtifactTimes(const std::vector<Duration>& artifactTimes);
void printTalentTreeTimes(const std::vector<std::chrono::microseconds>& artifactTimes);

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

	printlnWithHeader(Stream() << "Seed: " << programOptions->getSeed(), 2);

	Random& random = Random::GetInstance();
	random.gen.seed(programOptions->getSeed());

	generateArtifact(*programOptions);
	if (programOptions->getMeasureTime()) generateTimeReport(*programOptions);

	return 0;
}

std::stringstream Stream()
{
	return std::stringstream();
}

void printlnWithHeader(const std::ostream& message, unsigned int lines)
{
	std::cout << HEADER << " " << message.rdbuf() << " " << HEADER;
	for (unsigned int i = 0; i < lines; i++) std::cout << std::endl;
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
	return dictionaries;
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

	return branchGenerators;
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
	printlnWithHeader(Stream() <<
			"Generating " << Options::getGenerationTypeName(generationType), 1);
	printlnWithHeader(Stream() << "Number of iterations: " << iterations, 1);
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
	printlnWithHeader(Stream() << "Initializing generator", 2);

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
		const auto initializationTime = std::chrono::duration_cast<std::chrono::microseconds>(
				endInitialization - startInitialization);
		timeRepository.setInitializationTime(initializationTime);
	}

	for (unsigned int i = 0; i < programOptions.getIterations(); i++)
	{
		printlnWithHeader(Stream() << "Iteration: " << i, 2);

		std::chrono::time_point<std::chrono::steady_clock> startGeneration, endGeneration;
		if (measureTime) startGeneration = std::chrono::steady_clock::now();

		auto talentTree = talentTreeGenerator.GenerateTalentTree();

		if (measureTime)
		{
			endGeneration = std::chrono::steady_clock::now();
			const auto talentTreeTime = std::chrono::duration_cast<std::chrono::microseconds>(
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
	printlnWithHeader(Stream() << "Initializing generator", 2);

	const bool measureTime = programOptions.getMeasureTime();

	TimeRepository& timeRepository = TimeRepository::getInstance();
	std::chrono::time_point<std::chrono::steady_clock> startInitialization, endInitialization;
	if (measureTime) startInitialization = std::chrono::steady_clock::now();

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

	if (measureTime)
	{
		endInitialization = std::chrono::steady_clock::now();
		const auto initializationTime = std::chrono::duration_cast<std::chrono::microseconds>(
				endInitialization - startInitialization);
		timeRepository.setInitializationTime(initializationTime);
	}

	const GenerationType generationType = programOptions.getGenerationType();

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
	printlnWithHeader(Stream() << "Biased level 1 branches", 2);
	generateBranch(programOptions,
			propertyNames,
			branchGenerator,
			LEVEL_1_LESSER_TALENTS,
			LEVEL_1_GREATER_TALENTS);
	std::cout << std::endl;

	if (programOptions.getMeasureTime())
	{
		TimeRepository& timeRepository = TimeRepository::getInstance();
		timeRepository.setBranch1Times(timeRepository.getBranchTimes());
		timeRepository.setBranchTimes({});
	}
}

void generateBranch4(const ProgramOptions& programOptions,
		const std::vector<std::string>& propertyNames,
		const BranchGenerator& branchGenerator)
{
	printlnWithHeader(Stream() << "Biased level 4 branches", 2);
	generateBranch(programOptions,
			propertyNames,
			branchGenerator,
			LEVEL_4_LESSER_TALENTS,
			LEVEL_4_GREATER_TALENTS);
	std::cout << std::endl;

	if (programOptions.getMeasureTime())
	{
		TimeRepository& timeRepository = TimeRepository::getInstance();
		timeRepository.setBranch4Times(timeRepository.getBranchTimes());
		timeRepository.setBranchTimes({});
	}
}

void generateBranch7(const ProgramOptions& programOptions,
		const std::vector<std::string>& propertyNames,
		const BranchGenerator& branchGenerator)
{
	printlnWithHeader(Stream() << "Biased level 7 branches", 2);
	generateBranch(programOptions,
			propertyNames,
			branchGenerator,
			LEVEL_7_LESSER_TALENTS,
			LEVEL_7_GREATER_TALENTS);
	std::cout << std::endl;

	if (programOptions.getMeasureTime())
	{
		TimeRepository& timeRepository = TimeRepository::getInstance();
		timeRepository.setBranch7Times(timeRepository.getBranchTimes());
		timeRepository.setBranchTimes({});
	}
}

void generateBranch(const ProgramOptions& programOptions,
		const std::vector<std::string>& propertyNames,
		const BranchGenerator& branchGenerator,
		const int numLesserTalents,
		const int numGreaterTalents)
{
	const unsigned int iterations = programOptions.getIterations();

	const bool measureTime = programOptions.getMeasureTime();
	TimeRepository& timeRepository = TimeRepository::getInstance();

	for (unsigned int i = 0; i < iterations; i++)
	{
		printlnWithHeader(Stream() << "Iteration: " << i, 2);

		std::chrono::time_point<std::chrono::steady_clock> startGeneration, endGeneration;
		if (measureTime) startGeneration = std::chrono::steady_clock::now();

		const std::string bias = getBias(programOptions, propertyNames);
		auto talentBranch = branchGenerator.GenerateBranchWithTraits({ bias },
				numLesserTalents,
				numGreaterTalents);

		if (measureTime)
		{
			endGeneration = std::chrono::steady_clock::now();
			const auto generationTime = std::chrono::duration_cast<std::chrono::microseconds>(
					endGeneration - startGeneration);
			timeRepository.addBranchTime(generationTime);
		}

		std::cout << "Bias: " << bias << std::endl;

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

	printlnWithHeader(Stream() << "Time report", 2);

	std::chrono::microseconds initializationTime = timeRepository.getInitializationTime();
	printlnWithHeader(Stream() <<
			"Initialization: " << initializationTime.count() << " (µs)", 1);

	if (generationType == GenerationType::TALENT_TREE)
	{
		printlnWithHeader(Stream() << "Talent tree generation (ms)", 1);
		printTalentTreeTimes(timeRepository.getTalentTreeTimes());
	}
	else if (generationType == GenerationType::BRANCHES)
	{
		printlnWithHeader(Stream() << "Branch1 generation (µs)", 1);
		printArtifactTimes(timeRepository.getBranch1Times());
		printlnWithHeader(Stream() << "Branch4 generation (µs)", 1);
		printArtifactTimes(timeRepository.getBranch4Times());
		printlnWithHeader(Stream() << "Branch7 generation (µs)", 1);
		printArtifactTimes(timeRepository.getBranch7Times());
	}
	else if (generationType == GenerationType::BRANCH_1)
	{
		printlnWithHeader(Stream() << "Branch1 generation (µs)", 1);
		printArtifactTimes(timeRepository.getBranch1Times());
	}
	else if (generationType == GenerationType::BRANCH_4)
	{
		printlnWithHeader(Stream() << "Branch4 generation (µs)", 1);
		printArtifactTimes(timeRepository.getBranch4Times());
	}
	else if (generationType == GenerationType::BRANCH_7)
	{
		printlnWithHeader(Stream() << "Branch7 generation (µs)", 1);
		printArtifactTimes(timeRepository.getBranch7Times());
	}
}

template <typename Duration, typename Rep>
void printArtifactTimes(const std::vector<Duration>& artifactTimes)
{
	Rep totalTime = 0;
	for (size_t i = 0; i < artifactTimes.size(); i++)
	{
		const auto artifactTimeCount = artifactTimes[i].count();
		totalTime += artifactTimeCount;
		printlnWithHeader(Stream() << "Iteration " << i << ": " << artifactTimeCount, 1);
	}
	printlnWithHeader(Stream() << "Total time: " << totalTime, 1);
	printlnWithHeader(Stream() << "Average time: " << totalTime / artifactTimes.size(), 1);
}

void printTalentTreeTimes(const std::vector<std::chrono::microseconds>& artifactTimes)
{
	std::vector<std::chrono::milliseconds> milliTimes;
	std::transform(artifactTimes.begin(), artifactTimes.end(), std::back_inserter(milliTimes),
			[](auto t) { return std::chrono::duration_cast<std::chrono::milliseconds>(t); });
	printArtifactTimes(milliTimes);
}

