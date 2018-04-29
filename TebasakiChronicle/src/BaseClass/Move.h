#pragma once
#include "K_Math\MyMathFanctions.h"

//-----------------------------------------------------
//Moveクラス
//概要:動作量を座標に与える
//製作者:日比野
//-----------------------------------------------------
class Move
{
public:
	Move();
	Move(const K_Math::Vector3& vec,float jumpPow, float fallSpeed, float gravity);
	~Move();

	//設定処理
	void	SetJumpPow(float jumpPow);
	void	SetFallSpeed(float fallSpeed);
	void	SetGravity(float gravity);

	void	SetMoveDate(
		const K_Math::Vector3& moveVec, const float& jumpPow,
		const float& fallSpeed, const float& gravity);

	//取得処理
	float	GetJumpPow();
	float	GetFallSpeed();
	float	GetGravity();

	//動作
	void	GravityOperation();	//重力動作
	void	MovingOperation();	//移動動作
	void	JumpOperation();	//ジャンプ動作

private:
	K_Math::Vector3		moveVec;		//1フレームで動く量
	float	jumpPower;		//ジャンプ力
	float	fallSpeed;		//落下速度
	float	gravity;		//重力加速度
};