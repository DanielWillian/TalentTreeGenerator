#include "stdafx.h"
#include "PropertyRepository.h"

PropertyRepository::PropertyRepository()
{
	std::vector<TraitParent*> traitList = traitRepository.possibleTraits;
	for (auto* traitParent : traitList)
	{
		allProperties.push_back(std::unique_ptr<Property>(new Property(traitParent)));
	}

	std::vector<Property*> properties;
	for (const auto& ptr : allProperties)
	{
		properties.push_back(ptr.get());
	}

	auto level1 = GetPropertiesWithoutIds(properties, {"weaponType", "damageType", "healingType",
			"damageType1", "attributes"});
	level1Properties.insert(std::begin(level1), std::end(level1));
	level3Properties.insert(std::begin(level1), std::end(level1));

	auto level2 = GetPropertiesWithIds({"attributes"});
	level2Properties.insert(std::begin(level2), std::end(level2));

	auto level4 = GetPropertiesWithoutIds(properties, {"weaponType", "attributes"});
	level4Properties.insert(std::begin(level4), std::end(level4));
	level6Properties.insert(std::begin(level4), std::end(level4));

	level5Properties.insert(std::begin(level2), std::end(level2));
}

std::vector<Property*> PropertyRepository::GetPropertiesWithoutIds(
		const std::vector<Property*>& properties,
		const std::vector<std::string>& ids)
{
	auto result = properties;

	for (const auto& id : ids)
	{
		result.erase(std::remove_if(result.begin(), result.end(),
				[&](auto* p) -> bool
				{
					const auto& traitIds = p->trait->GetAllTraitIds();
					return std::find(traitIds.begin(), traitIds.end(), id) != traitIds.end();
				}),
				result.end());
	}

	return result;
}

std::vector<Property*> PropertyRepository::GetPropertiesWithIds(const std::vector<std::string>& ids)
{
	std::vector<Property*> result;

	for (const auto& property : allProperties)
	{
		bool bFound = false;
		for (auto& id : ids)
		{
			bFound = false;
			for (auto& traitId : property->trait->GetAllTraitIds())
			{
				if (id == traitId)
				{
					bFound = true;
					break;
				}
			}
			if (!bFound)
			{
				break;
			}
		}
		if (bFound)
		{
			result.push_back(property.get());
		}
	}

	return result;
}

