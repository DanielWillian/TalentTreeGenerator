#pragma once

#include "TalentDictionary.h"

class TalentDictionaryLevel7 : public TalentDictionary
{
public:
	TalentDictionaryLevel7();

	virtual std::pair<int, int> GetPropertiesNumberRange() const override { return {2, 3}; }
};

