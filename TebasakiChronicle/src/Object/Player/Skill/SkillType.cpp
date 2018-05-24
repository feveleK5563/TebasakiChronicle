#include "SkillType.h"

//�R���X�g���N�^
//!@brief �R���X�g���N�^
//!@param[in] �ő�g�p��
//!@param[in] �o������
//!@param[in] �p������
SkillType::SkillType(const int& maxUseNum, const float& appearDist, const int& continueTime)
	: maxUseNum(maxUseNum),appearDist(appearDist),continueTime(continueTime)
{

}


//-----------------------------------------------------------
//�f�X�g���N�^
//-----------------------------------------------------------
SkillType::~SkillType()
{

}



//-----------------------------------------------------------
//�X�V����
//-----------------------------------------------------------
void	SkillType::UpDate()
{

}


//�擾����
int		SkillType::GetContinueTime() const
{
	return continueTime;
}
float	SkillType::GetAppearDist() const
{
	return appearDist;
}
int		SkillType::GetMaxUseNum() const
{
	return maxUseNum;
}


