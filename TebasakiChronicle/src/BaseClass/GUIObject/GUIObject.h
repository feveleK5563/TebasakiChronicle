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
	GUIObject(	const std::string& imageName_,
				const K_Math::Vector3& pos_,
				const K_Math::Box2D& srcBox_);

	//!@brief �f�X�g���N�^
	~GUIObject();
	//!@brief �X�V����
	void	UpDate();
	//!@brief �`�揈��
	void	Render();

	//!@brief �ʒu�̈ړ�����
	//!@param[in] pos_ �ړ�������ʒu
	void	SetPos(const K_Math::Vector3& pos_);

private:
	K_Graphics::Texture*	texture;
	GameObject		object;		//�I�u�W�F�N�g
	std::string		imageName;	//�摜��
	K_Math::Box2D	srcBox;		//�摜���̃T�C�Y
};