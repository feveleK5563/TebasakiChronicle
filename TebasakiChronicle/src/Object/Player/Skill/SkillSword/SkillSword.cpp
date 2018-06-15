#include "SkillSword.h"


//コンストラクタ
SkillSword::SkillSword(const int& moveID,const int& maxUseNum, const float& dist, const int& continueTime,const int& attackPoint)
	: SkillType(moveID,maxUseNum,dist,continueTime,attackPoint)
{
	type = Type::AttackSkill;
	giveCollisionMask = CollisionMask::TakeDamageEnemy;
	reciveCollisionMask = CollisionMask::Non;
}

//デストラクタ
SkillSword::~SkillSword()
{
	
}

//更新
void	SkillSword::UpDate(GameObject& object)
{
	
}

