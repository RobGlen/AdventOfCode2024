#include "DayManager.h"

#include "Day.h"

void DayManager::RegisterDay(std::shared_ptr<Day> day)
{
	if (day == nullptr)
	{
		return;
	}

	m_dayMap.insert({ day->GetDayId(), day });
}

std::shared_ptr<Day> DayManager::OnDayParsing(const std::string& DayId)
{
	m_daysToRun.push_back(DayId);
	return FindDay(DayId);
}

std::shared_ptr<Day> DayManager::FindDay(const std::string& DayId) const
{
	auto foundDay = m_dayMap.find(DayId);
	if (foundDay != m_dayMap.end())
	{
		return foundDay->second;
	}

	return nullptr;
}

void DayManager::RunDays()
{
	for (const std::string& dayId : m_daysToRun)
	{
		std::shared_ptr<Day> day = FindDay(dayId);

		if (day == nullptr)
		{
			continue;
		}

		day->RunDay();
	}
	
}