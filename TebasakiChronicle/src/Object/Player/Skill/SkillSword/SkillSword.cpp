#include "SkillSword.h"


//コンストラクタ
SkillSword::SkillSword(const int& moveID,const int& maxUseNum, const float& dist, const int& continueTime,const int& attackPoint)
	: SkillType(moveID,maxUseNum,dist,continueTime,attackPoint)
{
	type = Type::AttackSkill;
	giveCollisionMask = Status::CollisionMaskState::TakeDamageEnemy;
	reciveCollisionMask = Status::CollisionMaskState::None;
}

//デストラクタ
SkillSword::~SkillSword()
{
	
}

//更新
void	SkillSword::UpDate(GameObject& object)
{
	
}

