#include "SkillSword.h"


//�R���X�g���N�^
SkillSword::SkillSword(const int& continueTime_,const float& distance_ ,
	GameObject& obj,const std::string& textureName,const AnimationCharaChip& animCharaChip)
	: SkillType(continueTime_,distance_,obj,textureName,animCharaChip)
{
	
}

//�f�X�g���N�^
SkillSword::~SkillSword()
{
	
}

//�X�V
void	SkillSword::UpDate()
{
	this->continueTime--;
	this->skillObject->UpDate();
}

//�`��
void	SkillSword::Render()
{
	this->skillObject->Render();
}


bool	SkillSword::KillTime()
{
	if (continueTime <= 0)
	{
		return true;
	}
	return false;
}

