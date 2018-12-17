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

Talent PathGenerator::GenerateRandomTalent(const bool lesser) const
{
	auto& properties = lesser ? lesserProperties : greaterProperties;
	auto* dictionary = lesser ? lesserDictionary : greaterDictionary;
	auto* property = GetRandomProperty(properties);

	auto propertyRange = dictionary->GetPropertiesNumberRange();
	const int numberOfProperties = GetRandomInt(propertyRange.first, propertyRange.second);

	std::vector<TalentEntry> tupleList;
	for (int i = 0; i < numberOfProperties; i++)
	{
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

