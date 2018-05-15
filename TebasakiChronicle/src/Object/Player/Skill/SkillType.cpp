#include "SkillType.h"


//-----------------------------------------------------------
//コンストラクタ
//-----------------------------------------------------------
SkillType::SkillType(const int& continueTime_, const float& distance_,
	GameObject& obj,const std::string& textureName,const AnimationCharaChip& animCharaChip)
	: continueTime(continueTime_), distance(distance_),appearPos(obj.GetPos())
{
	skillObject = new SkillObject(obj,distance,textureName,animCharaChip);
	std::cout << "SkillObjectを生成しました" << std::endl;
}

//-----------------------------------------------------------
//デストラクタ
//-----------------------------------------------------------
SkillType::~SkillType()
{
	if (skillObject != nullptr)
	{
		delete skillObject;
		skillObject = nullptr;
		std::cout << "SkillObjectを消去しました" << std::endl;
	}
}



//-----------------------------------------------------------
//更新処理
//-----------------------------------------------------------
void	SkillType::UpDate()
{

}

//-----------------------------------------------------------
//描画処理
//-----------------------------------------------------------
void	SkillType::Render()
{

}

