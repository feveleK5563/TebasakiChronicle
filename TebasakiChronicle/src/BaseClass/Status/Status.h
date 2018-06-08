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

	//コリジョンマスク
	enum CollisionMaskState
	{
		None = 0,
		Ground = 1 << 0,
		PlayerCollision = 1 << 1,
		EnemyCollision = 1 << 2,
		TakeDamagePlayer = 1 << 3,
		TakeDamageEnemy = 1 << 4,
		CameraGunCollision = 1 << 5,
		EnemyCamCollision = 1 << 6,
	};

public:
	//一括設定処理
	void	SetStatusData(
		const State& state,const K_Math::Vector3& pos,
		const K_Math::Vector3& angle,const K_Math::Vector3& scale,
		const Direction& dir, const int& attackPoint,const int& life
	);

	//!@brief	最大Lifeの設定
	//!@brief	maxLife_	最大Life
	void	SetMaxLife(const int maxLife_);
	//!@brief	最小Lifeの設定
	//!@brief	minLife_	最小Life
	void	SetMinLife(const int minLife_);

	//取得処理
	State&				GetState();
	K_Math::Vector3&	GetPos();
	K_Math::Vector3&	GetAngle();
	K_Math::Vector3&	GetScale();
	Direction&			GetDirection();
	int&				GetAttackPoint();
	int&				GetLife();
	int&				GetMaxLife();
	int&				GetMinLife();

private:
	State				state;		//状態
	K_Math::Vector3		pos;		//座標
	K_Math::Vector3		angle;		//傾き
	K_Math::Vector3		scale;		//拡大縮小
	Direction			direction;	//向き
	int					attackPoint;//攻撃力
	int					life;		//体力
	int					maxLife;	//最大life
	int					minLife;	//最小life
};