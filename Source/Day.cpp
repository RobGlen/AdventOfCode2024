#include "Day.h"

#include <iostream>

void Day::RunDay()
{
	RunDayPart1();
	RunDayPart2();
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