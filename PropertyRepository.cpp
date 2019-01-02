#include "stdafx.h"
#include "PropertyRepository.h"
#include "TraitRepository.h"

PropertyRepository::PropertyRepository()
{
	traitRepository = &TraitRepository::GetInstance();
	std::vector<TraitParent*> traitList = traitRepository->possibleTraits;
	for (auto* traitParent : traitList)
	{
		allProperties.push_back(std::unique_ptr<Property>(new Property(traitParent)));
	}

	std::vector<Property*> properties;
	for (const auto& ptr : allProperties)
	{
		properties.push_back(ptr.get());
	}

	auto level2 = GetPropertiesWithIds({"attributes"});
	auto level7 = GetPropertiesWithoutIds(properties, {"attributes"});
	auto level4 = GetPropertiesWithoutIds(level7, {"weaponType"});
	auto level1 = GetPropertiesWithoutIds(level4, {"damageType", "healingType", "damageType1"});
	auto level9 = GetPropertiesWithoutIds(level1, {"specCriticalChance", "specCriticalEffect"});
	level1Properties.insert(std::end(level1Properties), std::begin(level1), std::end(level1));
	level3Properties.insert(std::end(level3Properties), std::begin(level1), std::end(level1));

	level2Properties.insert(std::end(level2Properties), std::begin(level2), std::end(level2));

	level4Properties.insert(std::end(level4Properties), std::begin(level4), std::end(level4));
	level6Properties.insert(std::end(level6Properties), std::begin(level4), std::end(level4));

	level5Properties.insert(std::end(level5Properties), std::begin(level2), std::end(level2));

	level7Properties.insert(std::end(level7Properties), std::begin(level7), std::end(level7));
	level8Properties.insert(std::end(level8Properties), std::begin(level7), std::end(level7));

	level9Properties.insert(std::end(level9Properties), std::begin(level9), std::end(level9));
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
					const auto& traitIds = traitRepository->allTraitsIds[p->trait->index];
					return std::find(traitIds.begin(), traitIds.end(), id) != traitIds.end();
				}),
				result.end());
	}
	std::sort(result.begin(), result.end());

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
			for (auto& traitId : traitRepository->allTraitsIds[property->trait->index])
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

