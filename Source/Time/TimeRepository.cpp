#include "TimeRepository.h"
#include <chrono>
#include <vector>

TimeRepository::TimeRepository() {}

std::chrono::microseconds TimeRepository::getInitializationTime() const
{
	return initializationTime;
}

std::vector<std::chrono::microseconds> TimeRepository::getTalentTreeTimes() const
{
	return talentTreeTimes;
}

std::vector<std::chrono::microseconds> TimeRepository::getBranchTimes() const
{
	return branchTimes;
}

std::vector<std::chrono::microseconds> TimeRepository::getBranch1Times() const
{
	return branch1Times;
}

std::vector<std::chrono::microseconds> TimeRepository::getBranch4Times() const
{
	return branch4Times;
}

std::vector<std::chrono::microseconds> TimeRepository::getBranch7Times() const
{
	return branch7Times;
}

TimeRepository& TimeRepository::setInitializationTime(
		const std::chrono::microseconds& newInitializationTime)
{
	this->initializationTime = newInitializationTime;
	return *this;
}

TimeRepository& TimeRepository::setTalentTreeTimes(
		const std::vector<std::chrono::microseconds>& newTalentTreeTimes)
{
	this->talentTreeTimes = newTalentTreeTimes;
	return *this;
}

TimeRepository& TimeRepository::setBranchTimes(
		const std::vector<std::chrono::microseconds>& newBranchTimes)
{
	this->branchTimes = newBranchTimes;
	return *this;
}

TimeRepository& TimeRepository::setBranch1Times(
		const std::vector<std::chrono::microseconds>& newBranch1Times)
{
	this->branch1Times = newBranch1Times;
	return *this;
}

TimeRepository& TimeRepository::setBranch4Times(
		const std::vector<std::chrono::microseconds>& newBranch4Times)
{
	this->branch4Times = newBranch4Times;
	return *this;
}

TimeRepository& TimeRepository::setBranch7Times(
		const std::vector<std::chrono::microseconds>& newBranch7Times)
{
	this->branch7Times = newBranch7Times;
	return *this;
}

TimeRepository& TimeRepository::addTalentTreeTime(const std::chrono::microseconds& talentTreeTime)
{
	this->talentTreeTimes.push_back(talentTreeTime);
	return *this;
}

TimeRepository& TimeRepository::addBranchTime(const std::chrono::microseconds& branchTime)
{
	this->branchTimes.push_back(branchTime);
	return *this;
}

