#pragma once
#include "../src/Object/GameObject.h"
#include "../src/BaseClass/Collision/CollisionManager.h"

//--------------------------------------------------------------
//�X�L���I�u�W�F�N�g
//�T�v:�X�L���������A�����蔻���L�����`�b�v���o��������
//�����:�����
//--------------------------------------------------------------
class SkillObject
{
public:
	
	//!@brief SkillType����������炢�����蔻��t���I�u�W�F�N�g�𐶐�
	//!@param[in] obj �Q�[���I�u�W�F�N�g�̎Q��
	//!@param[in] distance ����
	//!@param[in] imageName �摜��
	//!@param[in] animCharaChip	�A�j���[�V�����L�����`�b�v
	SkillObject(GameObject& obj,
				const float& distance,
				const std::string& imageName,
				const AnimationCharaChip& animCharaChip);

	~SkillObject();

	//!@brief SkillType�ɉ��������ʏ���
	void	SkillEffect();

	//!@brief ������Ԃ�
	//!@return -1.0f�Ȃ獶,1.0f�Ȃ�E
	float	GetDir();

	//!@brief �X�V����
	void	UpDate();

	//!@brief �`�揈��
	void	Render();

private:
	GameObject					object;	//�Q�[���I�u�W�F�N�g
	K_Physics::CollisionShape*	shape;	//�x�[�X�R���W����
	CollisionManager		cManager;	//�R���W�����Ǘ���
};