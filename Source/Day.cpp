#include "Day.h"

#include <iostream>

void Day::RunDay()
{
	const std::string dayId = GetDayId();

	std::cout << dayId << " Part 1" << std::endl;
	RunDayPart1();

	std::cout << std::endl << dayId << " Part 2" << std::endl;
	RunDayPart2();

	std::cout << std::endl;
}

void Day::DebugReport(const std::string& inString) const
{
	if (m_dayData.m_enableDebugReport)
	{
		std::cout << inString;
	}
}

void Day::DebugReportEndl()
{
	if (m_dayData.m_enableDebugReport)
	{
		std::cout << std::endl;
	}
}