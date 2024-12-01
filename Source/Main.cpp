#include "Utils/DayManager.h"
#include "Utils/DayParser.h"

//#include "Days/Day01.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return -1;
    }

    for (int i = 1; i < argc; ++i)
    {
        DayParser::ParseDay(argv[i]);
    }

    DayManager::Get().RunDays();
    
    return 0;
}