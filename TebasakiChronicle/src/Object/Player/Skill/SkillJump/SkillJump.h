#pragma once
#include "../src/Object/Player/Skill/SkillType.h"

//---------------------------------------------------------------
//スキルジャンプ
//概要:ジャンプするスキルを発動
//製作者:日比野
//---------------------------------------------------------------
class SkillJump : public SkillType
{
public:
	//!@brief コンストラクタ
	//!@param[in] 動作ID
	//!@param[in] 最大使用回数
	//!@param[in] 出現距離
	//!@param[in] 継続時間
	//!@param[in] 攻撃力
	SkillJump(const int& moveID,const int& maxUseNum, const float& dist ,const int& continueTime_,const int& attackPoint);

	~SkillJump();

	//!@brief 更新処理
	void	UpDate(GameObject& object);

private:
};


