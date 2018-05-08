#include "CharaController.h"


//------------------------------------------------------------
//概要:キャラコントローラーの実装
//製作者:日比野
//------------------------------------------------------------


//-------------------------------------------------
//コンストラクタ
//-------------------------------------------------
CharaController::CharaController()
	
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
	float stickDepth = INPUT::GetStickPower(VpadIndex::Pad0,K_Input::VpadStick::L);
	//右方向を0度とした回転度
	float stickAngle = INPUT::GetStickRotation(VpadIndex::Pad0,K_Input::VpadStick::L);

	moveVec->x() += cosf(stickAngle) * stickDepth;	//スティックの角度方向に倒した分だけ進む
	moveVec->y() += sinf(stickAngle) * stickDepth;

	//傾きがない場合は、動かない(摩擦でゆっくり止まるようにする)
	if (stickDepth == 0)
	{
		moveVec->x() *= Friction;
		moveVec->y() *= Friction;
	}
	//INPUT::Run(VpadIndex::Pad0);				//入力処理を動かす
}




//移動ベクトルをセットする
void	CharaController::SetMoveVec(K_Math::Vector3* vec)
{
	this->moveVec = vec;
}

//移動ベクトルをもらい、操作する
void	CharaController::UpDate(K_Math::Vector3& vec)
{
	//左スティックの倒れている深さ
	float stickDepth = INPUT::GetStickPower(VpadIndex::Pad0,K_Input::VpadStick::L);
	//右方向を0度とした回転度
	float stickAngle = INPUT::GetStickRotation(VpadIndex::Pad0,K_Input::VpadStick::L);

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
		vec.x() = 0.0f;
	}
	vec.y() = 0;
	INPUT::Run(VpadIndex::Pad0);				//入力処理を動かす
}