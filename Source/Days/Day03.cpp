#include "Day03.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <regex>

Day03::Day03()
{
	m_dayData.m_tokenSeparator = "";
}

void Day03::RunDayPart1()
{
	m_dayData.m_enableDebugReport = true;

	const std::regex wordReg{ R"(mul\([0-9]+,[0-9]+\))" };

	int sum = 0;
	for (const std::string& program : m_dayData.m_rawData)
	{
		auto regBegin = std::sregex_iterator(program.begin(), program.end(), wordReg);
		auto regEnd = std::sregex_iterator();

		for (std::sregex_iterator itr = regBegin; itr != regEnd; ++itr)
		{
			std::smatch match = *itr;
			std::string matchStr = match.str();

			DebugReport(matchStr + ": ");

			auto commaPos = matchStr.find(",");
			std::string aStr = matchStr.substr(4, commaPos - 4);
			std::string bStr = matchStr.substr(commaPos + 1);

			const int multRes = std::stoi(aStr) * std::stoi(bStr);
			DebugReport(std::to_string(multRes));
			DebugReportEndl();

			sum += multRes;
		}
	}

	std::cout << sum << std::endl;
}

void Day03::RunDayPart2()
{
	m_dayData.m_enableDebugReport = true;
}
