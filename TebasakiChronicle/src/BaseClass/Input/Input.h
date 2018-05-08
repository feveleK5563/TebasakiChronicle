#pragma once
#include "InputClass.h"

//----------------------------------------------------------------
//Inputクラス
//概要:Input処理をシングルトンにし、簡単に利用する
//製作者:日比野
//----------------------------------------------------------------
using namespace K_Input;
class Input
{
private:
	//-----------------------------------------------------
	//コンストラクタ
	//-----------------------------------------------------
	Input::Input() : inputClass(nullptr)
	{

	}

	//-----------------------------------------------------
	//デストラクタ
	//-----------------------------------------------------
	Input::~Input()
	{
		if (inputClass != nullptr)
		{
			delete inputClass;
			inputClass = nullptr;
		}
	}
	static Input*	inputInstance;

public:
	//インスタンスの取得
	static Input*	GetInstance();

	//インプットクラスの取得
	K_Input::InputClass*	GetInput();
	//インプットクラスのセット
	void	SetInputClass(InputClass* input);
public:
	K_Input::InputClass*	inputClass;
};



//関数群
namespace INPUT
{
	//インプットクラスの取得
	void	SetInputClass(InputClass* inputClass);
	//パッドの追加
	bool	AddGamePad(const VpadIndex& padID);
	//現在のゲームパッドを返す
	VirtualGamePad*	GetPad(const VpadIndex& padID);

	//[GamePad],[JoyStick],[Key]のそれぞれのボタン・軸・スティックの割り当て
	void	SetButtonConfig(const VpadIndex& padID, const K_Input::VpadButton& padBtn, const K_Input::JoyButton& joyBtn, const K_Input::Key& keyBtn);
	void	SetAxisConfig(const VpadIndex& padID, const K_Input::VpadAxis& axis1, const K_Input::JoyAxis& axis2, const K_Input::Key& key1, const K_Input::Key& key2);
	void	SetStickConfig(const VpadIndex& padID, const K_Input::VpadStick& stick, const K_Input::VpadAxis& axis0, const K_Input::VpadAxis& axis1);

	//スティックの傾きの度合い(0.0f～1.0f)を取得
	float	GetStickPower(const VpadIndex& padID, const K_Input::VpadStick& padStick);
	//スティックの傾き(右方向から0度)を取得
	float	GetStickRotation(const VpadIndex& padID, const K_Input::VpadStick& padStick);

	//ボタン状態判定用　[押されたとき],[押しているとき],[離したとき]にtrueを返す
	bool	IsPressButton(const VpadIndex& padID, const VpadButton& button);
	bool	IsStayButton(const VpadIndex& padID, const VpadButton& button);
	bool	IsReaveButton(const VpadIndex& padID, const VpadButton& button);

	//入力情報を更新
	void	Run(const VpadIndex& padID);

	//デフォルト設定用
	void	Create(const VpadIndex& padID);
	void	Config(const VpadIndex& padID);
}