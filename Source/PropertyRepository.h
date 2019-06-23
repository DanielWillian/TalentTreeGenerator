#pragma once

#include "Models/Property.h"
#include "Dictionaries/PropertyDictionary.h"
#include <unordered_set>
#include <memory>

class PropertyRepository
{
public:
	static PropertyRepository& GetInstance()
	{
		static PropertyRepository instance;
		return instance;
	}

	PropertyRepository(PropertyRepository const&) = delete;
	void operator=(PropertyRepository const&) = delete;

	std::vector<Property*> GetPropertiesWithIds(const std::vector<Property*>& properties,
			const std::vector<std::string>& ids) const;

private:
	PropertyRepository();

	std::vector<Property*> GeneratePropertiesFromDictionary(const PropertyDictionary& dict);

	std::vector<Property*> GetPropertiesWithoutIds(const std::vector<Property*>& properties,
			const std::vector<std::string>& ids) const;

public:
	std::vector<std::unique_ptr<Property>> allProperties;

	std::vector<std::string> baseProperties;

	std::vector<std::string> damageTypes;

	std::vector<std::string> weaponTypes;

	std::vector<Property*> level1Properties;

	std::vector<Property*> level2Properties;

	std::vector<Property*> level3Properties;

	std::vector<Property*> level4Properties;

	std::vector<Property*> level5Properties;

	std::vector<Property*> level6Properties;

	std::vector<Property*> level7Properties;

	std::vector<Property*> level8Properties;

	std::vector<Property*> level9Properties;

private:
	PropertyDictionary propertyDictionary;
};

