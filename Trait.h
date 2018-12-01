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
};

class TraitChild : public Trait
{
private:
	std::string qualifier;
};

