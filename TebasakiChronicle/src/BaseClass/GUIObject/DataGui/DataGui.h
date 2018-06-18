#pragma once
#include "../src/BaseClass/GUIObject/GUIObject.h"


//---------------------------------------------------------------------
//�T�v: �f�[�^��\��������GUI(�P�̂̂���)
//�����: �����
//---------------------------------------------------------------------
class DataGui
{
public:
	//!@brief	�R���X�g���N�^
	DataGui(GameObject& gameObj);
	//!@brief	�f�X�g���N�^
	~DataGui();

	//!@brief	�X�V
	void	UpDate();
	//!@brief	�`��
	void	Render();

	//!@brief	�����̌v�Z
	//!@param[in]	gameObj	�Q�[���I�u�W�F�N�g
	void	Raito(GameObject& gameObj);

private:
	//!@brief	�j�̕ϓ�����
	void	Fluctuation(const K_Math::Vector3& targetPos);

private:
	GUIObject*	lifeNeedle;		//���C�t�̐j
	float		maxAngle;		//�ő�p�x
	float		minAngle;		//�ŏ��p�x
	float		raito;			//����
	float		changeAmount;	//�ω���
	float		offsetAngle;	//�I�t�Z�b�g�l
	K_Math::Vector3	showLife;

	int		life;
	int		maxLife;
	float	timeCnt;
};