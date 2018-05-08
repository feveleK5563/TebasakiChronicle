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
CharaController::CharaController(K_Input::InputClass* input)
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
	//コントローラーを作る
	input->AddGamePad(K_Input::VpadIndex::Pad0);

	//左スティックの倒れている深さ
	float stickDepth = input->GetPad(K_Input::VpadIndex::Pad0)->GetStickPower(K_Input::VpadStick::L);
	//右方向を0度とした回転度
	float stickAngle = input->GetPad(K_Input::VpadIndex::Pad0)->GetStickRotation(K_Input::VpadStick::L);

	K_Math::Vector3 moveVec = { 0,0,0 };
	moveVec.x() += cosf(stickAngle) * stickDepth * move->GetAddVec();	//スティックの角度方向に倒した分だけ進む

	//傾きがない場合は動作を停止する
	if (stickDepth == 0)
	{
		moveVec.x() = 0.f;
	}

	//moveクラスのmoveVecに移動量を加算する
	move->GetMoveVec() = moveVec;

	//ジャンプボタンを押す
	if (input->GetPad(K_Input::VpadIndex::Pad0)->IsPressButton(K_Input::VpadButton::R1))
	{
		move->JumpOperation();	//ジャンプ動作
	}

	//撮影ボタンを押す
	if (input->GetPad(K_Input::VpadIndex::Pad0)->IsStayButton(K_Input::VpadButton::L1))
	{
		//カメラマーカーを前に飛ばす
	}

	//move->GravityOperation();	//重力動作

	input->Run();				//入力処理を動かす
}



//InputClassの設定
//本来は、Inputはゲーム設定で行う
void	CharaController::SetInput()
{
	//コントローラーを作成
	input->AddGamePad(K_Input::VpadIndex::Pad0);

	//キーコンフィグをすることで入力を受け取る
	//スティックの[A,B,X,Y]を[Z,X,C,V]と連動させる
	input->GetPad(K_Input::VpadIndex::Pad0)->SetButtonConfig(K_Input::VpadButton::A, K_Input::JoyButton::Button0, K_Input::Key::Z);
	input->GetPad(K_Input::VpadIndex::Pad0)->SetButtonConfig(K_Input::VpadButton::B, K_Input::JoyButton::Button1, K_Input::Key::X);
	input->GetPad(K_Input::VpadIndex::Pad0)->SetButtonConfig(K_Input::VpadButton::X, K_Input::JoyButton::Button2, K_Input::Key::C);
	input->GetPad(K_Input::VpadIndex::Pad0)->SetButtonConfig(K_Input::VpadButton::Y, K_Input::JoyButton::Button3, K_Input::Key::V);

	//左スティックとArrowキーを連動させる
	input->GetPad(K_Input::VpadIndex::Pad0)->SetAxisConfig(K_Input::VpadAxis::Axis0, K_Input::JoyAxis::Axis0, K_Input::Key::ArrowRight, K_Input::Key::ArrowLeft);
	input->GetPad(K_Input::VpadIndex::Pad0)->SetAxisConfig(K_Input::VpadAxis::Axis1, K_Input::JoyAxis::Axis1, K_Input::Key::ArrowUp, K_Input::Key::ArrowDown);

	//仮想ゲームパッドの軸に割り当てスティックを作成
	input->GetPad(K_Input::VpadIndex::Pad0)->SetStickConfig(K_Input::VpadStick::L, K_Input::VpadAxis::Axis0, K_Input::VpadAxis::Axis1);
}