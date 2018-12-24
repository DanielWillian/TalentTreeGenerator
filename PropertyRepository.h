#pragma once

#include "Property.h"
#include "TraitRepository.h"
#include <unordered_set>
#include <memory>

class PropertyRepository
{
public:
	PropertyRepository();

	std::vector<Property*> GetPropertiesWithIds(const std::vector<std::string>& ids);

private:
	std::vector<Property*> GetPropertiesWithoutIds(const std::vector<Property*>& properties,
			const std::vector<std::string>& ids);

public:
	std::vector<std::unique_ptr<Property>> allProperties;

	std::unordered_set<Property*> level1Properties;

	std::unordered_set<Property*> level2Properties;

	std::unordered_set<Property*> level3Properties;

	std::unordered_set<Property*> level4Properties;

	std::unordered_set<Property*> level5Properties;

	std::unordered_set<Property*> level6Properties;

	std::unordered_set<Property*> level7Properties;

	TraitRepository traitRepository;
};

