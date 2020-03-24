#include "BranchGenerator.h"
#include "PropertyDistance.h"
#include "PropertyRepository.h"
#include "Utils/Random.h"
#include "Models/Talent.h"
#include "Models/TalentEntry.h"
#include "Utils/Statics.h"
#include <cmath>
#include <limits>
#include <random>
#include <iterator>

std::vector<Property*> BranchGenerator::GetAllRelatedProperties(
		const Property* property,
		const std::vector<Property*>& properties,
		const int distanceThreshold) const
{
	std::vector<Property*> result;

	for (auto* otherProperty : properties)
	{
		if (PropertyDistance::GetInstance().DistanceBetweenProperties(*property, *otherProperty) <=
				distanceThreshold)
		{
			result.push_back(otherProperty);
		}
	}

	return result;
}

std::vector<std::unique_ptr<Talent>> BranchGenerator::GenerateBranch(
		int numLesser,
		int numGreater,
		std::vector<Property*>* startingProperties) const
{
	std::vector<Property*> lesserPossibleProperties = lesserProperties;
	std::vector<Property*> greaterPossibleProperties = greaterProperties;
	return GenerateBranchInternal(numLesser,
			numGreater,
			lesserPossibleProperties,
			greaterPossibleProperties,
			startingProperties);
}

std::vector<std::unique_ptr<Talent>> BranchGenerator::GenerateBranchWithTraits(
		const std::vector<std::string>& desiredTraits,
		int numLesser,
		int numGreater) const
{
	auto desiredProperties = PropertyRepository::GetInstance().GetPropertiesWithIds(lesserProperties, desiredTraits);
	if (!desiredProperties.empty())
	{
		return GenerateBranch(numLesser, numGreater, &desiredProperties);
	}

	std::vector<std::unique_ptr<Talent>> result;
	result.push_back(std::move(std::unique_ptr<Talent>(nullptr)));
	return result;
}

std::vector<std::unique_ptr<Talent>> BranchGenerator::GenerateBranchInternal(
		int numLesser,
		int numGreater,
		std::vector<Property*> inLesserPossibleProperties,
		std::vector<Property*> inGreaterPossibleProperties,
		std::vector<Property*>* startingProperties) const
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
	auto startingTalent = GenerateRandomTalent(inLesserPossibleProperties,
				lesserDictionary,
				startingProperty);
	IntersectionOfProperties(inLesserPossibleProperties, *startingTalent.get(), PropertyDistance::SOMEWHAT_SIMILAR);
	result.push_back(std::move(startingTalent));
	numLesser--;
	for (int i = 0; i < numLesser; i++)
	{
		std::unique_ptr<Talent> talent = GenerateRandomTalent(inLesserPossibleProperties,
				lesserDictionary,
				nullptr);
		IntersectionOfProperties(inLesserPossibleProperties, *talent.get(), PropertyDistance::SOMEWHAT_SIMILAR);
		result.push_back(std::move(talent));
	}

	for (auto& talent : result)
	{
		IntersectionOfProperties(inGreaterPossibleProperties, *talent, PropertyDistance::SOMEWHAT_SIMILAR);
	}
	for (int i = 0; i < numGreater; i++)
	{
		std::unique_ptr<Talent> talent = GenerateRandomTalent(inGreaterPossibleProperties,
				greaterDictionary,
				nullptr);
		IntersectionOfProperties(inGreaterPossibleProperties, *talent.get(), PropertyDistance::SOMEWHAT_SIMILAR);
		result.push_back(std::move(talent));
	}

	return std::move(result);
}

void BranchGenerator::IntersectionOfProperties(
		std::vector<Property*>& inOutProperties,
		const Talent& talent,
		const int distanceThreshold
		) const
{
	for (auto& talentEntry : talent.talentEntries)
	{
		GetIntersection(inOutProperties,
				GetAllRelatedProperties(talentEntry.property, inOutProperties, distanceThreshold));
	}
}

void BranchGenerator::IntersectionOfProperties(
		std::vector<Property*>& inOutProperties,
		const Property* property,
		const int distanceThreshold
		) const
{
	GetIntersection(inOutProperties,
			GetAllRelatedProperties(property, inOutProperties, distanceThreshold));
}

void BranchGenerator::GetIntersection(std::vector<Property*>& a,
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

std::unique_ptr<Talent> BranchGenerator::GenerateTalent(const std::vector<std::string>& desiredTraits,
		const bool bLesser) const
{
	const auto& properties = bLesser ? lesserProperties : greaterProperties;
	const auto* dictionary = bLesser ? lesserDictionary : greaterDictionary;
	auto desiredProperties = PropertyRepository::GetInstance().GetPropertiesWithIds(properties, desiredTraits);
	if (!desiredProperties.empty())
	{
		auto* desiredProperty = *SelectRandom(desiredProperties.begin(), desiredProperties.end());
		auto relatedProperties = GetAllRelatedProperties(desiredProperty, properties, PropertyDistance::SIMILAR);
		return GenerateRandomTalent(relatedProperties, dictionary, desiredProperty);
	}

	return std::move(std::unique_ptr<Talent>(nullptr));
}

std::unique_ptr<Talent> BranchGenerator::GenerateRandomTalent(
		std::vector<Property*> inProperties,
		const TalentDictionary* dictionary,
		Property* startingProperty) const
{
	auto propertyRange = dictionary->GetPropertiesNumberRange();
	int numberOfProperties = GetRandomInt(propertyRange.first, propertyRange.second);

	std::vector<TalentEntry> tupleList;
	if (startingProperty)
	{
		GenerateRandomTalentTuple(inProperties, dictionary, numberOfProperties, tupleList, startingProperty);
		numberOfProperties--;
	}

	for (int i = 0; i < numberOfProperties; i++)
	{
		auto* property = GetRandomProperty(inProperties);

		GenerateRandomTalentTuple(inProperties, dictionary, numberOfProperties, tupleList, property);
	}

	return std::move(std::unique_ptr<Talent>(new Talent(tupleList)));
}

void BranchGenerator::GenerateRandomTalentTuple(
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
		IntersectionOfProperties(inOutProperties, property, PropertyDistance::SIMILAR);
	}
	else
	{
		possibleEntryIt->value = talentValue;
	}
}

int BranchGenerator::GetRandomInt(const int min, const int max) const
{
	return Random::GetInstance().GetRandomInt(min, max);
}

float BranchGenerator::GetRandomFloat(const float min, const float max) const
{
	return Random::GetInstance().GetRandomFloat(min, max);
}

Property* BranchGenerator::GetRandomProperty(std::vector<Property*> properties) const
{
	return *SelectRandom(properties.begin(), properties.end());
}

template<typename Iter>
Iter BranchGenerator::SelectRandom(Iter start, Iter end) const
{
	std::advance(start, GetRandomInt(0, (int) (std::distance(start, end) - 1)));

	return start;
}

