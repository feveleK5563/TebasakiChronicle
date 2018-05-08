#pragma once
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


	//カメラガンを生成する
	void	CreateCameraGun();

private:
	void	ChangeDir();		//入力に応じて向きを変える
	void	ShotCameraGun();	//カメラガンを飛ばす
	void	ReverseCameraGun();	//カメラガンを戻す
	void	Jump();				//ジャンプ

private:
	GameObject		object;		//ゲームオブジェクト
	CharaController	controller;	//コントローラー
public:
	CameraGun		cameraGun;	//カメラガン

public:
	K_Physics::CollisionShape*	shape;		//形の作成
	CollisionManager			cManager;	//コリジョンの管理者
};