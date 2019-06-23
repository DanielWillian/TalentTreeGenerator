#pragma once

#include "TalentDictionary.h"

class TalentDictionaryLevel9 : public TalentDictionary
{
public:
	TalentDictionaryLevel9();

	virtual std::pair<int, int> GetPropertiesNumberRange() const override { return {1, 1}; }
};

