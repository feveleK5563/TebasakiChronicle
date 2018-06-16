#pragma once
#include "K_Math/MyMathFanctions.h"
#include "../BaseClass/Move.h"
#include "../BaseClass/easing.h"
#include "../BaseClass/Status/Status.h"
#include "../src/BaseClass/ImageManager/ImageManager.h"

//-------------------------------------------------------------
//ゲームオブジェクト
//概要:オブジェクトの必要最低限の機能を提供する
//製作者:日比野
//-------------------------------------------------------------
class GameObject
{
public:
	GameObject();
	~GameObject();

	//設定処理
	void	SetStatus();
	void	SetMove(const Move* move);
	void	SetImage(K_Graphics::Texture* tex, bool isde = true);
	void	SetSound();
	void	SetEasing();

	//取得処理
	Status&				GetStatus();
	Move&				GetMove();
	ImageManager&		GetImage();
	Easing&				GetEasing();

	//ステータスの設定
	void	SetPos(const K_Math::Vector3& vec);
	void	SetAngle(const K_Math::Vector3& vec);
	void	SetScale(const K_Math::Vector3& vec);
	void	SetMoveVec(const K_Math::Vector3& vec);
	void	SetState(const Status::State& state);
	void	SetDirection(const Status::Direction& dir);
	void	SetAttackPoint(const int& atPoint);
	void	SetLife(const int& life);

	//ステータスの取得処理
	Status::State&		GetState();
	K_Math::Vector3&	GetPos();
	K_Math::Vector3&	GetAngle();
	K_Math::Vector3&	GetScale();
	K_Math::Vector3&	GetMoveVec();
	Status::Direction&	GetDirection();
	int&				GetAttackPoint();
	int&				GetLife();

	//!@brief	死んでいるかのチェック
	//!@param[in]	ライフがない true あるなら false
	bool	IsDead();

private:
	Status			status;		//Status
	Move			move;		//移動処理
	ImageManager*	image;		//ImageManager
								//Sound
	Easing			easing;		//イージング
};