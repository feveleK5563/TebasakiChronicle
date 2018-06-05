#include "SkillJump.h"


//�R���X�g���N�^
SkillJump::SkillJump(const int& moveID,const int& maxUseNum, const float& dist, const int& continueTime,const int& attackPoint)
	: SkillType(moveID,maxUseNum,dist,continueTime,attackPoint)
{
	
}

//�f�X�g���N�^
SkillJump::~SkillJump()
{

}

//�X�V
void	SkillJump::UpDate(GameObject& object)
{
	object.GetMove().JumpOperation();
}

