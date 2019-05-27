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

	const PropertyDictEntry& GetDictEntry(const std::string& id)
	{
		return **std::find_if(entries.begin(), entries.end(), [&id](const auto& e) { return e->id == id; });
	}

public:
	static const int TERMINAL = 0;
	static const int ALTERNATIVES = 1;
	static const int CONCATENATIONS = 2;

private:
	std::vector<std::unique_ptr<PropertyDictEntry>> entries;
};

