#pragma once

#include <string>
#include <vector>
#include <iterator>

class Trait
{
public:
	Trait(const int inId)
	{
		id = inId;
	}
	Trait() {}

	virtual bool HasChildren() const { return false; }
	virtual std::vector<Trait*>& GetChildren() { return subTraits; }

	virtual std::vector<int> GetAllTraitIds()
	{
		std::vector<int> result;
		result.push_back(id);
		for (Trait* trait : GetChildren())
		{
			std::vector<int> childTraits = trait->GetAllTraitIds();
			std::move(childTraits.begin(), childTraits.end(), std::back_inserter(result));
		}
		return result;
	}

	virtual std::string toString() const
	{
		std::string out = "( " + std::to_string(id);
		if (HasChildren())
		{
			out += " { ";
			for (Trait* subTrait : subTraits)
			{
				out += subTrait->toString() + " ";
			}
			out += "}";
		}
		out += " )";
		return out;
	}

public:
	int id;
	std::vector<Trait*> subTraits;
};

class TraitParent : public Trait
{
public:
	TraitParent(const int inId, const std::vector<Trait*>& inSubTraits) : Trait(inId)
	{
		subTraits = inSubTraits;
	}
	TraitParent() {}

	virtual bool HasChildren() const override { return true; }
};

class TraitChild : public Trait
{
public:
	TraitChild(const int inId) : Trait(inId) {}
	TraitChild() {}
};

