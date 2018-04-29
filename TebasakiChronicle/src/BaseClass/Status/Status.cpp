#include "Status.h"

//-----------------------------------------------------------------
//ステータスの実装
//製作者:日比野
//-----------------------------------------------------------------

//---------------------------------------------------
//コンストラクタ
//---------------------------------------------------
Status::Status()
{

}

//---------------------------------------------------
//デストラクタ
//---------------------------------------------------
Status::~Status()
{

}


//---------------------------------------------------
//設定処理
//---------------------------------------------------
void	Status::SetStatusData(const State& state, const K_Math::Vector3& pos,
	const K_Math::Vector3& angle, const K_Math::Vector3& scale,
	const Direction& dir, const float& attackPoint)
{
	this->state = state;
	this->pos = pos;
	this->angle = angle;
	this->scale = scale;
	this->direction = dir;
	this->attackPoint = attackPoint;
}

//---------------------------------------------------
//取得処理
//---------------------------------------------------
//状態の取得
Status::State&	Status::GetState()
{
	return state;
}

//位置の取得
K_Math::Vector3&	Status::GetPos()
{
	return pos;
}

//傾きの取得
K_Math::Vector3&	Status::GetAngle()
{
	return angle;
}

//拡大縮小の取得
K_Math::Vector3&	Status::GetScale()
{
	return scale;
}

//向きの取得
Status::Direction&	Status::GetDirection()
{
	return direction;
}

//攻撃力の取得
float&				Status::GetAttackPoint()
{
	return attackPoint;
}

