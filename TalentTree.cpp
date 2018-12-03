// TalentTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TraitRepository.h"
#include "Property.h"
#include "PropertyRepository.h"
#include <iostream>

int main()
{
	TraitRepository traitRep;
	Property directDamage(std::vector<TraitParent*>({ &traitRep.directDamageAffect }));
	Property directHealing(std::vector<TraitParent*>({ &traitRep.directHealingAffect }));

	//Property::DistanceBetweenProperties(directDamage, directHealing);

	PropertyRepository propertyRepository;
	std::vector<TraitParent*> traitList = propertyRepository.possibleTraits;

	for (size_t i = 0; i < traitList.size(); i++)
	{
		std::cout << i << " " << traitList[i]->toString() << std::endl;
	}

	Property property13({ traitList[0] });
	Property property14({ traitList[115] });
	Property::DistanceBetweenProperties(property13, property14);

	system("pause");
	return 0;
}

