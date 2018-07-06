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
	Move(const K_Math::Vector3& vec, float add, float jumpPow, float fallSpeed, float gravity);
	~Move();

	//設定処理
	void	SetAddVec(float addVec);
	void	SetJumpPow(float jumpPow);
	void	SetFallSpeed(float fallSpeed);
	void	SetGravity(float gravity);
	void	SetDefaultGravity();
	void	SetHorizontal(float horizontal);
	void	SetVertical(float vertical);

	void	SetMoveDate(
		const float& addVec, const float& jumpPow,
		const float& fallSpeed, const float& gravity);

	//取得処理
	K_Math::Vector3& GetMoveVec();
	float	GetAddVec();
	float	GetJumpPow();
	float	GetFallSpeed();
	float	GetGravity();
	float	GetHorizontalSpeed();

	//!@brief	落下速度の制御
	void	ControlFallSpeed();

	//動作
	void	GravityOperation(bool annulGravity);	//重力動作
	void	JumpOperation();						//ジャンプ動作
	void	Horizontal();		//水平移動
	void	Vertical();			//垂直移動

	//!@brief	水平移動の調節
	//!@brief	徐々に0にしていき、水平の移動をなくしていきます
	void	RegulationHorizon();

private:
	K_Math::Vector3		moveVec;		//移動量
	float				addVec;			//加算移動量(キャラクターの移動時に加算する値)
	float				jumpPower;		//ジャンプ力
	float				fallSpeed;		//落下速度
	float				defaultGravity;	//デフォルトの重力加速度
	float				gravity;		//重力加速度
	float				verticalPower;	//垂直の力
	float				horizontalPower;//水平の力
	float				verticalSpeed;	//垂直のスピード
	float				horizontalSpeed;//水平のスピード

	float				maxFallSpeed;		//最大落下速度
	float				maxverticalSpeed;	//最大垂直スピード
	float				maxhorizontalSpeed;	//最大水平スピード
};