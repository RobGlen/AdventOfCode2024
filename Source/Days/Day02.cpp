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
	m_dayData.m_enableDebugReport = false;
	static constexpr bool canRemoveLevel = false;
	SafetyReport(canRemoveLevel);
}

void Day02::RunDayPart2()
{
	m_dayData.m_enableDebugReport = true;
	static constexpr bool canRemoveLevel = true;
	SafetyReport(canRemoveLevel);
}

void Day02::SafetyReport(const bool canRemoveLevel)
{
	int safeCount = 0;
	int line = 1;
	for (const std::vector<std::string>& report : m_dayData.m_data)
	{
		bool isSafe = true;
		bool shouldRemoveLevel = canRemoveLevel;
		bool isLastPositive = false;
		bool isFirst = true;

		// test safety func.
		const auto TestSafety = [&isLastPositive, &isFirst](const std::vector<std::string>& report, const int indexA, const int indexB) -> bool
		{
			if (indexA >= report.size() || indexB >= report.size())
			{
				return true;
			}

			const int a = std::stoi(report[indexA]);
			const int b = std::stoi(report[indexB]);
			const int dist = a - b;
			const int absDist = std::abs(dist);

			if (absDist == 0 || absDist > 3)
			{
				return false;
			}

			if (!isFirst && ((isLastPositive && dist < 0) || (!isLastPositive && dist > 0)))
			{
				return false;
			}

			isLastPositive = dist > 0;
			isFirst = false;
			return true;
		};

		int safetyIssuesCount = 0;
		int removeIndex = -1;

		const auto TestReport = [&TestSafety](const std::vector<std::string>& report, const int skipIndex = -1)
		{
			for (int i = 0; i < report.size(); i++)
			{
				int offset = ((i + 1) != skipIndex) ? 1 : 2;
				if (i == skipIndex)
				{
					continue;
				}

				if (!TestSafety(report, i, i + offset))
				{
					return false;
				}
			}

			return true;
		};
		
		if (canRemoveLevel)
		{
			if (!TestReport(report))
			{
				isSafe = false;
				for (int i = 0; i < report.size(); ++i)
				{
					isLastPositive = false;
					isFirst = true;

					if (TestReport(report, i))
					{
						isSafe = true;
						break;
					}
				}
			}
		}
		else
		{
			isSafe = TestReport(report);
		}

		DebugReport(std::to_string(line) + "\t");
		if (isSafe)
		{
			for (int i = 0; i < report.size(); i++)
			{
				DebugReport(report[i] + " ");
			}
			DebugReport(": Safe.");
			safeCount++;
		}
		else
		{
			for (int i = 0; i < report.size(); i++)
			{
				DebugReport(report[i] + " ");
			}
			DebugReport(": Unsafe.\t");
		}
		DebugReportEndl();
		line++;
	}

	std::cout << safeCount << std::endl;
}