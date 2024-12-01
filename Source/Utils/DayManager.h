#ifndef __DAY_MANAGER_H__
#define __DAY_MANAGER_H__

#include <functional>
#include <memory>
#include <string>

class Day;

class DayManager
{
public:
	static DayManager& Get()
	{
		static DayManager dayManager;
		return dayManager;
	}

	void RegisterDay(std::shared_ptr<Day> day);

	std::shared_ptr<Day> OnDayParsing(const std::string& DayId);
	std::shared_ptr<Day> FindDay(const std::string& DayId) const;

	void RunDays();

private:
	std::vector<std::string> m_daysToRun;

	std::unordered_map<std::string, std::shared_ptr<Day>> m_dayMap;
};

#endif //__DAY_MANAGER_H__