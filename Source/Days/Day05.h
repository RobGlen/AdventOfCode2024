#ifndef __DAY_05_H__
#define __DAY_05_H__

#include "Day.h"

class Day05 : public Day
{
public:
	Day05();

	virtual std::string GetDayId() const override
	{
		return "Day05";
	}

	virtual void RunDayPart1() override;
	virtual void RunDayPart2() override;

private:
	void RunDay(const bool lookForGoodLines, const bool FixBadLines);
};

CREATE_DAY(Day05)

#endif //__DAY_05_H__
