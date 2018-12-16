#include "stdafx.h"
#include "PathGenerator.h"
#include "Talent.h"
#include "TalentEntry.h"
#include <cmath>
#include <limits>
#include <random>
#include <iterator>

template<typename Iter, typename RandomGenerator>
Iter SelectRandom(Iter start, Iter end, RandomGenerator& randomGen)
{
	std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
	std::advance(start, dis(randomGen));

	return start;
}

template<typename Iter>
Iter SelectRandom(Iter start, Iter end)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	return SelectRandom(start, end, gen);
}

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
	TalentDictEntry dictEntry = dictionary->GetDictEntry(property->trait->GetTerminalTraitsId()[0]);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(dictEntry.values.first,
			std::nextafter(dictEntry.values.second, std::numeric_limits<float>::max()));
	float talentValue = roundf(dis(gen) * 100) / 100;

	return Talent({ {property, dictEntry.modifier, talentValue} });
}

Property* PathGenerator::GetRandomProperty(std::unordered_set<Property*> properties) const
{
	return *SelectRandom(properties.begin(), properties.end());
}

