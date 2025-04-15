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
	m_dayData.m_enableDebugReport = true;
	int sum = 0;
	int lineIndex = 0;
	std::unordered_map<int, std::vector<int>> forwardOrderRules;
	std::unordered_map<int, std::vector<int>> backwardOrderRules;

	{
		typedef std::multimap<int, int> NumMap;
		NumMap orderRulesInitial;
		std::string row;

		do
		{
			row = m_dayData.m_rawData[lineIndex];

			if (row != "")
			{
				auto tokenPos = row.find("|");
				const std::string aStr = row.substr(0, tokenPos);
				const std::string bStr = row.substr(tokenPos + 1);
				const int a = std::stoi(aStr);
				const int b = std::stoi(bStr);
				orderRulesInitial.insert({ a, b });
			}
			lineIndex++;
		} while (lineIndex < m_dayData.m_rawData.size() && row != "");

		for (auto& [k, v] : orderRulesInitial)
		{
			forwardOrderRules[k].push_back(v);
			backwardOrderRules[v].push_back(k);
		}
	}

	for (lineIndex; lineIndex < m_dayData.m_rawData.size(); ++lineIndex)
	{
		const std::string& row = m_dayData.m_rawData[lineIndex];

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
		for (int i = 0; i < numbers.size(); ++i)
		{
			int currentNum = numbers[i];
			for (int j = i + 1; j < numbers.size(); ++j)
			{
				int nextNum = numbers[j];
				if (std::find(forwardOrderRules[currentNum].cbegin(), forwardOrderRules[currentNum].cend(), nextNum) == forwardOrderRules[currentNum].cend() ||
					std::find(forwardOrderRules[nextNum].cbegin(), forwardOrderRules[nextNum].cend(), currentNum) != forwardOrderRules[nextNum].cend())
				{
					isGood = false;
				}
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

void Day05::RunDayPart2()
{
	m_dayData.m_enableDebugReport = false;
}