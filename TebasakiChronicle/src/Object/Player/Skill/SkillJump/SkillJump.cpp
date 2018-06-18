#include "SkillJump.h"


//コンストラクタ
SkillJump::SkillJump(const int& moveID,const int& maxUseNum, const float& dist, const int& continueTime,const int& attackPoint)
	: SkillType(moveID,maxUseNum,dist,continueTime,attackPoint)
{
	type = Type::MoveSkill;
	giveCollisionMask = CollisionMask::Non;
	reciveCollisionMask = CollisionMask::Non;
}

//デストラクタ
SkillJump::~SkillJump()
{

}

//更新
void	SkillJump::UpDate(GameObject& object)
{
	
}

