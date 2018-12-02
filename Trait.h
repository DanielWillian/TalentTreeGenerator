#pragma once

#include <string>
#include <list>

class Trait
{
public:
	virtual bool HasChildren() const { return false; }
	virtual std::list<Trait*> GetChildren() const { return std::list<Trait*>(); }

	virtual std::list<int> GetAllTraitIds() const
	{
		std::list<int> result;
		result.push_back(id);
		for (Trait* trait : GetChildren())
		{
			result.splice(result.end(), trait->GetAllTraitIds());
		}
		return result;
	}

public:
	int id;
};

class TraitParent : public Trait
{
public:
	virtual bool HasChildren() const override { return true; }
	virtual std::list<Trait*> GetChildren() const override { return subTraits; }

public:
	std::list<Trait*> subTraits;
};

class TraitChild : public Trait
{
};

