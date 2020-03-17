#pragma once

#include <chrono>
#include <vector>

class TimeRepository {
public:
	static TimeRepository& GetInstance()
	{
		static TimeRepository instance;
		return instance;
	}

	TimeRepository(TimeRepository const&) = delete;
	void operator=(TimeRepository const&) = delete;

	std::chrono::milliseconds getInitializationTime() const;
	std::vector<std::chrono::milliseconds> getTalentTreeTimes() const;
	std::vector<std::chrono::milliseconds> getBranchTimes() const;
	std::vector<std::chrono::milliseconds> getBranch1Times() const;
	std::vector<std::chrono::milliseconds> getBranch4Times() const;
	std::vector<std::chrono::milliseconds> getBranch7Times() const;

	TimeRepository& setInitializationTime(const std::chrono::milliseconds& initializationTime);
	TimeRepository& setTalentTreeTimes(const std::vector<std::chrono::milliseconds>& talentTreeTimes);
	TimeRepository& setBranchTimes(const std::vector<std::chrono::milliseconds>& branchTimes);
	TimeRepository& setBranch1Times(const std::vector<std::chrono::milliseconds>& branch1Times);
	TimeRepository& setBranch4Times(const std::vector<std::chrono::milliseconds>& branch4Times);
	TimeRepository& setBranch7Times(const std::vector<std::chrono::milliseconds>& branch7Times);

	TimeRepository& addTalentTreeTime(const std::chrono::milliseconds& talentTreeTime);
	TimeRepository& addBranchTime(const std::chrono::milliseconds& talentTreeTime);

private:
	TimeRepository();

private:
	std::chrono::milliseconds initializationTime;
	std::vector<std::chrono::milliseconds> talentTreeTimes;
	std::vector<std::chrono::milliseconds> branchTimes;
	std::vector<std::chrono::milliseconds> branch1Times;
	std::vector<std::chrono::milliseconds> branch4Times;
	std::vector<std::chrono::milliseconds> branch7Times;
};

