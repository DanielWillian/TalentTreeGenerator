#pragma once

#include "TalentDictionary.h"

class TalentDictionaryLevel2 : public TalentDictionary
{
public:
	TalentDictionaryLevel2();

	virtual int GetFloatPrecision() const override { return 1; }
};

