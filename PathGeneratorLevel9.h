#pragma once

#include "PathGenerator.h"
#include "Property.h"
#include "Talent.h"
#include "TalentDictionary.h"
#include <vector>
#include <memory>

class PathGeneratorLevel9 : public PathGenerator
{
public:
	PathGeneratorLevel9(const std::vector<Property*>& inLesserProperties,
			TalentDictionary* inLesserDictionary,
			const std::vector<Property*>& inGreaterProperties,
			TalentDictionary* inGreaterDictionary)
			: PathGenerator(inLesserProperties, inLesserDictionary,
					inGreaterProperties, inGreaterDictionary)
	{
	}

	std::vector<std::unique_ptr<Talent>> GeneratePath(int numLesser, int numGreater) override;
};

