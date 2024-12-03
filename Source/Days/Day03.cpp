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
	m_dayData.m_enableDebugReport = false;
	RunCorruptedProgram();
}

void Day03::RunDayPart2()
{
	m_dayData.m_enableDebugReport = false;
	static constexpr bool runDoAndDont = true;
	RunCorruptedProgram(runDoAndDont);
}

void Day03::RunCorruptedProgram(const bool runDoAndDont)
{
	const std::regex wordReg{ R"((mul\([0-9]+,[0-9]+\))|(do\(\))|(don\'t\(\)))" };

	int sum = 0;
	static constexpr int mulIndex = 1;
	static constexpr int doIndex = 2;
	static constexpr int dontIndex = 3;
	bool shouldDo = true;

	for (const std::string& program : m_dayData.m_rawData)
	{
		auto regBegin = std::sregex_iterator(program.begin(), program.end(), wordReg);
		auto regEnd = std::sregex_iterator();

		for (std::sregex_iterator itr = regBegin; itr != regEnd; ++itr)
		{
			std::smatch match = *itr;
			std::string matchStr = match.str();

			if (match[mulIndex].matched)
			{
				std::string matchStr = match[1].str();
				DebugReport(matchStr + ": ");
				auto commaPos = matchStr.find(",");
				std::string aStr = matchStr.substr(4, commaPos - 4);
				std::string bStr = matchStr.substr(commaPos + 1);

				const int multRes = std::stoi(aStr) * std::stoi(bStr);
				DebugReport(std::to_string(multRes));

				if (shouldDo)
				{
					sum += multRes;
				}
			}
			else if (runDoAndDont)
			{
				if (match[doIndex].matched)
				{
					DebugReport("do");
					shouldDo = true;
				}
				else if (match[dontIndex].matched)
				{
					DebugReport("don't");
					shouldDo = false;
				}
			}
			DebugReportEndl();
		}
	}

	std::cout << sum << std::endl;
}