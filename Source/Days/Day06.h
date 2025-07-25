#ifndef __DAY_06_H__
#define __DAY_06_H__

#include "Day.h"

class Day06 : public Day
{
public:
	Day06();

	virtual std::string GetDayId() const override
	{
		return "Day06";
	}

	virtual void RunDayPart1() override;
	virtual void RunDayPart2() override;

private:
};

CREATE_DAY(Day06)

#endif //__DAY_06_H__
