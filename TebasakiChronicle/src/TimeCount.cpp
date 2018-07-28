#include "TimeCount.h"

TimeCount::TimeCount():
	cntTime(0),
	endTime(0),
	isTimeEnd(false),
	isCount(true){}

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
	if (endTime >= 0 &&
		cntTime >= endTime)
	{
		isTimeEnd = true;
		return;
	}

	++cntTime;
}

void TimeCount::SetTime(int time)
{
	cntTime = time;
}

void TimeCount::Count(bool isCount)
{
	this->isCount = isCount;
}

int TimeCount::GetNowCntTime() const
{
	return cntTime;
}

bool TimeCount::IsTimeEnd() const
{
	return isTimeEnd;
}