#include "Options.h"
#include "ProgramOptions.h"
#include "Resource.h"
#include <iostream>
#include <memory>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

namespace Options
{
namespace
{
const std::string OPTION_ARG_TALENT_TREE = "talent-tree";
const std::string OPTION_ARG_BRANCH = "branch";
const unsigned int DEFAULT_ITERATIONS = 1;

void showHelp()
{
	std::cout << HelpMessage_txt << std::endl;
}

void reportError(const std::string& error)
{
	std::cerr << error << std::endl << std::endl;
	showHelp();
	exit(1);
}

unsigned int stoui(const std::string& s)
{
	unsigned long longResult = stoul(s);
	unsigned int result = longResult;
	if (result != longResult) throw std::out_of_range("Too big for an unsigned int!");
	return result;
}

unsigned int getUnsignedInt(const std::string& s)
{
	try
	{
		return stoui(s);
	}
	catch (std::exception e)
	{
		reportError("Could not parse an unsigned int from " + s);
	}
	return 0;
}

enum class Option
{
	NONE, HELP, SEED, RANDOM, GENERATION, ITERATIONS
};

bool needsArgumentOption(const Option option)
{
	switch (option)
	{
		case Option::SEED: return true;
		case Option::RANDOM: return false;
		case Option::GENERATION: return true;
		case Option::ITERATIONS: return true;
		case Option::HELP: return false;
		default: return false;
	}
}

bool hasNecessaryArguments(const Option option,
		const std::vector<std::string>& args,
		const int currentArg)
{
	return !needsArgumentOption(option) || (currentArg + 1 < args.size());
}

void addRandomSeed(ProgramOptions& programOptions)
{
	programOptions.withSeed(std::random_device()());
}

GenerationType getGenerationType(const std::string& generationType)
{
	if (OPTION_ARG_TALENT_TREE == generationType) return GenerationType::TALENT_TREE;
	if (OPTION_ARG_BRANCH == generationType) return GenerationType::BRANCH;
	reportError("Unknown generation type: " + generationType);
	return GenerationType::NONE;
}

void processOption(const Option option,
		const std::vector<std::string>& args,
		const int currentArg,
		ProgramOptions& programOptions)
{
	switch (option)
	{
		case Option::SEED:
			programOptions.withSeed(getUnsignedInt(args[currentArg + 1]));
			return;
		case Option::RANDOM:
			addRandomSeed(programOptions);
			return;
		case Option::GENERATION:
			programOptions.withGenerationType(getGenerationType(args[currentArg + 1]));
			return;
		case Option::ITERATIONS:
			programOptions.withIterations(getUnsignedInt(args[currentArg + 1]));
			return;
		case Option::HELP:
			showHelp();
			exit(0);
		default:
			break;
	}
}

Option parseShortOption(const char arg)
{
	if ('h' == arg) return Option::HELP;
	if ('s' == arg) return Option::SEED;
	if ('r' == arg) return Option::RANDOM;
	if ('g' == arg) return Option::GENERATION;
	if ('i' == arg) return Option::ITERATIONS;
	return Option::NONE;
}

int parseShortOptions(const std::vector<std::string>& args, const int currentArg, ProgramOptions& programOptions)
{
	if (args[currentArg].length() == 1)
	{
		reportError("Found empty option: -");
	}
	bool foundArgumentOption = false;
	for (int j = 1; j < args[currentArg].length(); j++)
	{
		const Option option = parseShortOption(args[currentArg][j]);
		if (option == Option::NONE)
		{
			std::string errorMessage = "Unsupported option: " + std::string(1, args[currentArg][j]);
			errorMessage += " in argument: " + args[currentArg];
			reportError(errorMessage);
		}
		if (!hasNecessaryArguments(option, args, currentArg))
		{
			std::string errorMessage = "Option " + std::string(1, args[currentArg][j]);
			errorMessage += " in argument " + args[currentArg];
			errorMessage += " does not have the necessary option argument!";
			reportError(errorMessage);
		}
		const bool needArgOption = needsArgumentOption(option);
		if (foundArgumentOption && needArgOption)
		{
			reportError("Found two or more options requiring option argument in a single argument: "
					+ args[currentArg]);
		}
		processOption(option, args, currentArg, programOptions);
		foundArgumentOption |= needArgOption;
	}
	return currentArg + (foundArgumentOption ? 2 : 1);
}

Option parseLongOption(const std::string& arg)
{
	if ("help" == arg) return Option::HELP;
	if ("seed" == arg) return Option::SEED;
	if ("random" == arg) return Option::RANDOM;
	if ("generation" == arg) return Option::GENERATION;
	if ("iterations" == arg) return Option::ITERATIONS;
	return Option::NONE;
}

Option getLongOption(const std::string& argString)
{
	if (argString.length() == 2) return Option::NONE;
	return parseLongOption(argString.substr(2));
}

int parseLongOption(const std::vector<std::string>& args, const int currentArg, ProgramOptions& programOptions)
{
	const Option option = getLongOption(args[currentArg]);
	if (option == Option::NONE) reportError("Unsupported option: " + args[currentArg]);
	if (!hasNecessaryArguments(option, args, currentArg))
	{
		reportError("Option " + args[currentArg] + " does not have the necessary option argument!");
	}
	processOption(option, args, currentArg, programOptions);
	return currentArg + (needsArgumentOption(option) ? 2 : 1);
}

void addDefaultOptions(ProgramOptions& programOptions)
{
	if (!programOptions.getHasSeed()) addRandomSeed(programOptions);
	if (GenerationType::NONE == programOptions.getGenerationType())
	{
		programOptions.withGenerationType(GenerationType::TALENT_TREE);
	}
	if (programOptions.getIterations() <= 0)
	{
		programOptions.withIterations(DEFAULT_ITERATIONS);
	}
}
}

std::unique_ptr<ProgramOptions> parseArgs(const std::vector<std::string> args)
{
	std::unique_ptr<ProgramOptions> programOptions = std::make_unique<ProgramOptions>();

	for (int i = 0; i < args.size();)
	{
		if (args[i].compare(0, 2, "--") == 0)
		{
			const int nextArgIndex = parseLongOption(args, i, *programOptions);
			i = nextArgIndex;
		}
		else if (args[i].compare(0, 1, "-") == 0)
		{
			const int nextArgIndex = parseShortOptions(args, i, *programOptions);
			i = nextArgIndex;
		}
		else
		{
			reportError("Could not recognize option in argument: " + args[i]);
		}
	}

	addDefaultOptions(*programOptions);

	return programOptions;
}
}

