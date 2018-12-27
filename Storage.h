#pragma once

#include <unordered_map>

class Storage
{
public:
	static Storage& GetInstance()
	{
		static Storage instance;
		return instance;
	}

	Storage(Storage const&) = delete;
	void operator=(Storage const&) = delete;

	void SavePropertiesDist(const std::unordered_map<int, std::unordered_map<int, int>>& propertiesDist) const;

	std::unordered_map<int, std::unordered_map<int, int>> LoadPropertiesDist() const;

private:
	Storage() {}
};

