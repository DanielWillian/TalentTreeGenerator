#pragma once

#include "Property.h"
#include "Talent.h"
#include "TalentDictionary.h"
#include <unordered_set>

class PathGenerator
{
public:
	PathGenerator(const std::unordered_set<Property*>& inLesserProperties,
			TalentDictionary* inLesserDictionary,
			const std::unordered_set<Property*>& inGreaterProperties,
			TalentDictionary* inGreaterDictionary)
			: lesserProperties(inLesserProperties),
			lesserDictionary(inLesserDictionary),
			greaterProperties(inGreaterProperties),
			greaterDictionary(inGreaterDictionary)
	{
	}

	Talent GenerateRandomTalent(const bool lesser) const;

	Property* GetRandomProperty(std::unordered_set<Property*> properties) const;

	std::unordered_set<Property*> GetAllRelatedProperties(const Property* property,
			std::unordered_set<Property*> properties) const;

public:
	std::unordered_set<Property*> lesserProperties;

	TalentDictionary* lesserDictionary;

	std::unordered_set<Property*> greaterProperties;

	TalentDictionary* greaterDictionary;
};

