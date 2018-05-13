#pragma once
#include "SkillData.h"
#include "../src/Object/GameObject.h"
#include "../src/BaseClass/Collision/CollisionManager.h"

//--------------------------------------------------------------
//スキルオブジェクト
//概要:スキル生成時、当たり判定やキャラチップを出現させる
//製作者:日比野
//--------------------------------------------------------------
class SkillObject
{
public:
	explicit SkillObject(const SkillType& skillType_, const AnimationCharaChip& animCharaChip);
	~SkillObject();

	//!@brief SkillTypeに応じた効果処理
	void	SkillEffect();

	//!@brief SkillObject自身が消えるかの判断
	//!@return 消える時間が来たらtrue
	bool	CheckContinueTime();

	//!@brief 更新処理
	void	UpDate();

	//!@brief 描画処理
	void	Render();

private:
	GameObject					object;	//ゲームオブジェクト
	K_Physics::CollisionShape*	shape;	//ベースコリジョン
	CollisionManager		cManager;	//コリジョン管理者
	int						continueTime;	//継続時間
};