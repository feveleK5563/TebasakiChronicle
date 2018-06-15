#pragma once
#include "../src/Object/GameObject.h"
#include "../src/BaseClass/GUIObject/GUIObject.h"

//---------------------------------------------------------------------
//�T�v: �Q�[�W������GUI�I�u�W�F�N�g(�P�̂̂���)
//�����: �����
//---------------------------------------------------------------------
class GageGui 
{
public:
	//!@brief	�R���X�g���N�^
	GageGui();
	//!@brief	�f�X�g���N�^
	~GageGui();

	//!@brief	�������Z�o����
	void		Raito(float maxValue,float nowValue,float raito);

	//!@brief	�ʒu�Ɋ�����K�p����
	void		ProcessPos();
	//!@brief	�p�x�Ɋ�����K�p����
	void		ProcessRotation();
	//!@brief	�傫��������K�p����
	void		ProcessScale();

	//!@brief	�X�V
	void		UpDate();
	//!@brief	�`��
	void		Render();

private:
	//!@brief	�ʒu���w�肵����������
	void	AddMove(float moveAmount);
	//!@brief	��]�ʂ�^����
	void	AddRotation(float angleAmount);
	//!@brief	�o��
	void	Appear();

	//!@brief	�ʒu�̈ړ�
	void	Move();
	//!@brief	��]
	void	Rotate();

private:
	GUIObject		frame;			//�g
	GUIObject		backGround;		//���ɔz�u����Q�[�W
	GUIObject		fillAreaBox;	//��ɔz�u����Q�[�W

private:
	float			nowGagePos;		//�Q�[�W�̌��݈ʒu
	int				moveMotion;
};