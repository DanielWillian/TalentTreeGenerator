#pragma once

#include "Property.h"
#include "Talent.h"
#include "TalentDictionary.h"
#include <vector>

class PathGenerator
{
public:
	PathGenerator(const std::vector<Property*>& inLesserProperties,
			TalentDictionary* inLesserDictionary,
			const std::vector<Property*>& inGreaterProperties,
			TalentDictionary* inGreaterDictionary)
			: lesserProperties(inLesserProperties),
			lesserDictionary(inLesserDictionary),
			greaterProperties(inGreaterProperties),
			greaterDictionary(inGreaterDictionary)
	{
	}

	Property* GetRandomProperty(std::vector<Property*> properties) const;

	std::vector<Property*> GetAllRelatedProperties(const Property* property,
			const std::vector<Property*>& properties) const;

	std::vector<Talent> GeneratePath(int numLesser, int numGreater);

private:
	Talent GenerateRandomTalent(std::vector<Property*>& inOutProperties, const TalentDictionary* dictionary) const;

	template<typename Iter>
	Iter SelectRandom(Iter start, Iter end) const;

	int GetRandomInt(const int min, const int max) const;

	float GetRandomFloat(const float min, const float max) const;

	void IntersectionOfProperties(std::vector<Property*>& inOutProperties, const Talent& talent) const;

	void IntersectionOfProperties(std::vector<Property*>& inOutProperties, const Property* property) const;

	void GetIntersection(std::vector<Property*>& a,
			const std::vector<Property*>& b) const;

public:
	std::vector<Property*> lesserProperties;

	TalentDictionary* lesserDictionary;

	std::vector<Property*> greaterProperties;

	TalentDictionary* greaterDictionary;
};

