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
	void SetEndTime(int setEndTime);

	//���Ԃ𑪂�
	//���o�ߎ��Ԃ��I�����Ԃ𒴂��Ă����ꍇ�͌v���������I�ɒ�~����
	void Run();

	//���݂̌o�ߎ��Ԃ�Ԃ�
	int GetNowCntTime() const;

	//�o�ߎ��Ԃ��I�����Ԃ܂œ��B���Ă�����true��Ԃ�
	bool IsTimeEnd() const;
};