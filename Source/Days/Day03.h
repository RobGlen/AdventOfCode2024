#ifndef __DAY_03_H__
#define __DAY_03_H__

#include "Day.h"

class Day03 : public Day
{
public:
	Day03();

	virtual std::string GetDayId() const override
	{
		return "Day03";
	}

	virtual void RunDayPart1() override;
	virtual void RunDayPart2() override;

private:
	void RunCorruptedProgram(const bool runDoAndDont = false);
};

CREATE_DAY(Day03)

#endif //__DAY_03_H__
