#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <memory>

class PropertyDictEntry
{
public:
	PropertyDictEntry(const std::string& inId,
			const std::vector<std::string>& inDamageTypes,
			const std::vector<std::string>& inWeaponTypes)
		: id(inId), damageTypes(inDamageTypes), weaponTypes(inWeaponTypes)
	{
	}

public:
	std::string id;
	std::vector<std::string> damageTypes;
	std::vector<std::string> weaponTypes;
};

class PropertyDictionary
{
public:
	PropertyDictionary();

public:
	std::vector<PropertyDictEntry*> entries;

private:
	std::vector<std::unique_ptr<PropertyDictEntry>> managedEntries;
};

