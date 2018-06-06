#pragma once
#include "../src/Object/GameObject.h"
#include "../src/BaseClass/Collision/CollisionManager.h"
#include "../src/Object/TemporaryCollision/TemporaryCollisionManager.h"
#include "SkillType.h"
#include <memory>

class SkillType;
//--------------------------------------------------------------
//スキルオブジェクト
//概要:スキル生成時、当たり判定やキャラチップを出現させる
//製作者:日比野
//--------------------------------------------------------------
class SkillObject
{
public:

	//!@brief SkillTypeから振る舞いを生成
	//!@brief SkillType 振る舞いを受け取る
	//!@brief obj ゲームオブジェクトの参照
	SkillObject(std::shared_ptr<SkillType> skillType_, GameObject& obj,
		const std::string& imageName,
		const AnimationCharaChip& animCharaChip);

	~SkillObject();

public:
	//!@brief 更新処理
	void	UpDate(GameObject& gameObj);

	//!@brief 描画処理
	void	Render();

	//!@brief 振る舞いをセットする
	//!@param[in] skillType_ スキルのふるまい
	void	SetSkillType(std::shared_ptr<SkillType> skillType_);

	//!@brief 生存時間内かをチェック
	//!@return 生存時間内ならtrue
	bool	CheckSurvivalTime();



	//!@brief	1回だけ更新させるフラグのセット
	//!@param[in] oneFlag_	1回だけ更新するなら true
	void	SetOneUpdateFlag(bool oneFlag_);

private:
	//!@brief 向きを返す
	//!@return -1.0fなら左,1.0fなら右
	float	GetDir();

	//!@brief	更新し続けるか
	//!@return	更新するなら true しないなら false
	bool	OneProcess();

private:
	std::shared_ptr<SkillType>	skillType;		//スキル動作
	GameObject					object;			//ゲームオブジェクト
	K_Physics::CollisionShape*	shape;			//ベースコリジョン
	int							continueCnt;	//継続時間計測
	TemporaryCollisionManager	tempColManager;	//テンポラリオブジェクト


	bool	oneFlag;
	bool	upDateFlag;			//更新するかのフラグ
};