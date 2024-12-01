#ifndef __DAY_01_H__
#define __DAY_01_H__

#include "Day.h"

class Day01 : public Day
{
public:
	Day01();

	virtual std::string GetDayId() const override
	{
		return "Day01";
	}

	virtual void RunDayPart1() override;
	virtual void RunDayPart2() override;
};

CREATE_DAY(Day01)

#endif //__DAY_01_H__
