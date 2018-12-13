#pragma once

#include "Property.h"
#include "TraitRepository.h"
#include <unordered_set>

class PropertyRepository
{
public:
	PropertyRepository();

	std::vector<Property*> GetPropertiesWithIds(const std::vector<std::string>& ids);

private:
	std::vector<Property*> GetPropertiesWithoutIds(const std::vector<Property*>& properties,
			const std::vector<std::string>& ids);

public:
	std::vector<Property*> allProperties;

	std::unordered_set<Property*> level1Properties;

	std::unordered_set<Property*> level3Properties;

	TraitRepository traitRepository;
};

