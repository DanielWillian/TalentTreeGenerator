#pragma once

#include "TalentDictionary.h"

class TalentDictionaryLevel3 : public TalentDictionary
{
public:
	TalentDictionaryLevel3();

	virtual std::pair<int, int> GetPropertiesNumberRange() const override { return {3, 3}; }
};

