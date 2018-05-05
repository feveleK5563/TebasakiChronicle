#pragma once
#include "K_Math/MyMathFanctions.h"

//---------------------------------------------------------------------
//ステータスクラス
//概要:ステータスを保持している
//製作者:日比野
//---------------------------------------------------------------------
class Status
{
public:
	Status();
	~Status();

public:
	//向き
	enum Direction
	{
		Left = 90,
		Right = 180,
	};

	//状態
	enum State
	{
		Walk,
		Run,
		Jump
	};

public:
	//設定処理
	void	SetStatusData(
		const State& state,const K_Math::Vector3& pos,
		const K_Math::Vector3& angle,const K_Math::Vector3& scale,
		const Direction& dir,const float& attackPoint,const int& life
	);


	//取得処理
	State&				GetState();
	K_Math::Vector3&	GetPos();
	K_Math::Vector3&	GetAngle();
	K_Math::Vector3&	GetScale();
	K_Math::Vector3&	GetMoveVec();
	Direction&			GetDirection();
	float&				GetAttackPoint();
	int&				GetLife();

private:
	State				state;		//状態
	K_Math::Vector3		pos;		//座標
	K_Math::Vector3		angle;		//傾き
	K_Math::Vector3		scale;		//拡大縮小
	K_Math::Vector3		moveVec;	//移動量
	Direction			direction;	//向き
	float				attackPoint;//攻撃力
	int					life;		//体力
};