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
	//左スティックの倒れている深さ
	float stickDepth = input->GetPad(K_Input::VpadIndex::Pad0)->GetStickPower(K_Input::VpadStick::L);
	//右方向を0度とした回転度
	float stickAngle = input->GetPad(K_Input::VpadIndex::Pad0)->GetStickRotation(K_Input::VpadStick::L);

	moveVec->x() += cosf(stickAngle) * stickDepth;	//スティックの角度方向に倒した分だけ進む
	moveVec->y() += sinf(stickAngle) * stickDepth;

	//傾きがない場合は、動かない(摩擦でゆっくり止まるようにする)
	if (stickDepth == 0)
	{
		moveVec->x() *= Friction;
		moveVec->y() *= Friction;
	}
	input->Run();				//入力処理を動かす
}



//InputClassの設定
//本来は、Inputはゲーム設定で行う
void	CharaController::SetInput(K_Input::InputClass* in)
{
	input = in;	//取得

	//コントローラーを作成
	input->AddGamePad(K_Input::VpadIndex::Pad0);

	//キーコンフィグをすることで入力を受け取る
	//スティックの[A,B,X,Y,L1,R1]を[Z,X,C,V,A,S]と連動させる
	input->GetPad(K_Input::VpadIndex::Pad0)->SetButtonConfig(K_Input::VpadButton::A, K_Input::JoyButton::Button0, K_Input::Key::Z);
	input->GetPad(K_Input::VpadIndex::Pad0)->SetButtonConfig(K_Input::VpadButton::B, K_Input::JoyButton::Button1, K_Input::Key::X);
	input->GetPad(K_Input::VpadIndex::Pad0)->SetButtonConfig(K_Input::VpadButton::X, K_Input::JoyButton::Button2, K_Input::Key::C);
	input->GetPad(K_Input::VpadIndex::Pad0)->SetButtonConfig(K_Input::VpadButton::Y, K_Input::JoyButton::Button3, K_Input::Key::V);
	input->GetPad(K_Input::VpadIndex::Pad0)->SetButtonConfig(K_Input::VpadButton::L1, K_Input::JoyButton::Button4, K_Input::Key::A);
	input->GetPad(K_Input::VpadIndex::Pad0)->SetButtonConfig(K_Input::VpadButton::R1, K_Input::JoyButton::Button5, K_Input::Key::S);

	//左スティックとArrowキーを連動させる
	input->GetPad(K_Input::VpadIndex::Pad0)->SetAxisConfig(K_Input::VpadAxis::Axis0, K_Input::JoyAxis::Axis0, K_Input::Key::ArrowRight, K_Input::Key::ArrowLeft);
	input->GetPad(K_Input::VpadIndex::Pad0)->SetAxisConfig(K_Input::VpadAxis::Axis1, K_Input::JoyAxis::Axis1, K_Input::Key::ArrowUp, K_Input::Key::ArrowDown);

	//仮想ゲームパッドの軸に割り当てスティックを作成
	input->GetPad(K_Input::VpadIndex::Pad0)->SetStickConfig(K_Input::VpadStick::L, K_Input::VpadAxis::Axis0, K_Input::VpadAxis::Axis1);
}



//移動ベクトルをセットする
void	CharaController::SetMoveVec(K_Math::Vector3* vec)
{
	this->moveVec = vec;
}

void	CharaController::UpDate(K_Math::Vector3& vec)
{
	//左スティックの倒れている深さ
	float stickDepth = input->GetPad(K_Input::VpadIndex::Pad0)->GetStickPower(K_Input::VpadStick::L);
	//右方向を0度とした回転度
	float stickAngle = input->GetPad(K_Input::VpadIndex::Pad0)->GetStickRotation(K_Input::VpadStick::L);

	//横方向のみの移動
	if (stickDepth != 0)
	{
		//スティックの角度方向に倒した分だけ進む
		vec.x() = cosf(stickAngle) * stickDepth * 0.5f;
	}
	else
	//傾きがない場合は、動かない(摩擦でゆっくり止まるようにする)
	{
		vec.x() *= Friction;
		vec.y() *= Friction;

		vec.x() = 0;
		vec.y() = 0;
	}

	input->Run();				//入力処理を動かす
}