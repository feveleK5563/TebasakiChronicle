#pragma once
//#include "../src/Object/GameObject.h"
#include "../src/Object//Player/CameraGun/CameraGun.h"
#include "../src/Object/Player/CharaController/CharaController.h"

//--------------------------------------------------------------------
//プレイヤー
//概要:プレイヤー専用のもの
//製作者:日比野
//--------------------------------------------------------------------
class Player
{
public:
	Player();
	~Player();

	//仮の大きな処理
	void	Initliaze();	//初期化
	void	UpDate();		//更新
	void	Render();		//描画

	//カメラガンのスキルを取得する
	void	SetSkillData();

	//InputClassの取得処理
	void	GetInputClass(K_Input::InputClass* input);

	//カメラガンを生成する
	void	CreateCameraGun();

private:
	GameObject		object;		//ゲームオブジェクト
	CharaController	controller;	//コントローラー
public:
	CameraGun		cameraGun;	//カメラガン
	
	K_Input::InputClass*		input;		//InputClass


public:
	K_Physics::BulletPhysics*	physics;	//物理BulletPhysics
	K_Physics::CollisionShape*	shape;		//形の作成
	K_Physics::CollisionData*	collision;	//コリジョン
	K_Physics::CollisionTag*	targetTag;	//ターゲットのコリジョンタグ
};