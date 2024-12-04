#ifndef __DAY_04_H__
#define __DAY_04_H__

#include "Day.h"

class Day04 : public Day
{
public:
	Day04();

	virtual std::string GetDayId() const override
	{
		return "Day04";
	}

	virtual void RunDayPart1() override;
	virtual void RunDayPart2() override;

private:
	void RunCorruptedProgram(const bool runDoAndDont = false);
};

CREATE_DAY(Day04)

#endif //__DAY_04_H__
