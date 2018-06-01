#include "TimeCount.h"

TimeCount::TimeCount():
	cntTime(0),
	endTime(0),
	isTimeEnd(false) {}

void TimeCount::ResetCntTime()
{
	cntTime = 0;
	isTimeEnd = false;
}

void TimeCount::SetEndTime(int setEndTime)
{
	endTime = setEndTime;
	isTimeEnd = false;
}

void TimeCount::Run()
{
	if (cntTime >= endTime)
	{
		isTimeEnd = true;
	}

	++cntTime;
}

int TimeCount::GetNowCntTime() const
{
	return cntTime;
}

bool TimeCount::IsTimeEnd() const
{
	return isTimeEnd;
}