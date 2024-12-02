#ifndef __DAY_02_H__
#define __DAY_02_H__

#include "Day.h"

class Day02 : public Day
{
public:
	Day02();

	virtual std::string GetDayId() const override
	{
		return "Day02";
	}

	virtual void RunDayPart1() override;
	virtual void RunDayPart2() override;

private:
	void SafetyReport(const bool canRemoveLevel);
};

CREATE_DAY(Day02)

#endif //__DAY_02_H__
