#pragma once
#include "../src/BaseClass/Move.h"
#include "K_Input/InputClass.h"

//--------------------------------------------------------------
//キャラクターコントローラー
//概要:キャラを操作する
//製作者:日比野
//--------------------------------------------------------------
class CharaController
{
public:
	CharaController();
	CharaController(K_Input::InputClass* input);
	~CharaController();

	void	SetInput();		//InputClassの設定
	void	UpDate();		//更新

private:
	//定数-------------------
	//const float Friction = 0.9f;

	//変数-------------------
	Move*	move;					//移動
	K_Input::InputClass*	input;	//入力ボタン
};


