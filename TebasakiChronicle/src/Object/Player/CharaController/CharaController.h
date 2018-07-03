#pragma once
#include "../src/BaseClass/Input/Input.h"
#include "../src/BaseClass/Move.h"

//--------------------------------------------------------------
//�L�����N�^�[�R���g���[���[
//�T�v:�L�����𑀍삷��
//�����:�����
//--------------------------------------------------------------
class CharaController
{
public:
	CharaController();
	~CharaController();

	//1:�Q�Ƃ����ړ��x�N�g���𗘗p���āA���͑�����s��
	void	UpDate(Move& move);

	//�X�e�B�b�N���͂�����������Ԃ�
	bool	IsLStickInput();

	//!@brief	�����͂������ꂽ�����f
	bool	IsStickLeft();
	//!@brief	�E���͂������ꂽ�����f
	bool	IsStickRight();
private:
	float friction;
	float inputAngle;
};


