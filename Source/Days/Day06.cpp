#include "Day06.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <vector>
#include <map>

struct Pos
{
	int x = 0;
	int y = 0;

	int& operator[](int index)
	{
		return ((index % 2) == 0) ? x : y;
	}

	Pos& operator+=(Pos& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	Pos& operator-=(Pos& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	Pos operator+(const Pos& other) const
	{
		Pos newPos = *this;
		newPos.x += other.x;
		newPos.y += other.y;
		return newPos;
	}

	Pos operator-(const Pos& other) const
	{
		Pos newPos = *this;
		newPos.x -= other.x;
		newPos.y -= other.y;
		return newPos;
	}

	Pos operator/(const Pos& other) const
	{
		Pos newPos = *this;
		
		newPos.x = (newPos.x != 0) ? newPos.x / other.x : 0;
		newPos.y = (newPos.y != 0) ? newPos.y / other.y : 0;
		return newPos;
	}

	bool operator==(const Pos& other) const
	{
		return x == other.x && y == other.y;
	}

	Pos Abs() const
	{
		Pos newPos = *this;
		newPos.x = abs(newPos.x);
		newPos.y = abs(newPos.y);
		return newPos;
	}
};

struct PosGroup
{
	Pos group[4];

	Pos& operator[](int index)
	{
		return group[index];
	}

	bool CompareAny(Pos& otherPos)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (group[i] == otherPos)
			{
				return true;
			}
		}

		return false;
	}
};

struct Place
{
	int bitId = 0;
	Pos pos;

	char item;

	void MakeBitId()
	{
		bitId = (pos.x << 8) | pos.y;
	}

	bool operator==(const Place& other) const
	{
		return bitId == other.bitId;
	}

	bool operator==(int otherBitId) const
	{
		return bitId == otherBitId;
	}
};

// 0,-1     1,0     0,1     -1,0
//     +1,+1   -1,+1   -1,-1    +1,-1

struct Guard
{
	Place place;
	Pos dir{ 0, -1 };
	Pos dirOffset{ 1, 1 };
	int indexToFlip = 0;

	void Rotate()
	{
		dir += dirOffset;
		dirOffset[indexToFlip] = -dirOffset[indexToFlip];
		indexToFlip = (indexToFlip + 1) % 2;
	}
};


Day06::Day06()
{
	m_dayData.m_tokenSeparator = "";
}

void Day06::RunDayPart1()
{
	m_dayData.m_enableDebugReport = false;
	RunDay();
	std::cout << m_visits << std::endl;
}

void Day06::RunDayPart2()
{
	m_dayData.m_enableDebugReport = true;
	//RunDay();

	int timeLoopSpots = 0;
	std::vector<Pos> loopPoses;
	std::vector<PosGroup> groups;
	for (int i = 0; i + 2 < m_rotations.size(); ++i)
	{
		PosGroup posGroup;
		posGroup[0] = m_rotations[i].pos;
		posGroup[1] = m_rotations[i + 1].pos;
		posGroup[2] = m_rotations[i + 2].pos;

		Pos samePosCount;
		Pos newLoopPos;

		for (int j = 0; j < 2; ++j)
		{
			if (posGroup[j].x == posGroup[j + 1].x)
			{
				samePosCount.x++;
			}
			if (posGroup[j].y == posGroup[j + 1].y)
			{
				samePosCount.y++;
			}
		}

		if (samePosCount.x == 1 && samePosCount.y == 1)
		{
			Pos newTimeLoopRotation;
			
			newTimeLoopRotation = posGroup[0] + (posGroup[2] - posGroup[1]);
			//newTimeLoopRotation.y = posGroup[0].y + (posGroup[2].y - posGroup[1].y);

			posGroup[3] = newTimeLoopRotation;

			//const int xDist = newTimeLoopRotation.x - posGroup[2].x;
			//const int yDist = newTimeLoopRotation.y - posGroup[2].y;

			const Pos dist = newTimeLoopRotation - posGroup[2];
			const Pos normalDist = dist / dist.Abs();

			Pos newTimeLoopPos = newTimeLoopRotation + normalDist;
			//newTimeLoopPos.x = newTimeLoopRotation.x + normalXDist;
			//newTimeLoopPos.y = newTimeLoopRotation.y + normalYDist;

			if (std::find(loopPoses.cbegin(), loopPoses.cend(), newTimeLoopPos) == loopPoses.cend())
			{
				if (std::find_if(m_rotations.cbegin(), m_rotations.cend(),
					[&newTimeLoopRotation, &posGroup, dist, normalDist](const Place& currentPlace)
					{
						if (normalDist.x != 0)
						{
							const int currentPlaceDist = currentPlace.pos.x - posGroup[2].x;
							const int normalCurrentPlaceDist = (currentPlaceDist != 0) ? currentPlaceDist / abs(currentPlaceDist) : 0;

							return (currentPlace.pos.y == newTimeLoopRotation.y) &&
								(normalCurrentPlaceDist == normalDist.x) &&
								(abs(currentPlaceDist) < abs(dist.x));
						}
						
						if (normalDist.y != 0)
						{
							const int currentPlaceDist = currentPlace.pos.y - posGroup[2].y;
							const int normalCurrentPlaceDist = (currentPlaceDist != 0) ? currentPlaceDist / abs(currentPlaceDist) : 0;
							return (currentPlace.pos.x == newTimeLoopRotation.x) &&
								(normalCurrentPlaceDist == normalDist.y) &&
								(abs(currentPlaceDist) < abs(dist.y));
						}

						return false;
						
					}) == m_rotations.cend())
				{
					timeLoopSpots++;
					loopPoses.push_back(newTimeLoopPos);
				}
			}

			Pos halfPoint;
			halfPoint.x = posGroup[2].x + static_cast<int>((newTimeLoopRotation.x - posGroup[2].x) * 0.5f);
			halfPoint.y = posGroup[2].y + static_cast<int>((newTimeLoopRotation.y - posGroup[2].y) * 0.5f);
			
			Pos centerPoint;
			centerPoint.x = posGroup[1].x + static_cast<int>((newTimeLoopRotation.x - posGroup[1].x) * 0.5f);
			centerPoint.y = posGroup[1].y + static_cast<int>((newTimeLoopRotation.y - posGroup[1].y) * 0.5f);

			
			/*if (m_dayData.m_rawData[halfPoint.y][halfPoint.x] != '#')
			{
				for (PosGroup& otherPosGroup : groups)
				{
					if (otherPosGroup.CompareAny(centerPoint))
					{
						timeLoopSpots++;
						halfPoint.x += normalXDist;
						halfPoint.y += normalYDist;
						loopPoses.push_back(halfPoint);
					}
				}
			}*/

			groups.push_back(posGroup);

		}
	}

	//for (int i = 0; i + 1 < groups.size(); ++i)
	//{
	//	PosGroup& group1 = groups[i];
	//	PosGroup& group2 = groups[i + 1];

	//	
	//}
	for (PosGroup& group : groups)
	{
		for (PosGroup& otherGroup : groups)
		{
			Pos centerPoint;
			centerPoint.x = group[1].x + static_cast<int>((group[3].x - group[1].x) * 0.5f);
			centerPoint.y = group[1].y + static_cast<int>((group[3].y - group[1].y) * 0.5f);

			if (otherGroup.CompareAny(centerPoint))
			{
				timeLoopSpots++;
			}
		}
	}

	std::cout << timeLoopSpots << std::endl;

	for (int i = 0; i < m_dayData.m_rawData.size(); ++i)
	{
		const std::string& line = m_dayData.m_rawData[i];

		for (int j = 0; j < line.size(); ++j)
		{
			Pos pos{ j, i };
			Place place;
			place.pos = pos;
			place.MakeBitId();
			if (std::find(loopPoses.cbegin(), loopPoses.cend(), pos) != loopPoses.cend())
			{
				if (line[j] == '#')
				{
					DebugReport("X");
				}
				else
				{
					DebugReport("O");
				}
			}
			else if (std::find(m_rotations.cbegin(), m_rotations.cend(), place.bitId) != m_rotations.cend())
			{
				DebugReport("+");
			}
			else if (line[j] == '#')
			{
				DebugReport("#");
			}
			else if (line[j] == '^')
			{
				DebugReport("^");
			}
			else
			{
				DebugReport(".");
			}
		}
		DebugReportEndl();
	}
}

void Day06::RunDay()
{
	std::unordered_map<int, Place> places;

	Guard guard;

	Pos bounds;
	bounds.y = static_cast<int>(m_dayData.m_rawData.size());

	for (int i = 0; i < bounds.y; ++i)
	{
		const std::string& line = m_dayData.m_rawData[i];

		if (bounds.x == 0)
		{
			bounds.x = static_cast<int>(line.size());
		}

		for (int j = 0; j < bounds.x; ++j)
		{
			if (line[j] == '#')
			{
				Place newPlace;
				newPlace.pos = { j, i };
				newPlace.MakeBitId();
				newPlace.item = '#';
				places.insert({ newPlace.bitId, newPlace });
			}
			else if (line[j] == '^')
			{
				guard.place.pos = { j, i };
				guard.place.item = '^';
				guard.place.MakeBitId();
			}
		}
	}

	m_visits = 0;
	std::vector<int> visitsList;
	while (guard.place.pos.x >= 0 &&
		guard.place.pos.x < bounds.x &&
		guard.place.pos.y >= 0 &&
		guard.place.pos.y < bounds.y)
	{
		Place currentGuardPlace = guard.place;
		currentGuardPlace.pos += guard.dir;
		currentGuardPlace.MakeBitId();

		if (places.find(currentGuardPlace.bitId) != places.cend())
		{
			currentGuardPlace.pos -= guard.dir;
			currentGuardPlace.MakeBitId();
			guard.place = currentGuardPlace;
			guard.Rotate();
			m_rotations.push_back(guard.place);
		}
		else
		{
			if (std::find(visitsList.cbegin(), visitsList.cend(), currentGuardPlace.bitId) == visitsList.cend())
			{
				m_visits += 1;
				visitsList.push_back(currentGuardPlace.bitId);
			}
			guard.place = currentGuardPlace;
		}
	}
}