#ifndef __DAY_01_H__
#define __DAY_01_H__

#include "Day.h"

class Day01 : public Day
{
public:
	virtual std::string GetDayId() const override
	{
		return "Day01";
	}

	virtual void RunDay() override;
};

CREATE_DAY(Day01)

#endif //__DAY_01_H__
