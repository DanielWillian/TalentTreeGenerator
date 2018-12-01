#pragma once

#include <string>
#include <list>

class Trait
{
};

class TraitParent : public Trait
{
private:
	std::list<Trait> subTraits;
	std::string name;
};

class TraitChild : public Trait
{
private:
	std::string qualifier;
};

