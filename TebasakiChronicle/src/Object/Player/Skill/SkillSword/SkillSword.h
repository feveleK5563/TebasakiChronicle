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
	//!@param[in] continueTime_ 継続時間
	//!@param[in] distance_ 距離
	//!@param[in] appearPos_ 出現位置
	explicit SkillSword(const int& continueTime_, const float& distance_,
		GameObject& obj,const std::string& textureName,const AnimationCharaChip& animCharaChip);
	~SkillSword();

	//!@brief 更新処理
	void	UpDate();
	//!@brief 描画処理
	void	Render();

	//!@brief 自身が消える時間を計測
	//!@return 0秒になったらtrue
	bool	KillTime();

private:
};
