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

	Property::DistanceBetweenProperties(directDamage, directHealing);

	PropertyRepository propertyRepository;

	system("pause");
	return 0;
}

