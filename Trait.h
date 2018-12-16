#pragma once

#include <string>
#include <vector>
#include <iterator>

class Trait
{
public:
	Trait(const std::string inId)
	{
		id = inId;
	}
	Trait() {}

	virtual bool HasChildren() const { return false; }
	virtual std::vector<Trait*>& GetChildren() { return subTraits; }

	virtual std::vector<std::string> GetAllTraitIds()
	{
		std::vector<std::string> result;
		result.push_back(id);
		for (Trait* trait : GetChildren())
		{
			std::vector<std::string> childTraits = trait->GetAllTraitIds();
			std::move(childTraits.begin(), childTraits.end(), std::back_inserter(result));
		}
		return result;
	}

	virtual std::vector<std::string> GetTerminalTraitsId()
	{
		std::vector<std::string> result;
		if (!HasChildren())
		{
			result.push_back(id);
		}
		else
		{
			for (Trait* trait : GetChildren())
			{
				std::vector<std::string> childTraits = trait->GetTerminalTraitsId();
				std::move(childTraits.begin(), childTraits.end(), std::back_inserter(result));
			}
		}
		return result;
	}

	virtual Trait* GetTraitWithId(const std::string& id)
	{
		if (this->id == id)
		{
			return this;
		}
		else
		{
			for (Trait* trait : subTraits)
			{
				Trait* possibleTrait = trait->GetTraitWithId(id);
				if (possibleTrait)
				{
					return possibleTrait;
				}
			}
		}
		return nullptr;
	}

	virtual std::string toString() const
	{
		std::string out = "( " + id;
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
	std::string id;
	std::vector<Trait*> subTraits;
};

class TraitParent : public Trait
{
public:
	TraitParent(const std::string inId, const std::vector<Trait*>& inSubTraits) : Trait(inId)
	{
		subTraits = inSubTraits;
	}
	TraitParent() {}

	virtual bool HasChildren() const override { return true; }
};

class TraitChild : public Trait
{
public:
	TraitChild(const std::string inId) : Trait(inId) {}
	TraitChild() {}
};

