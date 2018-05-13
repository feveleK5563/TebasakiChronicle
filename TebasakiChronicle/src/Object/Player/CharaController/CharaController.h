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
	void	UpDate(Move& move);

	//スティック入力があったかを返す
	bool	IsLStickInput();
private:
	//定数-------------------
	float Friction = 0.f;
};


