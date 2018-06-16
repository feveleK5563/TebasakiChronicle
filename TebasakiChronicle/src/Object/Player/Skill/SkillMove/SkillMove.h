#pragma once
#include "../src/Object/Player/Skill/SkillType.h"

//---------------------------------------------------------------
//�X�L���W�����v
//�T�v:�W�����v����X�L���𔭓�
//�����:�����
//---------------------------------------------------------------
class SkillMove : public SkillType
{
public:
	//!@brief �R���X�g���N�^
	//!@param[in] ����ID
	//!@param[in] �ő�g�p��
	//!@param[in] �o������
	//!@param[in] �p������
	//!@param[in] �U����
	SkillMove(const int& moveID,const int& maxUseNum, const float& dist ,const int& continueTime_,const int& attackPoint);

	~SkillMove();

	//!@brief �X�V����
	void	UpDate(GameObject& object);

private:
};


