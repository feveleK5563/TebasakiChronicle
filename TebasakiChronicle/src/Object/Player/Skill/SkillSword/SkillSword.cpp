#include "SkillSword.h"


//�R���X�g���N�^
SkillSword::SkillSword(const int& moveID,const int& maxUseNum, const float& dist, const int& continueTime,const int& attackPoint)
	: SkillType(moveID,maxUseNum,dist,continueTime,attackPoint)
{
	type = Type::AttackSkill;
	giveCollisionMask = Status::CollisionMaskState::TakeDamageEnemy;
	reciveCollisionMask = Status::CollisionMaskState::None;
}

//�f�X�g���N�^
SkillSword::~SkillSword()
{
	
}

//�X�V
void	SkillSword::UpDate(GameObject& object)
{
	
}

