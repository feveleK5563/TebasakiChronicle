#include "SkillAttack.h"


//�R���X�g���N�^
SkillAttack::SkillAttack(const int& moveID,const int& maxUseNum, const float& dist, const int& continueTime,const int& attackPoint)
	: SkillType(moveID,maxUseNum,dist,continueTime,attackPoint)
{
	type = Type::AttackSkill;
}

//�f�X�g���N�^
SkillAttack::~SkillAttack()
{
	
}

//�X�V
void	SkillAttack::UpDate(GameObject& object)
{
	
}

