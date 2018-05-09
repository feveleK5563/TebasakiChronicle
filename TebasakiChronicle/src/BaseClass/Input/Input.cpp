#include "Input.h"

Input*	Input::inputInstance = nullptr;
//----------------------------------------------------
//インスタンスの取得
//----------------------------------------------------
Input*	Input::GetInstance()
{
	if (inputInstance == nullptr)
	{
		inputInstance = new Input();
	}
	return inputInstance;
}

Input*	input = Input::GetInstance();



//InputClassの取得
K_Input::InputClass*	Input::GetInput()
{
	return inputClass;
}

//InputClassのセット
void	Input::SetInputClass(InputClass* input)
{
	this->inputClass = input;
}


//-----------------------------------------------------------------------
//関数群
//-----------------------------------------------------------------------
namespace INPUT
{
	//InputClassの設定
	void	SetInputClass(InputClass* inputClass)
	{
		input->inputClass = inputClass;
		//input->SetInputClass(inputClass);
	}
	
	//ゲームパッドの追加
	bool	AddGamePad(const VpadIndex& padID)
	{
		input->GetInput()->AddGamePad(padID);
		return true;
	}

	//現在のゲームパッドの取得
	VirtualGamePad*	GetPad(const VpadIndex& padID)
	{
		return input->GetInput()->GetPad(padID);
	}

	//------------------------------------------------------
	//設定処理
	//------------------------------------------------------
	//ボタンの割り当ての設定
	void	SetButtonConfig(const VpadIndex& padID, const K_Input::VpadButton& padBtn, const K_Input::JoyButton& joyBtn, const K_Input::Key& keyBtn)
	{
		GetPad(padID)->SetButtonConfig(padBtn, joyBtn, keyBtn);
	}

	//スティックの軸の設定
	void	SetAxisConfig(const VpadIndex& padID, const K_Input::VpadAxis& axis1, const K_Input::JoyAxis& axis2, const K_Input::Key& key1, const K_Input::Key& key2)
	{
		GetPad(padID)->SetAxisConfig(axis1, axis2, key1, key2);
	}

	//スティックの設定
	void	SetStickConfig(const VpadIndex& padID, const K_Input::VpadStick& stick, const K_Input::VpadAxis& axis0, const K_Input::VpadAxis& axis1)
	{
		GetPad(padID)->SetStickConfig(stick, axis0, axis1);
	}

	//スティックの傾き度を返す
	float	GetStickPower(const VpadIndex& padID, const K_Input::VpadStick& padStick)
	{
		return GetPad(padID)->GetStickPower(padStick);
	}

	//スティックの角度を返す
	//右方向を0度とした回転度
	float	GetStickRotation(const VpadIndex& padID, const K_Input::VpadStick& padStick)
	{
		return GetPad(padID)->GetStickRotation(padStick);
	}

	//------------------------------------------------------------------------
	//ボタン判定処理
	//------------------------------------------------------------------------
	//押されたとき,true
	bool	IsPressButton(const VpadIndex& padID, const VpadButton& button)
	{
		if (GetPad(padID)->IsPressButton(button)) { return true; }
		return false;
	}
	//押している間,true
	bool	IsStayButton(const VpadIndex& padID, const VpadButton& button)
	{
		if (GetPad(padID)->IsStayButton(button)) { return true; }
		return false;
	}
	//離されたとき,true
	bool	IsReaveButton(const VpadIndex& padID, const VpadButton& button)
	{
		if (GetPad(padID)->IsReaveButton(button)) { return true; }
		return false;
	}

	//----------------------------------------------------------------------
	//デフォルト設定
	//----------------------------------------------------------------------
	//デフォルトのボタン配置などを設定する
	void	Config(const VpadIndex& padID)
	{
		//キーコンフィグをすることで入力を受け取る
		//スティックの[A,B,X,Y,L1,R1]を[Z,X,C,V,A,S]と連動させる
		SetButtonConfig(padID, VpadButton::A, JoyButton::Button0, Key::Z);
		SetButtonConfig(padID, VpadButton::B, JoyButton::Button1, Key::X);
		SetButtonConfig(padID, VpadButton::X, JoyButton::Button2, Key::C);
		SetButtonConfig(padID, VpadButton::Y, JoyButton::Button3, Key::V);
		SetButtonConfig(padID, VpadButton::L1, JoyButton::Button4, Key::A);
		SetButtonConfig(padID, VpadButton::R1, JoyButton::Button5, Key::S);

		//左スティックとArrowキーを連動させる
		SetAxisConfig(padID, VpadAxis::Axis0, JoyAxis::Axis0, Key::ArrowRight, Key::ArrowLeft);
		SetAxisConfig(padID, VpadAxis::Axis1, JoyAxis::Axis1, Key::ArrowUp, Key::ArrowDown);

		//仮想ゲームパッドの軸を割り当てる
		SetStickConfig(padID, VpadStick::L, VpadAxis::Axis0, VpadAxis::Axis1);
	}

	//入力情報を更新
	void	Run(const VpadIndex& padID)
	{
		GetPad(padID)->Run();
	}

	//デフォルトのInputを生成する
	void	Create(const VpadIndex& padID)
	{
		AddGamePad(padID);
		Config(padID);
	}
}