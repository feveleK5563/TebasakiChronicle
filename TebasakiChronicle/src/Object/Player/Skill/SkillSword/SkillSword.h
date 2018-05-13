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
	//!@param[in] maxUseNum_ 最大使用回数
	//!@param[in] continueTime_ 継続時間
	//!@param[in] appearPos_ 出現位置
	explicit SkillSword(const int& maxUseNum_, const int& continueTime_, const K_Math::Vector3& appearPos_);
	
	void	UpDate();
	void	Render();
};