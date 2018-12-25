#include "stdafx.h"
#include "PathGenerator.h"
#include "PropertyDistance.h"
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
		if (PropertyDistance::GetInstance().DistanceBetweenProperties(*property, *otherProperty) <= 5)
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

	std::unordered_set<Property*> lesserPossibleProperties = lesserProperties;
	result.push_back(GenerateRandomTalent(lesserPossibleProperties, lesserDictionary));
	numLesser--;
	for (int i = 0; i < numLesser; i++)
	{
		Talent talent = GenerateRandomTalent(lesserPossibleProperties, lesserDictionary);
		result.push_back(talent);
	}

	std::unordered_set<Property*> greaterPossibleProperties = greaterProperties;
	for (auto& talent : result)
	{
		IntersectionOfProperties(greaterPossibleProperties, talent);
	}
	for (int i = 0; i < numGreater; i++)
	{
		Talent talent = GenerateRandomTalent(greaterPossibleProperties, greaterDictionary);
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

void PathGenerator::IntersectionOfProperties(std::unordered_set<Property*>& inOutProperties, const Property* property) const
{
	inOutProperties = GetIntersection(inOutProperties,
			GetAllRelatedProperties(property, inOutProperties));
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

Talent PathGenerator::GenerateRandomTalent(std::unordered_set<Property*>& inOutProperties,
		const TalentDictionary* dictionary) const
{
	auto propertyRange = dictionary->GetPropertiesNumberRange();
	const int numberOfProperties = GetRandomInt(propertyRange.first, propertyRange.second);

	std::vector<TalentEntry> tupleList;
	for (int i = 0; i < numberOfProperties; i++)
	{
		auto* property = GetRandomProperty(inOutProperties);

		auto possibleEntryIt = std::find_if(tupleList.begin(), tupleList.end(),
				[&] (const auto& e) { return *e.property == *property; });
		const bool alreadyHasProperty = possibleEntryIt != tupleList.end();

		auto terminalIds = property->trait->GetTerminalTraitsId();
		auto dictEntries = dictionary->GetDictEntries(terminalIds[0]);
		dictEntries.erase(std::remove_if(dictEntries.begin(), dictEntries.end(),
				[&] (const auto* e)
				{
					return alreadyHasProperty ? possibleEntryIt->modifier != e->modifier : false;
				}),
				dictEntries.end());
		TalentDictEntry* dictEntry = *SelectRandom(dictEntries.begin(), dictEntries.end());

		float valueModifier = 1;
		auto modifierEntries = dictionary->GetModifierEntries();
		for (auto it = terminalIds.begin() + 1; it != terminalIds.end(); it++)
		{
			for (auto* entry : modifierEntries)
			{
				if (*it == entry->key)
				{
					valueModifier *= GetRandomFloat(entry->values.first, entry->values.second);
				}
			}
		}

		const int dictPrecision = dictionary->GetFloatPrecision();
		const float randomValue = GetRandomFloat(dictEntry->values.first, dictEntry->values.second);
		float talentValue = (roundf((randomValue - 1) * valueModifier / numberOfProperties * dictPrecision)
				/ dictPrecision) + 1;
		talentValue += alreadyHasProperty ? possibleEntryIt->value - 1 : 0;
		talentValue = std::min(talentValue, dictEntry->values.second * valueModifier);

		if (!alreadyHasProperty)
		{
			tupleList.push_back({property, dictEntry->modifier, talentValue});
			IntersectionOfProperties(inOutProperties, property);
		}
		else
		{
			possibleEntryIt->value = talentValue;
		}
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
	const float nextAfter = std::nextafter(max, std::numeric_limits<float>::max());
	std::uniform_real_distribution<float> dis(min, nextAfter);
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

