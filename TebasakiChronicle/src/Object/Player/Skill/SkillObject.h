#pragma once
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
	
	//!@brief SkillTypeから情報をもらい当たり判定付きオブジェクトを生成
	//!@param[in] obj ゲームオブジェクトの参照
	//!@param[in] distance 距離
	//!@param[in] imageName 画像名
	//!@param[in] animCharaChip	アニメーションキャラチップ
	SkillObject(GameObject& obj,
				const float& distance,
				const std::string& imageName,
				const AnimationCharaChip& animCharaChip);

	~SkillObject();

	//!@brief SkillTypeに応じた効果処理
	void	SkillEffect();

	//!@brief 向きを返す
	//!@return -1.0fなら左,1.0fなら右
	float	GetDir();

	//!@brief 更新処理
	void	UpDate();

	//!@brief 描画処理
	void	Render();

private:
	GameObject					object;	//ゲームオブジェクト
	K_Physics::CollisionShape*	shape;	//ベースコリジョン
	CollisionManager		cManager;	//コリジョン管理者
};