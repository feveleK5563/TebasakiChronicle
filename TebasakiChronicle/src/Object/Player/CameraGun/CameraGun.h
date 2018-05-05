#pragma once

#include "../src/Object/GameObject.h"
#include "K_Physics\BulletPhysics.h"

//----------------------------------------------------------------
//カメラガン
//概要:撮影用のカメラで、敵を撮影して、スキルを取得する
//製作者:日比野
//----------------------------------------------------------------
class CameraGun
{
public:
	CameraGun();
	CameraGun(const K_Math::Vector3& moveVec);
	~CameraGun();

	//****************************
	//1:向いている方向に移動するのは、Moveクラスが行う
	//2:衝突判定は、Collisionクラスが行う
	//3:追尾処理は問題ない
	//****************************
	void	MoveDir(const K_Math::Vector3& moveVec);	//向いている方向に移動
	void	Chase(const K_Math::Vector3& targetPos);	//追尾処理
	bool	HitCheck(const std::string& name);
	
	//仮処理
	void	Initailize();	//初期化処理
	void	UpDate();		//更新処理
	void	Render();		//描画

public:
	GameObject	object;	//ゲームオブジェクト
	bool		active;
private:

public:
	K_Math::Vector3	moveVec;
	K_Physics::BulletPhysics*	physics;	//物理BulletPhysics
	K_Physics::CollisionShape*	shape;		//形の作成
	K_Physics::CollisionData*	collision;	//コリジョン
	K_Physics::CollisionTag*	targetTag;	//ターゲットのコリジョンタグ

};