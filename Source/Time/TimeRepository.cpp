#include "TimeRepository.h"
#include <chrono>
#include <vector>

TimeRepository::TimeRepository() {}

std::chrono::milliseconds TimeRepository::getInitializationTime() const
{
	return initializationTime;
}

std::vector<std::chrono::milliseconds> TimeRepository::getTalentTreeTimes() const
{
	return talentTreeTimes;
}

std::vector<std::chrono::milliseconds> TimeRepository::getBranchTimes() const
{
	return branchTimes;
}

std::vector<std::chrono::milliseconds> TimeRepository::getBranch1Times() const
{
	return branch1Times;
}

std::vector<std::chrono::milliseconds> TimeRepository::getBranch4Times() const
{
	return branch4Times;
}

std::vector<std::chrono::milliseconds> TimeRepository::getBranch7Times() const
{
	return branch7Times;
}

TimeRepository& TimeRepository::setInitializationTime(
		const std::chrono::milliseconds& initializationTime)
{
	this->initializationTime = initializationTime;
	return *this;
}

TimeRepository& TimeRepository::setTalentTreeTimes(
		const std::vector<std::chrono::milliseconds>& talentTreeTimes)
{
	this->talentTreeTimes = talentTreeTimes;
	return *this;
}

TimeRepository& TimeRepository::setBranchTimes(
		const std::vector<std::chrono::milliseconds>& branchTimes)
{
	this->branchTimes = branchTimes;
	return *this;
}

TimeRepository& TimeRepository::setBranch1Times(
		const std::vector<std::chrono::milliseconds>& branch1Times)
{
	this->branch1Times = branch1Times;
	return *this;
}

TimeRepository& TimeRepository::setBranch4Times(
		const std::vector<std::chrono::milliseconds>& branch4Times)
{
	this->branch4Times = branch4Times;
	return *this;
}

TimeRepository& TimeRepository::setBranch7Times(
		const std::vector<std::chrono::milliseconds>& branch7Times)
{
	this->branch7Times = branch7Times;
	return *this;
}

TimeRepository& TimeRepository::addTalentTreeTime(const std::chrono::milliseconds& talentTreeTime)
{
	this->talentTreeTimes.push_back(talentTreeTime);
	return *this;
}

TimeRepository& TimeRepository::addBranchTime(const std::chrono::milliseconds& talentTreeTime)
{
	this->branchTimes.push_back(talentTreeTime);
	return *this;
}

