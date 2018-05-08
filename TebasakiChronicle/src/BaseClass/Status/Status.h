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
		Right = 0,
		Left = 180,
	};

	//状態
	enum State
	{
		Non,
		Active,
		Death,
	};

public:
	//一括設定処理
	void	SetStatusData(
		const State& state,const K_Math::Vector3& pos,
		const K_Math::Vector3& angle,const K_Math::Vector3& scale,
		const Direction& dir, const int& attackPoint,const int& life
	);


	//取得処理
	State&				GetState();
	K_Math::Vector3&	GetPos();
	K_Math::Vector3&	GetAngle();
	K_Math::Vector3&	GetScale();
	Direction&			GetDirection();
	int&				GetAttackPoint();
	int&				GetLife();

private:
	State				state;		//状態
	K_Math::Vector3		pos;		//座標
	K_Math::Vector3		angle;		//傾き
	K_Math::Vector3		scale;		//拡大縮小
	Direction			direction;	//向き
	int					attackPoint;//攻撃力
	int					life;		//体力
};