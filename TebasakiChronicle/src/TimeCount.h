#pragma once

class TimeCount
{
private:
	int cntTime;	//�o�ߎ���
	int endTime;	//�I������
	bool isTimeEnd;	//�I�����Ԃ𒴉߂��Ă��邩�ۂ�

public:
	TimeCount();

	//�o�ߎ��Ԃ�0�ɂ���
	void ResetCntTime();

	//�I�����Ԃ�ݒ肷��
	//-1�Ŗ���
	void SetEndTime(int setEndTime);

	//���Ԃ𑪂�
	void Run();

	//���݂̌o�ߎ��Ԃ�Ԃ�
	int GetNowCntTime() const;

	//�ݒ肳��Ă���I�����Ԃ�Ԃ�
	int GetEndTime() const;

	//�o�ߎ��Ԃ��I�����Ԃ܂œ��B���Ă�����true��Ԃ�
	bool IsTimeEnd() const;
};