#include "SkillJump.h"


//�R���X�g���N�^
SkillJump::SkillJump(const int& moveID,const int& maxUseNum, const float& dist, const int& continueTime,const int& attackPoint)
	: SkillType(moveID,maxUseNum,dist,continueTime,attackPoint)
{
	type = Type::MoveSkill;
	giveCollisionMask = Status::CollisionMaskState::None;
	reciveCollisionMask = Status::CollisionMaskState::None;
}

//�f�X�g���N�^
SkillJump::~SkillJump()
{

}

//�X�V
void	SkillJump::UpDate(GameObject& object)
{
	
}

