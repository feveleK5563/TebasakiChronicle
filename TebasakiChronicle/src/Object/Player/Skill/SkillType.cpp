#include "SkillType.h"

//コンストラクタ
//!@brief コンストラクタ
//!@param[in] 最大使用回数
//!@param[in] 出現距離
//!@param[in] 継続時間
SkillType::SkillType(const int& maxUseNum, const float& appearDist, const int& continueTime)
	: maxUseNum(maxUseNum),appearDist(appearDist),continueTime(continueTime)
{

}


//-----------------------------------------------------------
//デストラクタ
//-----------------------------------------------------------
SkillType::~SkillType()
{

}



//-----------------------------------------------------------
//更新処理
//-----------------------------------------------------------
void	SkillType::UpDate()
{

}


//取得処理
int		SkillType::GetContinueTime() const
{
	return continueTime;
}
float	SkillType::GetAppearDist() const
{
	return appearDist;
}
int		SkillType::GetMaxUseNum() const
{
	return maxUseNum;
}


