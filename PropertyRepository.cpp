#include "stdafx.h"
#include "PropertyRepository.h"

PropertyRepository::PropertyRepository()
{
	std::vector<TraitParent*> traitList = traitRepository.possibleTraits;
	for (auto* traitParent : traitList)
	{
		allProperties.push_back(new Property(traitParent));
	}
}


std::vector<Property*> PropertyRepository::GetPropertiesWithIds(const std::vector<std::string>& ids)
{
	std::vector<Property*> result;

	for (auto* property : allProperties)
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
			result.push_back(property);
		}
	}

	return result;
}

