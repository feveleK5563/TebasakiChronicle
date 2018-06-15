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

	//���̃��C�t����
	void	RaitoRaito();

private:
	GUIObject*	lifeNeedle;	//���C�t�̐j
	float	angle;			//�p�x
	float	maxAngle;		//�ő�p�x
	float	minAngle;		//�ŏ��p�x
	float	raito;			//����
	float	decreaseAmount;	//���炷��
	int		life;
	int		maxLife;
	float	timeCnt;
	bool	upDataFlag;	
};