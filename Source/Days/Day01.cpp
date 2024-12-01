#include "Day01.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

Day01::Day01()
{
	m_dayData.m_tokenSeparator = "   ";
}

void Day01::RunDay()
{
	m_dayData;

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

	std::cout << sum;
}