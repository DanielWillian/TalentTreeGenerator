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

	Property property13({ traitList[0] });
	Property property14({ traitList[115] });
	std::cout << Property::DistanceBetweenProperties(property13, property14) << std::endl;

	system("pause");
	return 0;
}

