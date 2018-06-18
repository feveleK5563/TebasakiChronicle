#include "SkillMove.h"


//コンストラクタ
SkillMove::SkillMove(const int& moveID,const int& maxUseNum, const float& dist, const int& continueTime,const int& attackPoint)
	: SkillType(moveID,maxUseNum,dist,continueTime,attackPoint)
{
	type = Type::MoveSkill;
}

//デストラクタ
SkillMove::~SkillMove()
{

}

//更新
void	SkillMove::UpDate(GameObject& object)
{
	
}

