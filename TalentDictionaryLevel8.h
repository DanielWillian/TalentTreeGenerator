#pragma once

#include "TalentDictionary.h"

class TalentDictionaryLevel8 : public TalentDictionary
{
public:
	TalentDictionaryLevel8();

	virtual std::pair<int, int> GetPropertiesNumberRange() const override { return {3, 4}; }
};

