#include "Day04.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <vector>
#include <regex>

Day04::Day04()
{
	m_dayData.m_tokenSeparator = "";
}

void Day04::RunDayPart1()
{
	m_dayData.m_enableDebugReport = false;

	int xmasCount = 0;
	std::string stringToFind = "XMAS";

	std::function<bool(const int, const int, const int)> FindAdjadcentCharFunc = nullptr;

	// std::function<bool(std::vector<std::string>& data, const int x, const int y, const int STFIndex)

	const auto TestIndexForXmas = [&FindAdjadcentCharFunc, &stringToFind, &data = m_dayData.m_rawData](const int x, const int y, const int STFIndex) -> bool
		{
			if (y < 0 || y >= data.size())
			{
				return false;
			}

			const std::string& row = data[y];

			if (x < 0 || x >= row.size())
			{
				return false;
			}

			return row[x] == stringToFind[STFIndex];
		};

	FindAdjadcentCharFunc = [&FindAdjadcentCharFunc, &TestIndexForXmas, &stringToFind, &data = m_dayData.m_rawData](const int x, const int y, const int STFIndex) -> bool
	{
		if (stringToFind.size() < STFIndex)
		{
			return false;
		}

		const int nextStfIndex = STFIndex + 1;

		if (TestIndexForXmas(x, y, STFIndex))
		{
			return FindAdjadcentCharFunc(x, y, nextStfIndex);
		}

		// cross - up down left right
		if (TestIndexForXmas(x - 1, y, STFIndex))
		{
			return FindAdjadcentCharFunc(x - 1, y, nextStfIndex);
		}

		if (TestIndexForXmas(x + 1, y, STFIndex))
		{
			return FindAdjadcentCharFunc(x + 1, y, nextStfIndex);
		}

		if (TestIndexForXmas(x, y - 1, STFIndex))
		{
			return FindAdjadcentCharFunc(x, y - 1, nextStfIndex);
		}

		if (TestIndexForXmas(x, y + 1, STFIndex))
		{
			return FindAdjadcentCharFunc(x, y + 1, nextStfIndex);
		}

		// diagonals
		if (TestIndexForXmas(x - 1, y - 1, STFIndex))
		{
			return FindAdjadcentCharFunc(x - 1, y - 1, nextStfIndex);
		}

		if (TestIndexForXmas(x - 1, y + 1, STFIndex))
		{
			return FindAdjadcentCharFunc(x - 1, y + 1, nextStfIndex);
		}

		if (TestIndexForXmas(x + 1, y - 1, STFIndex))
		{
			return FindAdjadcentCharFunc(x + 1, y - 1, nextStfIndex);
		}

		if (TestIndexForXmas(x + 1, y + 1, STFIndex))
		{
			return FindAdjadcentCharFunc(x + 1, y + 1, nextStfIndex);
		}

		return true;
	};

	for (int i = 0; i < m_dayData.m_rawData.size(); ++i)
	{
		const std::string& row = m_dayData.m_rawData[0];
		for (int j = 0; j < row.size(); ++j)
		{
			const char xmasChar = row[j];

			constexpr int strToFindIndex = 0;
			if (FindAdjadcentCharFunc(j, i, strToFindIndex))
			{
				xmasCount++;
			}
		}
	}

	std::cout << xmasCount << std::endl;
}

void Day04::RunDayPart2()
{
	m_dayData.m_enableDebugReport = false;
	
}