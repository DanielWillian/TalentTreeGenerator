#include "stdafx.h"
#include "PathGenerator.h"
#include "Talent.h"
#include "TalentEntry.h"
#include <cmath>
#include <limits>
#include <random>
#include <iterator>

std::unordered_set<Property*> PathGenerator::GetAllRelatedProperties(
		const Property* property,
		std::unordered_set<Property*> properties) const
{
	std::unordered_set<Property*> result;

	for (auto* otherProperty : properties)
	{
		if (Property::DistanceBetweenProperties(*property, *otherProperty) <= 5)
		{
			result.insert(otherProperty);
		}
	}

	return result;
}

std::vector<Talent> PathGenerator::GeneratePath(int numLesser, int numGreater)
{
	if (numLesser <= 1 && numGreater <= 0)
	{
		return {};
	}
	std::vector<Talent> result;

	result.push_back(GenerateRandomTalent(true));
	numLesser--;
	std::unordered_set<Property*> lesserPossibleProperties = lesserProperties;
	IntersectionOfProperties(lesserPossibleProperties, result[0]);
	for (int i = 0; i < numLesser; i++)
	{
		Talent talent = GenerateRandomTalent(lesserPossibleProperties, lesserDictionary);
		IntersectionOfProperties(lesserPossibleProperties, talent);
		result.push_back(talent);
	}

	std::unordered_set<Property*> greaterPossibleProperties = greaterProperties;
	IntersectionOfProperties(greaterPossibleProperties, result[0]);
	for (int i = 0; i < numGreater; i++)
	{
		Talent talent = GenerateRandomTalent(greaterPossibleProperties, greaterDictionary);
		IntersectionOfProperties(greaterPossibleProperties, talent);
		result.push_back(talent);
	}

	return result;
}

void PathGenerator::IntersectionOfProperties(std::unordered_set<Property*>& inOutProperties, const Talent& talent) const
{
	for (auto& talentEntry : talent.talentEntries)
	{
		inOutProperties = GetIntersection(inOutProperties,
				GetAllRelatedProperties(talentEntry.property, inOutProperties));
	}
}

std::unordered_set<Property*> PathGenerator::GetIntersection(const std::unordered_set<Property*>& a,
		const std::unordered_set<Property*>& b) const
{
	std::unordered_set<Property*> result;
	for (auto it = a.begin(); it != a.end(); it++)
	{
		if (b.find(*it) != b.end())
		{
			result.insert(*it);
		}
	}
	return result;
}

Talent PathGenerator::GenerateRandomTalent(const bool lesser) const
{
	auto& properties = lesser ? lesserProperties : greaterProperties;
	auto* dictionary = lesser ? lesserDictionary : greaterDictionary;
	return GenerateRandomTalent(properties, dictionary);
}

Talent PathGenerator::GenerateRandomTalent(const std::unordered_set<Property*>& properties,
		const TalentDictionary* dictionary) const
{
	auto propertyRange = dictionary->GetPropertiesNumberRange();
	const int numberOfProperties = GetRandomInt(propertyRange.first, propertyRange.second);

	std::vector<TalentEntry> tupleList;
	for (int i = 0; i < numberOfProperties; i++)
	{
		auto* property = GetRandomProperty(properties);

		TalentDictEntry dictEntry = dictionary->GetDictEntry(property->trait->GetTerminalTraitsId()[0]);
		const float randomValue = GetRandomFloat(dictEntry.values.first, dictEntry.values.second);
		const float talentValue = ((roundf(randomValue * 100) / 100 - 1) / numberOfProperties) + 1;

		tupleList.push_back({property, dictEntry.modifier, talentValue});
	}

	return Talent(tupleList);
}

int PathGenerator::GetRandomInt(const int min, const int max) const
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}

float PathGenerator::GetRandomFloat(const float min, const float max) const
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, std::nextafter(max, std::numeric_limits<float>::max()));
	return dis(gen);
}

Property* PathGenerator::GetRandomProperty(std::unordered_set<Property*> properties) const
{
	return *SelectRandom(properties.begin(), properties.end());
}

template<typename Iter>
Iter PathGenerator::SelectRandom(Iter start, Iter end) const
{
	std::advance(start, GetRandomInt(0, std::distance(start, end) - 1));

	return start;
}

