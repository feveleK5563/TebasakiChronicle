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

	//!@brief	�`��
	void		Render();
private:
	GUIObject	guiObject;	//GUI�I�u�W�F�N�g
	float		result;
	float		baseAngle;
};