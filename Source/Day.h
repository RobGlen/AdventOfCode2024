#ifndef __DAY_H__
#define __DAY_H__

#include <string>
#include <vector>

#include "Utils/DayManager.h"

struct DayData
{
	std::vector<std::string> m_rawData;
	std::string m_tokenSeparator = " ";
	std::vector<std::vector<std::string>> m_data;
	bool m_enableDebugReport = false;
};


class Day
{
public:
	virtual std::string GetDayId() const = 0;

	void RunDay();
	virtual void RunDayPart1() = 0;
	virtual void RunDayPart2() = 0;

	template<class T_Class>
	static void Create()
	{
		DayManager::Get().RegisterDay(std::shared_ptr<Day>(new T_Class));
	}

	const DayData& GetData() const
	{
		return m_dayData;
	}

	void SetData(const DayData& inData)
	{
		m_dayData = inData;
	}

protected:
	void DebugReport(const std::string& inString) const;
	void DebugReportEndl();

	DayData m_dayData;

};

template<class T_DayClass>
class DayRegistry
{
public:
	DayRegistry()
	{
		Day::Create<T_DayClass>();
	}
};

#define CREATE_DAY(DayType) DayRegistry<DayType> dayRegistry;

#endif //__DAY_H__