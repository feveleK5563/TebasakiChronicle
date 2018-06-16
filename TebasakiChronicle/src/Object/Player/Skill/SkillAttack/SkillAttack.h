#pragma once
#include "../src/Object/Player/Skill/SkillType.h"

//---------------------------------------------------------------
//�X�L���\�[�h
//�T�v:�؂�X�L���𔭓�
//�����:�����
//---------------------------------------------------------------
class SkillAttack : public SkillType
{
public:
	//!@brief �R���X�g���N�^
	//!@param[in] ����ID
	//!@param[in] �ő�g�p��
	//!@param[in] �o������
	//!@param[in] �p������
	//!@param[in] �U����
	SkillAttack(const int& moveID,const int& maxUseNum, const float& dist ,const int& continueTime_,const int& attackPoint);

	~SkillAttack();

	//!@brief �X�V����
	void	UpDate(GameObject& object);

private:
};


