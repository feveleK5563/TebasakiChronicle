#pragma once
#include "../src/Object/GameObject.h"
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

private:
	GameObject		object;		//ゲームオブジェクト
	CharaController	controller;	//コントローラー
	CameraGun		cameraGun;	//カメラガン
};