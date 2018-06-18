#pragma once
#include "../src/BaseClass/GUIObject/GUIObject.h"


//---------------------------------------------------------------------
//�T�v: GUI�̃I�u�W�F�N�g(�P�̂̂���)
//�����: �����
//---------------------------------------------------------------------
class ScreenGui
{
public:
	//!@brief	�R���X�g���N�^
	ScreenGui();
	//!@brief	�ł��g���N�^
	~ScreenGui();

	//!@brief	�X�V
	void	UpDate();
	//!@brief	�`��
	void	Render();

	//!@brief	���߂ɕ`�悷��
	void	EarlyRender();
	//!@brief	�x�߂ɕ`�悷��
	void	LateRender();

private:
	GUIObject*		gearLeft[5];	//���ԍ���
	GUIObject*		gearRight[6];	//���ԉE��
	GUIObject*		gearLife[4];	//Life�̎���
	GUIObject*		skillArea;		//�X�L����UI
	GUIObject*		lifeBaseArea;	//�̗͂̊��
	GUIObject*		enemyLife;		//�G�̃��C�t�Q�[�W
};