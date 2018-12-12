#pragma once

#include "Property.h"
#include "TraitRepository.h"

class PropertyRepository
{
public:
	PropertyRepository();

	std::vector<Property*> GetPropertiesWithIds(const std::vector<std::string>& ids);

public:
	std::vector<Property*> allProperties;

	TraitRepository traitRepository;
};

