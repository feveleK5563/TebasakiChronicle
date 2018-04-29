#include "CharaController.h"


//------------------------------------------------------------
//概要:キャラコントローラーの実装
//製作者:日比野
//------------------------------------------------------------


//-------------------------------------------------
//コンストラクタ
//-------------------------------------------------
CharaController::CharaController()
	: input(nullptr)
{

}
CharaController::CharaController(K_Input::InputGLFW* input)
	: input(input)
{

}

//-------------------------------------------------
//デストラクタ
//-------------------------------------------------
CharaController::~CharaController()
{

}


//-------------------------------------------------
//更新処理
//-------------------------------------------------
void	CharaController::UpDate()
{
	//左スティック(キーボードではArrowキー)
	//横軸の大きさと左右(-1.0f～1.0f)がわかる
	float value = input->GetStickState(K_Input::VpadStick::L);	
	//止まるときは[value]が[0]のとき
	if (value == 0) { moveVec.x() *= Friction; }

	//ジャンプボタンを押す
	if (input->isPressButton(K_Input::VpadButton::R1))
	{
		move->JumpOperation();	//ジャンプ動作
	}

	//撮影ボタンを押す(カメラマーカーを前に飛ばす)
	if (input->isStayButton(K_Input::VpadButton::L1))
	{

	}

	move->GravityOperation();	//重力動作

	input->Run();				//入力処理を動かす
}