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
			dayData.m_rawData.push_back(line);

			if (dayData.m_tokenSeparator != "")
			{
				//line.split();
				std::vector<std::string> lineData;
				std::string currentString = line;
				std::string::size_type tokenPos = 0;

				while ((tokenPos = currentString.find(dayData.m_tokenSeparator)) != std::string::npos)
				{
					std::string value = currentString.substr(0, tokenPos);
					lineData.push_back(value);
					currentString = currentString.substr(tokenPos + dayData.m_tokenSeparator.size());
				}

				lineData.push_back(currentString);
				
				dayData.m_data.push_back(lineData);
			}
		}

		day->SetData(dayData);
	}
}