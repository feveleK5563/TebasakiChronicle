#include "TimeCount.h"

TimeCount::TimeCount():
	cntTime(0),
	endTime(0),
	isTimeEnd(false) {}

//経過時間を0にする
void TimeCount::ResetCntTime()
{
	cntTime = 0;
	isTimeEnd = false;
}

//終了時間を設定する
//-1で無効
void TimeCount::SetEndTime(int setEndTime)
{
	endTime = setEndTime;
	isTimeEnd = false;
}

//時間を測る
void TimeCount::Run()
{
	if (endTime != -1 &&
		cntTime >= endTime)
	{
		isTimeEnd = true;
	}

	++cntTime;
}

//現在の経過時間を返す
int TimeCount::GetNowCntTime() const
{
	return cntTime;
}

//設定されている終了時間を返す
int TimeCount::GetEndTime() const
{
	return endTime;
}

//経過時間が終了時間まで到達していたらtrueを返す
bool TimeCount::IsTimeEnd() const
{
	return isTimeEnd;
}