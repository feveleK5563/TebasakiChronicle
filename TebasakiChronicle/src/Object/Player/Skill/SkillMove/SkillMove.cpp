#include "SkillMove.h"


//�R���X�g���N�^
SkillMove::SkillMove(const int& moveID,const int& maxUseNum, const float& dist, const int& continueTime,const int& attackPoint)
	: SkillType(moveID,maxUseNum,dist,continueTime,attackPoint)
{
	type = Type::MoveSkill;
}

//�f�X�g���N�^
SkillMove::~SkillMove()
{

}

//�X�V
void	SkillMove::UpDate(GameObject& object)
{
	
}

