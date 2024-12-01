#include "DayParser.h"

#include <format>
#include <fstream>
#include <string>

#include "Day.h"
#include "DayManager.h"

void DayParser::ParseDay(char* const dayArg)
{
	std::string dayId(dayArg);
	std::string dayFile = std::format("Data/Days/{}.txt", dayId);

	std::ifstream istream{ dayFile };

	if (istream)
	{
		std::shared_ptr<Day> day = DayManager::Get().OnDayParsing(dayId);

		if (day == nullptr)
		{
			return;
		}

		// we retrieve this first in case a particular day overrides some properties for bespoke needs.
		DayData dayData = day->GetData();

		for (std::string line; getline(istream, line); )
		{
			dayData.m_data.push_back(line);
		}

		day->SetData(dayData);
	}
}