#pragma once

#include "../src/Object/GameObject.h"
#include "K_Physics\BulletPhysics.h"
#include "../../../BaseClass/Collision/CollisionManager.h"
#include "../../Enemy/Enemy.h"

//----------------------------------------------------------------
//カメラガン
//概要:撮影用のカメラで、敵を撮影して、スキルを取得する
//製作者:日比野
//----------------------------------------------------------------
class CameraGun
{
public:
	CameraGun();
	~CameraGun();

	void	Chase(const K_Math::Vector3& targetPos);	//敵の座標をゆっくり追尾する
	void	RecieveData();
	bool	CheckUserData();

	void	Initailize();								//初期化処理
	void	UpDate(const K_Math::Vector3& pPos);		//更新処理
	void	Render();									//描画

	void	SetPlayerPos(const K_Math::Vector3& pos);	//プレイヤーの座標と同期する
	void	SetCameraGun(bool isInjection);				//カメラの速度の設定
	void	SetDirection(const Status::Direction& dir);	//向きの設定
	float 	GetDir();
	
	void	DataReset();

	//!@brief カメラガンが受け取ったスキルデータを渡す
	//!@return skillAndCharaChip スキルのデータ
	Enemy::SkillAndCharaChip& GetSkillAndCharaChip();

private:
	bool	CheckNowState(const Status::State& state);	//現在の状態を調べる
	bool	CheckAddSpeed();

public:

	GameObject					object;			//ゲームオブジェクト
private:
	K_Physics::CollisionShape*	shape;			//形の作成
	CollisionManager			cManager;		//コリジョンの管理

	int							targetNum;		//ターゲットの番号を格納する
	Enemy::SkillAndCharaChip*	targetData;		//ターゲットのスキルデータを格納する
};