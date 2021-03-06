#include "CharaController.h"


//------------------------------------------------------------
//概要:キャラコントローラーの実装
//製作者:日比野
//------------------------------------------------------------


//-------------------------------------------------
//コンストラクタ
//-------------------------------------------------
CharaController::CharaController()
	: friction(0.0f),inputAngle(1.5f)
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

//移動ベクトルをもらい、操作する
void	CharaController::UpDate(Move& move)
{
	//左スティックの倒れている深さ
	float stickDepth = INPUT::GetStickPower(VpadIndex::Pad0,K_Input::VpadStick::L);
	//右方向を0度とした回転度
	float stickAngle = INPUT::GetStickRotation(VpadIndex::Pad0,K_Input::VpadStick::L);

	//横方向のみの移動
	if (stickDepth != 0)
	{
		//スティックの角度方向に倒した分だけ進む
		move.GetMoveVec().x = cosf(stickAngle) * stickDepth * move.GetAddVec();
	}
	else
	//傾きがない場合は、動かない(摩擦でゆっくり止まるようにする)
	{
		move.GetMoveVec().x *= friction;
	}
}


//------------------------------------------------------
//移動の入力スティックがおされているかの判定
bool	CharaController::IsLStickInput()
{
	float stickDepth = INPUT::GetStickPower(VpadIndex::Pad0, K_Input::VpadStick::L);
	float stickAngle = INPUT::GetStickRotation(VpadIndex::Pad0, K_Input::VpadStick::L);
	if (stickDepth == 0)
	{
		return false;
	}
	if (inputAngle < stickAngle && stickAngle < inputAngle + 0.1f)
	{
		return false;
	}
	if (-inputAngle - 0.1f < stickAngle && stickAngle < -inputAngle)
	{
		return false;
	}
	return true;
}

//!@brief	左入力が押されたか判断
bool	CharaController::IsStickLeft()
{
	//左スティックの倒れている深さ
	float stickDepth = INPUT::GetStickPower(VpadIndex::Pad0, K_Input::VpadStick::L);
	//右方向を0度とした回転度
	float stickAngle = INPUT::GetStickRotation(VpadIndex::Pad0, K_Input::VpadStick::L);

	if (stickDepth != 0 && K_Math::DegToRad(-90) != stickAngle && stickAngle != K_Math::DegToRad(90))
	{
		if (!((K_Math::DegToRad(-90) < stickAngle) && (stickAngle < K_Math::DegToRad(90))))
		{
			return true;
		}
	}
	return false;
}
//!@brief	右入力が押されたか判断
bool	CharaController::IsStickRight()
{
	//左スティックの倒れている深さ
	float stickDepth = INPUT::GetStickPower(VpadIndex::Pad0, K_Input::VpadStick::L);
	//右方向を0度とした回転度
	float stickAngle = INPUT::GetStickRotation(VpadIndex::Pad0, K_Input::VpadStick::L);
	if (stickDepth != 0 && K_Math::DegToRad(-90) != stickAngle && stickAngle != K_Math::DegToRad(90))
	{
		if ((K_Math::DegToRad(-90) < stickAngle) && (stickAngle < K_Math::DegToRad(90)))
		{
			return true;
		}
	}
	return false;
}