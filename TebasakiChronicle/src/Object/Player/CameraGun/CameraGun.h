#pragma once

#include "../src/Object/GameObject.h"
#include "K_Physics\BulletPhysics.h"
#include "../../../BaseClass/Collision/CollisionManager.h"

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

	//****************************
	//1:向いている方向に移動するのは、Moveクラスが行う
	//2:衝突判定は、Collisionクラスが行う
	//3:追尾処理は問題ない
	//****************************
	void	Chase(const K_Math::Vector3& targetPos);	//敵の座標をゆっくり追尾する
	void	RecieveData();
	bool	CheckUserData();

	void	Initailize();								//初期化処理
	void	UpDate(const K_Math::Vector3& pPos);		//更新処理
	void	Render();									//描画

	void	SetPlayerPos(const K_Math::Vector3& pos);	//プレイヤーの座標と同期する
	void	SetMoveVec(bool isInjection);				//カメラの速度の設定
	void	SetDirection(const Status::Direction& dir);	//向きの設定
	float 	GetDir();
	

private:
	bool	CheckNowState(const Status::State& state);	//現在の状態を調べる
	bool	CheckAddSpeed();

public:

	GameObject					object;			//ゲームオブジェクト
private:
	K_Physics::CollisionShape*	shape;			//形の作成
	CollisionManager			cManager;		//コリジョンの管理
	void*						targetUserData;	//ターゲットのスキルデータを格納する
};