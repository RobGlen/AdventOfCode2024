#include "Day01.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

Day01::Day01()
{
	m_dayData.m_tokenSeparator = "   ";
}

void Day01::RunDayPart1()
{
	std::vector<int> listA, listB;

	for (const std::vector<std::string>& pair : m_dayData.m_data)
	{
		listA.push_back(std::stoi(pair[0]));
		listB.push_back(std::stoi(pair[1]));
	}

	const auto sortFunc = [](const int a, const int b)
	{
		return a < b;
	};

	std::sort(listA.begin(), listA.end(), sortFunc);
	std::sort(listB.begin(), listB.end(), sortFunc);

	int sum = 0;
	for (int i = 0; i < listA.size(); ++i)
	{
		sum += std::abs(listA[i] - listB[i]);
	}

	std::cout << sum << std::endl;
}

void Day01::RunDayPart2()
{
	std::vector<int> listA, listB;

	for (const std::vector<std::string>& pair : m_dayData.m_data)
	{
		listA.push_back(std::stoi(pair[0]));
		listB.push_back(std::stoi(pair[1]));
	}

	int sum = 0;
	for (int aItem : listA)
	{
		int count = 0;

		std::vector<int>::iterator it = listB.begin();
		while ((it = std::find(it, listB.end(), aItem)) != listB.end())
		{
			count++;
			it++;
		}
		sum += aItem * count;
	}

	std::cout << sum << std::endl;
}