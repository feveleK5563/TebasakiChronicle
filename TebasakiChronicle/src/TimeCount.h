#pragma once

class TimeCount
{
private:
	int cntTime;	//�o�ߎ���
	int endTime;	//�I������
	bool isTimeEnd;	//�I�����Ԃ𒴉߂��Ă��邩�ۂ�
	bool isCount;

public:
	TimeCount();

	//�o�ߎ��Ԃ�0�ɂ���
	void ResetCntTime();

	//�I�����Ԃ�ݒ肷��
	void SetEndTime(int setEndTime);

	//���Ԃ𑪂�
	void Run();

	//�����I�Ɍ��݂̎��Ԃ�ݒ肷��
	void SetTime(int time);

	//���Ԃ̉��Z���������ۂ���ݒ�(false���w�肷���Run���Ă�ł����l���ω����Ȃ��Ȃ�)
	void Count(bool isCount);

	//���݂̌o�ߎ��Ԃ�Ԃ�
	int GetNowCntTime() const;

	//�o�ߎ��Ԃ��I�����Ԃ܂œ��B���Ă�����true��Ԃ�
	bool IsTimeEnd() const;
};