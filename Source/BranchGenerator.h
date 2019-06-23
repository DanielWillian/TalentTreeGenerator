#pragma once

#include "Models/Property.h"
#include "Models/Talent.h"
#include "Dictionaries/TalentDictionary.h"
#include <vector>
#include <memory>

class BranchGenerator
{
public:
	BranchGenerator(const std::vector<Property*>& inLesserProperties,
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
			const std::vector<Property*>& properties,
			const int distanceThreshold) const;

	virtual std::vector<std::unique_ptr<Talent>> GenerateBranch(
			int numLesser,
			int numGreater,
			std::vector<Property*>* startingProperties = nullptr);

	virtual std::vector<std::unique_ptr<Talent>> GenerateBranchWithTraits(
			const std::vector<std::string>& desiredTraits,
			int numLesser,
			int numGreater);

	virtual std::unique_ptr<Talent> GenerateTalent(const std::vector<std::string>& desiredTraits,
			const bool bLesser) const;

protected:
	virtual std::unique_ptr<Talent> GenerateRandomTalent(
			std::vector<Property*> inProperties,
			const TalentDictionary* dictionary,
			Property* startingProperty = nullptr) const;

	template<typename Iter>
	Iter SelectRandom(Iter start, Iter end) const;

	int GetRandomInt(const int min, const int max) const;

	float GetRandomFloat(const float min, const float max) const;

	void IntersectionOfProperties(std::vector<Property*>& inOutProperties,
			const Talent& talent,
			const int distanceThreshold) const;

	void IntersectionOfProperties(std::vector<Property*>& inOutProperties,
			const Property* property,
			const int distanceThreshold) const;

	void GetIntersection(std::vector<Property*>& a,
			const std::vector<Property*>& b) const;

	virtual void GenerateRandomTalentTuple(
			std::vector<Property*>& inOutProperties,
			const TalentDictionary* dictionary,
			const int numberOfProperties,
			std::vector<TalentEntry>& tupleList,
			Property* property) const;

	virtual std::vector<std::unique_ptr<Talent>> GenerateBranchInternal(
			int numLesser,
			int numGreater,
			std::vector<Property*> inLesserPossibleProperties,
			std::vector<Property*> inGreaterPossibleProperties,
			std::vector<Property*>* startingProperties = nullptr);

public:
	std::vector<Property*> lesserProperties;

	TalentDictionary* lesserDictionary;

	std::vector<Property*> greaterProperties;

	TalentDictionary* greaterDictionary;
};

