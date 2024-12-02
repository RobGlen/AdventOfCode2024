#include "Day02.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

Day02::Day02()
{
	
}

void Day02::RunDayPart1()
{
	int safeCount = 0;
	for (const std::vector<std::string>& report : m_dayData.m_data)
	{
		bool bIsSafe = true;
		
		
		bool bIsLastPositive = false;
		bool bIsFirst = true;
		for (int i = 0; i < report.size() - 1; i++)
		{
			std::cout << report[i] << " ";

			if (!bIsSafe)
			{
				continue;
			}

			const int a = std::stoi(report[i]);
			const int b = std::stoi(report[i+1]);
			const int dist = a - b;
			const int absDist = std::abs(dist);

			if (absDist == 0 || absDist > 3)
			{
				bIsSafe = false;
				continue;
			}

			if (!bIsFirst && ((bIsLastPositive && dist < 0) || (!bIsLastPositive && dist > 0)))
			{
				bIsSafe = false;
				continue;
			}

			bIsLastPositive = dist > 0;
			bIsFirst = false;
		}

		std::cout << report[report.size() - 1] << " ";

		if (bIsSafe)
		{
			std::cout << ": Safe.";
			safeCount++;
		}
		else
		{
			std::cout << ": Unsafe.";
		}

		std::cout << std::endl;
	}

	std::cout << safeCount << std::endl;
}

void Day02::RunDayPart2()
{
	
}