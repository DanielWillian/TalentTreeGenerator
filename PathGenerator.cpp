#include "stdafx.h"
#include "PathGenerator.h"
#include "PropertyDistance.h"
#include "PropertyRepository.h"
#include "Talent.h"
#include "TalentEntry.h"
#include "Statics.h"
#include <cmath>
#include <limits>
#include <random>
#include <iterator>

std::vector<Property*> PathGenerator::GetAllRelatedProperties(
		const Property* property,
		const std::vector<Property*>& properties) const
{
	std::vector<Property*> result;

	for (auto* otherProperty : properties)
	{
		if (PropertyDistance::GetInstance().DistanceBetweenProperties(*property, *otherProperty) <=
				PropertyDistance::SIMILARITY_THRESHOLD)
		{
			result.push_back(otherProperty);
		}
	}

	return result;
}

std::vector<std::unique_ptr<Talent>> PathGenerator::GeneratePath(
		int numLesser,
		int numGreater,
		std::vector<Property*>* startingProperties)
{
	std::vector<Property*> lesserPossibleProperties = lesserProperties;
	std::vector<Property*> greaterPossibleProperties = greaterProperties;
	return GeneratePathInternal(numLesser,
			numGreater,
			lesserPossibleProperties,
			greaterPossibleProperties,
			startingProperties);
}

std::vector<std::unique_ptr<Talent>> PathGenerator::GeneratePathWithTraits(
		const std::vector<std::string>& desiredTraits,
		int numLesser,
		int numGreater)
{
	auto desiredProperties = PropertyRepository::GetInstance().GetPropertiesWithIds(lesserProperties, desiredTraits);
	if (!desiredProperties.empty())
	{
		return GeneratePath(numLesser, numGreater, &desiredProperties);
	}

	std::vector<std::unique_ptr<Talent>> result;
	result.push_back(std::move(std::unique_ptr<Talent>(nullptr)));
	return result;
}

std::vector<std::unique_ptr<Talent>> PathGenerator::GeneratePathInternal(
		int numLesser,
		int numGreater,
		std::vector<Property*> inOutLesserPossibleProperties,
		std::vector<Property*> inOutGreaterPossibleProperties,
		std::vector<Property*>* startingProperties)
{
	if (numLesser < 1 && numGreater <= 0)
	{
		return {};
	}
	std::vector<std::unique_ptr<Talent>> result;

	Property* startingProperty;
	startingProperty = startingProperties ?
			*SelectRandom(startingProperties->begin(), startingProperties->end()) :
			nullptr;
	result.push_back(GenerateRandomTalent(inOutLesserPossibleProperties,
				lesserDictionary,
				startingProperty));
	if (startingProperties)
	{
		GetIntersection(*startingProperties, inOutLesserPossibleProperties);
	}
	numLesser--;
	for (int i = 0; i < numLesser; i++)
	{
		startingProperty = startingProperties ?
				*SelectRandom(startingProperties->begin(), startingProperties->end()) :
				nullptr;
		std::unique_ptr<Talent> talent = GenerateRandomTalent(inOutLesserPossibleProperties,
				lesserDictionary,
				startingProperty);
		if (startingProperties)
		{
			GetIntersection(*startingProperties, inOutLesserPossibleProperties);
		}
		result.push_back(std::move(talent));
	}

	for (auto& talent : result)
	{
		IntersectionOfProperties(inOutGreaterPossibleProperties, *talent);
	}
	for (int i = 0; i < numGreater; i++)
	{
		startingProperty = startingProperties ?
				*SelectRandom(startingProperties->begin(), startingProperties->end()) :
				nullptr;
		std::unique_ptr<Talent> talent = GenerateRandomTalent(inOutGreaterPossibleProperties,
				greaterDictionary,
				startingProperty);
		if (startingProperties)
		{
			GetIntersection(*startingProperties, inOutGreaterPossibleProperties);
		}
		result.push_back(std::move(talent));
	}

	return std::move(result);
}

void PathGenerator::IntersectionOfProperties(std::vector<Property*>& inOutProperties, const Talent& talent) const
{
	for (auto& talentEntry : talent.talentEntries)
	{
		GetIntersection(inOutProperties,
				GetAllRelatedProperties(talentEntry.property, inOutProperties));
	}
}

void PathGenerator::IntersectionOfProperties(std::vector<Property*>& inOutProperties, const Property* property) const
{
	GetIntersection(inOutProperties,
			GetAllRelatedProperties(property, inOutProperties));
}

void PathGenerator::GetIntersection(std::vector<Property*>& a,
		const std::vector<Property*>& b) const
{
	for (auto it = a.begin(); it != a.end();)
	{
		if (!Statics::Contain(b, *it))
		{
			it = a.erase(it);
		}
		else
		{
			it++;
		}
	}
}

std::unique_ptr<Talent> PathGenerator::GenerateTalent(const std::vector<std::string>& desiredTraits,
		const bool bLesser) const
{
	const auto& properties = bLesser ? lesserProperties : greaterProperties;
	const auto* dictionary = bLesser ? lesserDictionary : greaterDictionary;
	auto desiredProperties = PropertyRepository::GetInstance().GetPropertiesWithIds(properties, desiredTraits);
	if (!desiredProperties.empty())
	{
		auto* desiredProperty = *SelectRandom(desiredProperties.begin(), desiredProperties.end());
		auto relatedProperties = GetAllRelatedProperties(desiredProperty, properties);
		return GenerateRandomTalent(relatedProperties, dictionary, desiredProperty);
	}

	return std::move(std::unique_ptr<Talent>(nullptr));
}

std::unique_ptr<Talent> PathGenerator::GenerateRandomTalent(
		std::vector<Property*>& inOutProperties,
		const TalentDictionary* dictionary,
		Property* startingProperty) const
{
	auto propertyRange = dictionary->GetPropertiesNumberRange();
	int numberOfProperties = GetRandomInt(propertyRange.first, propertyRange.second);

	std::vector<TalentEntry> tupleList;
	if (startingProperty)
	{
		GenerateRandomTalentTuple(inOutProperties, dictionary, numberOfProperties, tupleList, startingProperty);
		numberOfProperties--;
	}

	for (int i = 0; i < numberOfProperties; i++)
	{
		auto* property = GetRandomProperty(inOutProperties);

		GenerateRandomTalentTuple(inOutProperties, dictionary, numberOfProperties, tupleList, property);
	}

	return std::move(std::unique_ptr<Talent>(new Talent(tupleList)));
}

void PathGenerator::GenerateRandomTalentTuple(
		std::vector<Property*>& inOutProperties,
		const TalentDictionary* dictionary,
		const int numberOfProperties,
		std::vector<TalentEntry>& tupleList,
		Property* property) const
{
	auto possibleEntryIt = std::find_if(tupleList.begin(), tupleList.end(),
			[&] (const auto& e) { return *e.property == *property; });
	const bool alreadyHasProperty = possibleEntryIt != tupleList.end();

	auto terminalIds = property->ids;
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

Property* PathGenerator::GetRandomProperty(std::vector<Property*> properties) const
{
	return *SelectRandom(properties.begin(), properties.end());
}

template<typename Iter>
Iter PathGenerator::SelectRandom(Iter start, Iter end) const
{
	std::advance(start, GetRandomInt(0, std::distance(start, end) - 1));

	return start;
}

