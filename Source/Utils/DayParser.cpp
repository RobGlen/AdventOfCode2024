#include "DayParser.h"

#include <string>
#include <format>

void DayParser::ParseDay(char* const dayArg)
{
	std::string DayFile = std::format("Data/Days/{}.txt", dayArg);

	std::ifstream is{ DayFile };


}