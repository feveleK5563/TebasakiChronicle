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
//一括設定処理
//---------------------------------------------------
void	Status::SetStatusData(const State& state, const K_Math::Vector3& pos,
	const K_Math::Vector3& angle, const K_Math::Vector3& scale,
	const Direction& dir, const int& attackPoint,const int& life)
{
	this->state = state;
	this->pos = pos;
	this->angle = angle;
	this->scale = scale;
	this->direction = dir;
	this->attackPoint = attackPoint;
	this->life = life;
}

//!@brief	最大Lifeの設定
//!@brief	maxLife_	最大Life
void	Status::SetMaxLife(const int maxLife_)
{
	maxLife = maxLife_;
}
//!@brief	最小Lifeの設定
//!@brief	minLife_	最小Life
void	Status::SetMinLife(const int minLife_)
{
	minLife = minLife_;
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
int&				Status::GetAttackPoint()
{
	return attackPoint;
}

//体力の取得
int&				Status::GetLife()
{
	return life;
}

//!@brief	最大体力の取得
//!@return	maxLife	最大Life
int&				Status::GetMaxLife()
{
	return maxLife;
}

//!@brief	最小体力の取得
//!@return	minLife	最小Life
int&				Status:: GetMinLife()
{
	return minLife;
}

