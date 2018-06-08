#pragma once
#include "../src/Object/GameObject.h"
#include "../src/BaseClass/ImageManager/ImageManager.h"


//---------------------------------------------------------------------
//�T�v: GUI�̃I�u�W�F�N�g(�P�̂̂���)
//�����: �����
//---------------------------------------------------------------------
class GUIObject
{
public:
	//!@brief �R���X�g���N�^
	//!@param[in] imageName_ �摜��
	//!@param[in] pos_	�ʒu
	//!@param[in] srcBox_ �摜���̃T�C�Y
	GUIObject(const std::string& imageName_,
		const K_Math::Vector3& pos_,
		const K_Math::Box2D& srcBox_);

	//!@brief �f�X�g���N�^
	~GUIObject();
	//!@brief �X�V����
	void	UpDate();
	//!@brief 2D��Ԃɕ`�悷��
	void	Render();
	//!@brief	3D��Ԃɕ`�悷��
	void	Render3D();

	//!@brief �ʒu�̐ݒ�
	//!@param[in] pos_ �ړ�������ʒu
	void	SetPos(const K_Math::Vector3& pos_);

	//!@brief	�ʒu�̈ړ�
	//!@param[in] moveVec �ړ���
	void	AddVec(const K_Math::Vector3& moveVec);

	//!@brief	�傫���̐ݒ�
	//!@param[in]	scale �傫��
	void	SetScale(const K_Math::Vector3& scale);

	//!@brief	GameObject�̎擾
	//!@return	�Q�[���I�u�W�F�N�g
	GameObject&	GetGameObject();

	//!@brief	��]���x�̐ݒ�
	//!@param[in]	ratateSpeed_ ��]���x
	void		SetRotateSpeed(const float rotateSpeed_);
private:
	K_Graphics::Texture*	texture;
	GameObject		object;		//�I�u�W�F�N�g
	std::string		imageName;	//�摜��
	K_Math::Box2D	srcBox;		//�摜���̃T�C�Y
	float			rotateSpeed;	//��]���x
};