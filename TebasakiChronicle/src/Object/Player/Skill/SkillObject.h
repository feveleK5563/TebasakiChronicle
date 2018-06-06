#pragma once
#include "../src/Object/GameObject.h"
#include "../src/BaseClass/Collision/CollisionManager.h"
#include "../src/Object/TemporaryCollision/TemporaryCollisionManager.h"
#include "SkillType.h"
#include <memory>

class SkillType;
//--------------------------------------------------------------
//�X�L���I�u�W�F�N�g
//�T�v:�X�L���������A�����蔻���L�����`�b�v���o��������
//�����:�����
//--------------------------------------------------------------
class SkillObject
{
public:

	//!@brief SkillType����U�镑���𐶐�
	//!@brief SkillType �U�镑�����󂯎��
	//!@brief obj �Q�[���I�u�W�F�N�g�̎Q��
	SkillObject(std::shared_ptr<SkillType> skillType_, GameObject& obj,
		const std::string& imageName,
		const AnimationCharaChip& animCharaChip);

	~SkillObject();

public:
	//!@brief �X�V����
	void	UpDate(GameObject& gameObj);

	//!@brief �`�揈��
	void	Render();

	//!@brief �U�镑�����Z�b�g����
	//!@param[in] skillType_ �X�L���̂ӂ�܂�
	void	SetSkillType(std::shared_ptr<SkillType> skillType_);

	//!@brief �������ԓ������`�F�b�N
	//!@return �������ԓ��Ȃ�true
	bool	CheckSurvivalTime();



	//!@brief	1�񂾂��X�V������t���O�̃Z�b�g
	//!@param[in] oneFlag_	1�񂾂��X�V����Ȃ� true
	void	SetOneUpdateFlag(bool oneFlag_);

private:
	//!@brief ������Ԃ�
	//!@return -1.0f�Ȃ獶,1.0f�Ȃ�E
	float	GetDir();

	//!@brief	�X�V�������邩
	//!@return	�X�V����Ȃ� true ���Ȃ��Ȃ� false
	bool	OneProcess();

private:
	std::shared_ptr<SkillType>	skillType;		//�X�L������
	GameObject					object;			//�Q�[���I�u�W�F�N�g
	K_Physics::CollisionShape*	shape;			//�x�[�X�R���W����
	int							continueCnt;	//�p�����Ԍv��
	TemporaryCollisionManager	tempColManager;	//�e���|�����I�u�W�F�N�g


	bool	oneFlag;
	bool	upDateFlag;			//�X�V���邩�̃t���O
};