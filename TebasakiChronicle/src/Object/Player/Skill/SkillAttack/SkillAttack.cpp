#include "SkillAttack.h"


//コンストラクタ
SkillAttack::SkillAttack(const int& moveID,const int& maxUseNum, const float& dist, const int& continueTime,const int& attackPoint)
	: SkillType(moveID,maxUseNum,dist,continueTime,attackPoint)
{
	type = Type::AttackSkill;
}

//デストラクタ
SkillAttack::~SkillAttack()
{
	
}

//更新
void	SkillAttack::UpDate(GameObject& object)
{
	
}

