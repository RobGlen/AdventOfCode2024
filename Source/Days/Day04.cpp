#include "Day04.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <vector>
#include <regex>

struct Pos
{
	int x = 0;
	int y = 0;
};

Day04::Day04()
{
	m_dayData.m_tokenSeparator = "";
}

void Day04::RunDayPart1()
{
	m_dayData.m_enableDebugReport = false;

	int xmasCount = 0;
	std::string stringToFind = "XMAS";

	std::function<bool(const int, const int, const int, const Pos)> FindAdjadcentCharFunc = nullptr;

	std::vector<Pos> posOffsetsToTest = {
		// neutral
		//{ 0, 0 },

		// up down left right
		{ -1, 0 },
		{ 1, 0 },
		{ 0, -1 },
		{ 0, 1 },

		// diagonals
		{ -1, -1 },
		{ 1, -1 },
		{ -1, 1 },
		{ 1, 1 }
	};

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

	FindAdjadcentCharFunc = [this, &FindAdjadcentCharFunc, &TestIndexForXmas, &stringToFind, &data = m_dayData.m_rawData, &xmasCount](const int x, const int y, const int STFIndex, const Pos posToTest) -> bool
	{
		if (STFIndex >= stringToFind.size())
		{
			++xmasCount;
			return true;
		}

		const int nextStfIndex = STFIndex + 1;

		if (TestIndexForXmas(x + posToTest.x, y + posToTest.y, STFIndex))
		{
			if (FindAdjadcentCharFunc(x + posToTest.x, y + posToTest.y, nextStfIndex, posToTest))
			{
				return true;
			}
		}

		return false;
	};

	std::vector<Pos> found;
	for (int i = 0; i < m_dayData.m_rawData.size(); ++i)
	{
		const std::string& row = m_dayData.m_rawData[i];
		for (int j = 0; j < row.size(); ++j)
		{
			const char xmasChar = row[j];

			if (xmasChar == 'X')
			{
				DebugReport("X: Pos " + std::to_string(j) + ", " + std::to_string(i));
				DebugReportEndl();

				found.push_back({ j, i });
				constexpr int strToFindIndex = 1;
				for (const Pos& posToTest : posOffsetsToTest)
				{
					FindAdjadcentCharFunc(j, i, strToFindIndex, posToTest);
				}
			}
		}
	}

	std::cout << xmasCount << std::endl;
}

void Day04::RunDayPart2()
{
	m_dayData.m_enableDebugReport = false;

	std::vector<Pos> posOffsetsToTest = {
		// diagonals
		{ -1, -1 },
		{ 1, -1 },
		{ -1, 1 },
		{ 1, 1 }
	};

	int xmasCount = 0;
	for (int i = 0; i < m_dayData.m_rawData.size(); ++i)
	{
		const std::string& row = m_dayData.m_rawData[i];
		for (int j = 0; j < row.size(); ++j)
		{
			if (row[j] == 'A')
			{
				int MCount = 0;
				int SCount = 0;
				Pos M1Index = { -1, -1 };
				Pos S1Index = { -1, -1 };
				bool MAligned = false;
				bool SAligned = false;
				for (const Pos pos : posOffsetsToTest)
				{
					const int x = j + pos.x;
					const int y = i + pos.y;

					if (y < 0 || y >= m_dayData.m_rawData.size())
					{
						continue;
					}

					if (x < 0 || x >= m_dayData.m_rawData[y].size())
					{
						continue;
					}

					if (m_dayData.m_rawData[y][x] == 'M')
					{
						MCount++;

						if (MCount == 1)
						{
							M1Index = { x, y };
						}
						else if (MCount == 2)
						{
							MAligned = x == M1Index.x || y == M1Index.y;
						}
					}
					else if (m_dayData.m_rawData[y][x] == 'S')
					{
						SCount++;

						if (SCount == 1)
						{
							S1Index = { x, y };
						}
						else if (SCount == 2)
						{
							SAligned = x == S1Index.x || y == S1Index.y;
						}
					}
				}

				if (MAligned && SAligned)
				{
					xmasCount++;
				}
			}
		}
	}
	std::cout << xmasCount << std::endl;
}