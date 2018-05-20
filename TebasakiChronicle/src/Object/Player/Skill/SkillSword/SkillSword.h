#pragma once
#include "../src/Object/Player/Skill/SkillType.h"

//---------------------------------------------------------------
//スキルソード
//概要:切るスキルを発動
//製作者:日比野
//---------------------------------------------------------------
class SkillSword : public SkillType
{
public:
	//!@brief コンストラクタ
	//!@param[in] 最大使用回数
	//!@param[in] 出現距離
	//!@param[in] 継続時間
	SkillSword(const int& maxUseNum, const float& dist ,const int& continueTime_);

	~SkillSword();

	//!@brief 更新処理
	void	UpDate();

private:
};
