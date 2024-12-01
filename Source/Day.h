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
};


class Day
{
public:
	virtual std::string GetDayId() const = 0;

	virtual void RunDay() = 0;

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