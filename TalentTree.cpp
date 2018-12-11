// TalentTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TraitRepository.h"
#include "Property.h"
#include <iostream>

int main()
{
	TraitRepository traitRep;
	std::vector<TraitParent*> traitList = traitRep.possibleTraits;

	for (size_t i = 0; i < traitList.size(); i++)
	{
		std::cout << i << " " << traitList[i]->toString() << std::endl;
	}

	Property property1({ traitRep.GetTraitsWithIds({ "allDamage", "singleTarget" })[0] });
	Property property2({ traitRep.GetTraitsWithIds({ "allHealing", "singleTarget" })[0] });
	std::cout << Property::DistanceBetweenProperties(property1, property2) << std::endl;

	system("pause");
	return 0;
}

