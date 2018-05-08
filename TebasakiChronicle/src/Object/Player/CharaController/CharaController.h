#pragma once
#include "../src/BaseClass/Input/Input.h"
#include "../src/BaseClass/Move.h"

//--------------------------------------------------------------
//キャラクターコントローラー
//概要:キャラを操作する
//製作者:日比野
//--------------------------------------------------------------
class CharaController
{
public:
	CharaController();
	~CharaController();



	//1:参照した移動ベクトルを利用して、入力操作を行う
	void	UpDate(K_Math::Vector3& vec);

	//1:最初に動かすベクトルを設定してもらう
	//2:そのあとにUpDate()で設定したベクトルを動かす
	void	SetMoveVec(K_Math::Vector3* vec);
	void	UpDate();

private:
	//定数-------------------
	float Friction = 0.f;

	//変数-------------------
	Move*					move;		//移動
	K_Math::Vector3*		moveVec;	//移動量
};


