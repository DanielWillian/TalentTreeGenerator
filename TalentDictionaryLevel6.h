#pragma once

#include "TalentDictionary.h"

class TalentDictionaryLevel6 : public TalentDictionary
{
public:
	TalentDictionaryLevel6();

	virtual std::pair<int, int> GetPropertiesNumberRange() const override { return {3, 4}; }
};

