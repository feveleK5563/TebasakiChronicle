#pragma once

#include "../src/Object/GameObject.h"

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
	void	MoveDir(const K_Math::Vector3& moveVec);	//向いている方向に移動
	bool	HitEnemy();									//敵と衝突したかの判定
	void	Chase(const K_Math::Vector3& targetPos);	//追尾処理

	
	//仮処理
	void	Initailize();	//初期化処理
	void	UpDate();		//更新処理
	void	Render();		//描画

private:
	GameObject	object;	//ゲームオブジェクト
	bool		active;
};