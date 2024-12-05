#include "Day05.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <vector>
#include <map>

Day05::Day05()
{
	m_dayData.m_tokenSeparator = "";
}

void Day05::RunDayPart1()
{
	m_dayData.m_enableDebugReport = false;

}

void Day05::RunDayPart2()
{
	m_dayData.m_enableDebugReport = true;

	int sum = 0;
	int i = 0;
	typedef std::multimap<int, int> NumMap;
	NumMap orderRules;
	{
		std::string row;
		do
		{
			row = m_dayData.m_rawData[i];

			if (row != "")
			{
				auto tokenPos = row.find("|");
				std::string a = row.substr(0, tokenPos);
				std::string b = row.substr(tokenPos + 1);
				orderRules.insert({ std::stoi(a), std::stoi(b) });
			}
			i++;
		} while (i < m_dayData.m_rawData.size() && row != "");
	}

	for (i; i < m_dayData.m_rawData.size(); ++i)
	{
		const std::string& row = m_dayData.m_rawData[i];

		std::string remaining = row;
		std::string::size_type tokenPos = 0;
		std::vector<int> numbers;
		do
		{
			tokenPos = remaining.find(",");
			std::string num = remaining.substr(0, tokenPos);
			numbers.push_back(std::stoi(num));
			remaining = remaining.substr(tokenPos + 1);
		} while (tokenPos != std::string::npos);

		bool isGood = true;
		for (int numindex = 0; numindex < numbers.size() - 1; ++numindex)
		{
			bool found = false;
			for (NumMap::iterator it = orderRules.find(numbers[numindex]); it != orderRules.end(); ++it)
			{

				if (it->second == numbers[numindex+1])
				{
					found = true;
				}
			}

			if (!found)
			{
				isGood = false;
				break;
			}
		}

		if (isGood)
		{
			int goodNum = numbers[(numbers.size() - 1) / 2];
			DebugReport(std::to_string(goodNum));
			DebugReportEndl();
			sum += goodNum;
		}
	}
	
	std::cout << sum << std::endl;
}