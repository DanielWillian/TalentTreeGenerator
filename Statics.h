#pragma once

#include <vector>
#include <algorithm>

class Statics
{
public:
	template<typename T>
	static bool ContainAll(const std::vector<T>& vec, const std::vector<T>& elems)
	{
		bool result = true;

		for (const T& t : elems)
		{
			result &= Contain(vec, t);
		}

		return result;
	}

	template<typename T>
	static bool ContainAny(const std::vector<T>& vec, const std::vector<T>& elems)
	{
		bool result = false;

		for (const T& t : elems)
		{
			result |= Contain(vec, t);
		}

		return result;
	}

	template<typename T>
	static bool Contain(const std::vector<T>& vec, const T& elem)
	{
		return std::binary_search(vec.begin(), vec.end(), elem);
	}
};

