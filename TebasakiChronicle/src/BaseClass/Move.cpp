#include "Move.h"

//------------------------------------------------------
//概要:Moveクラスの処理内容
//製作者:日比野
//------------------------------------------------------


//------------------------------------------------------
//コンストラクタ
//------------------------------------------------------
Move::Move() :
	moveVec(K_Math::Vector3(0, 0, 0)),
	addVec(0.0f),
	jumpPower(0.0f),
	fallSpeed(0.0f),
	gravity(-0.5f)
{

}
Move::Move(const K_Math::Vector3& vec, float add, float jumpPow, float fallSpeed, float gravity) :
	moveVec(vec),
	addVec(add),
	jumpPower(jumpPow),
	fallSpeed(fallSpeed),
	gravity(gravity)
{

}

//------------------------------------------------------
//デストラクタ
//------------------------------------------------------
Move::~Move()
{

}


//------------------------------------------------------
//設定処理
//------------------------------------------------------
//加算移動量
void	Move::SetAddVec(float addVec)
{
	this->addVec = addVec;
}

//ジャンプ力の設定
void	Move::SetJumpPow(float jumpPow)
{
	this->jumpPower = jumpPow;
}

//落下速度の設定
void	Move::SetFallSpeed(float fallSpeed)
{
	this->fallSpeed = fallSpeed;
}

//重力加速度の設定
void	Move::SetGravity(float gravity)
{
	this->gravity = gravity;
}

//データの設定
void	Move::SetMoveDate(	const float& addVec, const float& jumpPow,
							const float& fallSpeed, const float& gravity)
{
	this->moveVec = K_Math::Vector3(0, 0, 0);
	this->addVec = addVec;
	this->jumpPower = jumpPow;
	this->fallSpeed = fallSpeed;
	this->gravity = gravity;
}


//------------------------------------------------------
//取得処理
//------------------------------------------------------
//動作量を取得(変更可能)
K_Math::Vector3& Move::GetMoveVec()
{
	return moveVec;
}

//加算移動量を取得
float	Move::GetAddVec()
{
	return addVec;
}

//ジャンプ力の取得
float	Move::GetJumpPow()
{
	return jumpPower;
}

//落下速度の取得
float	Move::GetFallSpeed()
{
	return fallSpeed;
}

//重力加速度の設定
float	Move::GetGravity()
{
	return gravity;
}


//------------------------------------------------------
//動作
//------------------------------------------------------
//重力動作
void	Move::GravityOperation(bool annulGravity)
{
	if (annulGravity == true)
	{
		moveVec.y() = 0;
		fallSpeed = 0;
		return;
	}

	moveVec.y() += fallSpeed;
	fallSpeed += gravity;
}

//ジャンプ動作
void	Move::JumpOperation()
{
	fallSpeed = jumpPower;

	//ジャンプの設定と同時にキャラクターを少し動かす
	moveVec.y() += fallSpeed;
}