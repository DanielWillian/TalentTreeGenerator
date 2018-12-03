#pragma once

#include "Trait.h"
#include "TraitConstants.h"
#include "Property.h"

class PropertyNode
{
public:
	PropertyNode(const int inId, const std::vector<std::vector<PropertyNode*>>& inPropertySubOptions)
	{
		id = inId;
		propertySubOptions = inPropertySubOptions;
	}
	PropertyNode() {}

	int id;
	std::vector<std::vector<PropertyNode*>> propertySubOptions;
};

class PropertyRepository
{
public:
	PropertyRepository();

private:
	void GenerateAllProperties();

	std::vector<Trait*> GenerateTraitFromPropertyNode(PropertyNode* propertyNode);

	template<class T>
	std::vector<std::vector<T*>> PermuteLists(const std::vector<std::vector<T*>>& listOfLists);

	template<class T>
	std::vector<std::vector<T>> PermuteLists(const std::vector<std::vector<T>>& listOfLists);

	PropertyNode masterNode;
	std::vector<Property> possibleProperties;
};

