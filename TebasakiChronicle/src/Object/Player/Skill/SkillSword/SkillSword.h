#pragma once
#include "../src/Object/Player/Skill/SkillType.h"

//---------------------------------------------------------------
//�X�L���\�[�h
//�T�v:�؂�X�L���𔭓�
//�����:�����
//---------------------------------------------------------------
class SkillSword : public SkillType
{
public:
	//!@brief �R���X�g���N�^
	//!@param[in] �ő�g�p��
	//!@param[in] �o������
	//!@param[in] �p������
	SkillSword(const int& maxUseNum, const float& dist ,const int& continueTime_);

	~SkillSword();

	//!@brief �X�V����
	void	UpDate();

private:
};
