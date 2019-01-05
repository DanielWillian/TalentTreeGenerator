#include "stdafx.h"
#include "PathGeneratorLevel9.h"
#include "PropertyDistance.h"
#include "Talent.h"
#include "TalentEntry.h"
#include "Statics.h"
#include <cmath>
#include <limits>
#include <random>
#include <iterator>

std::vector<std::unique_ptr<Talent>> PathGeneratorLevel9::GeneratePath(
		int numLesser,
		int numGreater,
		Property* startingProperty)
{
	if (numLesser < 1 && numGreater >= 0)
	{
		return {};
	}

	Property* beneficial = nullptr;
	Property* detrimental = nullptr;
	while ((!beneficial || !detrimental) && beneficial == detrimental)
	{
		beneficial = GetRandomProperty(lesserProperties);
		auto related = GetAllRelatedProperties(beneficial, lesserProperties);
		std::vector<Property*> difference;
		std::set_difference(lesserProperties.begin(), lesserProperties.end(),
				related.begin(), related.end(), std::inserter(difference, std::begin(difference)));
		detrimental = GetRandomProperty(difference);
	}

	auto beneficialTerminalIds = beneficial->trait->GetTerminalTraitsId();
	auto beneficialDictEntries = lesserDictionary->GetDictEntries(beneficialTerminalIds[0]);
	beneficialDictEntries.erase(std::remove_if(beneficialDictEntries.begin(), beneficialDictEntries.end(),
			[&] (const auto* entry)
			{
				return entry->type != TalentDictionary::BENEFICIAL;
			}),
			beneficialDictEntries.end());
	TalentDictEntry* beneficialDictEntry = *SelectRandom(beneficialDictEntries.begin(), beneficialDictEntries.end());

	auto detrimentalTerminalIds = detrimental->trait->GetTerminalTraitsId();
	auto detrimentalDictEntries = lesserDictionary->GetDictEntries(detrimentalTerminalIds[0]);
	detrimentalDictEntries.erase(std::remove_if(detrimentalDictEntries.begin(), detrimentalDictEntries.end(),
			[&] (const auto* entry)
			{
				return entry->type != TalentDictionary::DETRIMENTAL;
			}),
			detrimentalDictEntries.end());
	TalentDictEntry* detrimentalDictEntry = *SelectRandom(detrimentalDictEntries.begin(), detrimentalDictEntries.end());

	const int dictPrecision = lesserDictionary->GetFloatPrecision();
	const float randomValue = GetRandomFloat(0.0f, 1.0f);
	float beneficialValue = beneficialDictEntry->values.first + randomValue *
		(beneficialDictEntry->values.second - beneficialDictEntry->values.first);
	beneficialValue = (roundf((beneficialValue - 1) * dictPrecision)
			/ dictPrecision) + 1;
	float detrimentalValue = detrimentalDictEntry->values.first + randomValue *
		(detrimentalDictEntry->values.second - detrimentalDictEntry->values.first);
	detrimentalValue = (roundf((detrimentalValue - 1) * dictPrecision)
			/ dictPrecision) + 1;

	std::vector<TalentEntry> tupleList;
	tupleList.push_back({beneficial, beneficialDictEntry->modifier, beneficialValue});
	tupleList.push_back({detrimental, detrimentalDictEntry->modifier, detrimentalValue});

	std::vector<std::unique_ptr<Talent>> result;
	result.push_back(std::unique_ptr<Talent>(new Talent(tupleList)));
	return std::move(result);
}

