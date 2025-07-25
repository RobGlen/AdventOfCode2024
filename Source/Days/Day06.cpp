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
};

struct Place
{
	long long bitId = 0;
	Pos pos;

	char item;

	void MakeBitId()
	{
		bitId = (static_cast<long long>(pos.x) << 16) | pos.y;
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

	int visits = 0;
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
		}
		else
		{
			if (std::find(visitsList.cbegin(), visitsList.cend(), currentGuardPlace.bitId) == visitsList.cend())
			{
				visits += 1;
				visitsList.push_back(currentGuardPlace.bitId);
			}
			guard.place = currentGuardPlace;
		}
	}

	std::cout << visits << std::endl;
}

void Day06::RunDayPart2()
{
	m_dayData.m_enableDebugReport = false;
}