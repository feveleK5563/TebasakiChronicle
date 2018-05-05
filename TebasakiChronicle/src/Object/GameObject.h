#pragma once
#include "K_Math/MyMathFanctions.h"
#include "../BaseClass/Move.h"
#include "../BaseClass/easing.h"
#include "../BaseClass/Status/Status.h"
#include "../src/BaseClass/ImageManager/ImageManager.h"

//-------------------------------------------------------------
//ゲームオブジェクト
//概要:オブジェクトの必要最低限の機能を提供する
//製作者:日比野
//-------------------------------------------------------------
class GameObject
{
public:
	GameObject();
	~GameObject();

	//設定処理
	void	SetStatus();
	void	SetMove(const Move* move);
	void	SetImage();
	void	SetSound();
	void	SetEasing();

	//取得処理
	Status*				GetStatus();
	Move*				GetMove();
	ImageManager*		GetImage();
	Easing*				GetEasing();

	
private:
	Status			status;		//Status
	Move			move;		//移動処理
	ImageManager*	image;		//ImageManager
								//Sound
	Easing			easing;		//イージング
};