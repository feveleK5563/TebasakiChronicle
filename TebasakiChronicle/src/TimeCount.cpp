#include "TimeCount.h"

TimeCount::TimeCount():
	cntTime(0),
	endTime(0),
	isTimeEnd(false) {}

//�o�ߎ��Ԃ�0�ɂ���
void TimeCount::ResetCntTime()
{
	cntTime = 0;
	isTimeEnd = false;
}

//�I�����Ԃ�ݒ肷��
//-1�Ŗ���
void TimeCount::SetEndTime(int setEndTime)
{
	endTime = setEndTime;
	isTimeEnd = false;
}

//���Ԃ𑪂�
void TimeCount::Run()
{
	if (endTime != -1 &&
		cntTime >= endTime)
	{
		isTimeEnd = true;
	}

	++cntTime;
}

//���݂̌o�ߎ��Ԃ�Ԃ�
int TimeCount::GetNowCntTime() const
{
	return cntTime;
}

//�ݒ肳��Ă���I�����Ԃ�Ԃ�
int TimeCount::GetEndTime() const
{
	return endTime;
}

//�o�ߎ��Ԃ��I�����Ԃ܂œ��B���Ă�����true��Ԃ�
bool TimeCount::IsTimeEnd() const
{
	return isTimeEnd;
}