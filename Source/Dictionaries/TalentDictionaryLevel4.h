#pragma once

#include "TalentDictionary.h"

class TalentDictionaryLevel4 : public TalentDictionary
{
public:
	TalentDictionaryLevel4();

	virtual std::pair<int, int> GetPropertiesNumberRange() const override { return {1, 2}; }
};

