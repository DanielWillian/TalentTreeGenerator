#pragma once

#include <chrono>
#include <vector>

class TimeRepository {
public:
	static TimeRepository& getInstance()
	{
		static TimeRepository instance;
		return instance;
	}

	TimeRepository(TimeRepository const&) = delete;
	void operator=(TimeRepository const&) = delete;

	std::chrono::microseconds getInitializationTime() const;
	std::vector<std::chrono::microseconds> getTalentTreeTimes() const;
	std::vector<std::chrono::microseconds> getBranchTimes() const;
	std::vector<std::chrono::microseconds> getBranch1Times() const;
	std::vector<std::chrono::microseconds> getBranch4Times() const;
	std::vector<std::chrono::microseconds> getBranch7Times() const;

	TimeRepository& setInitializationTime(const std::chrono::microseconds& newInitializationTime);
	TimeRepository& setTalentTreeTimes(const std::vector<std::chrono::microseconds>& newTalentTreeTimes);
	TimeRepository& setBranchTimes(const std::vector<std::chrono::microseconds>& newBranchTimes);
	TimeRepository& setBranch1Times(const std::vector<std::chrono::microseconds>& newBranch1Times);
	TimeRepository& setBranch4Times(const std::vector<std::chrono::microseconds>& newBranch4Times);
	TimeRepository& setBranch7Times(const std::vector<std::chrono::microseconds>& newBranch7Times);

	TimeRepository& addTalentTreeTime(const std::chrono::microseconds& talentTreeTime);
	TimeRepository& addBranchTime(const std::chrono::microseconds& branchTime);

private:
	TimeRepository();

private:
	std::chrono::microseconds initializationTime;
	std::vector<std::chrono::microseconds> talentTreeTimes;
	std::vector<std::chrono::microseconds> branchTimes;
	std::vector<std::chrono::microseconds> branch1Times;
	std::vector<std::chrono::microseconds> branch4Times;
	std::vector<std::chrono::microseconds> branch7Times;
};

