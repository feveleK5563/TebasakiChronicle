#include "SkillSword.h"


//コンストラクタ
SkillSword::SkillSword(const int& continueTime_,const float& distance_ ,
	GameObject& obj,const std::string& textureName,const AnimationCharaChip& animCharaChip)
	: SkillType(continueTime_,distance_,obj,textureName,animCharaChip)
{
	
}

//デストラクタ
SkillSword::~SkillSword()
{
	
}

//更新
void	SkillSword::UpDate()
{
	this->continueTime--;
	this->skillObject->UpDate();
}

//描画
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

