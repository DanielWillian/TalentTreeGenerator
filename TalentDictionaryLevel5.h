#pragma once

#include "TalentDictionary.h"

class TalentDictionaryLevel5 : public TalentDictionary
{
public:
	TalentDictionaryLevel5();

	virtual int GetFloatPrecision() const override { return 1; }
};

