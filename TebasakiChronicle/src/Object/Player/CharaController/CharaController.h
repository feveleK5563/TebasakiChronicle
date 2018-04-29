#pragma once
#include "../src/BaseClass/Move.h"
#include "InputGLFW.h"

//--------------------------------------------------------------
//キャラクターコントローラー
//概要:キャラを操作する
//製作者:日比野
//--------------------------------------------------------------
class CharaController
{
public:
	CharaController();
	CharaController(K_Input::InputGLFW* input);
	~CharaController();

	void	UpDate();		//更新

private:
	//定数-------------------
	const float Friction = 0.9f;

	//変数-------------------
	Move*	move;					//移動
	K_Input::InputGLFW*	input;		//入力ボタン
	K_Math::Vector3 moveVec;		//移動量
};


