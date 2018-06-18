#include "GameObject.h"

//------------------------------------------------------------
//概要:ゲームオブジェクトの処理
//製作者:日比野
//------------------------------------------------------------

//---------------------------------------------
//コンストラクタ
//---------------------------------------------
GameObject::GameObject()
	:image(nullptr)
{

}

//---------------------------------------------
//デストラクタ
//---------------------------------------------
GameObject::~GameObject()
{
	if (image != nullptr)
	{
		delete image;
		image = nullptr;
	}
}


//---------------------------------------------
//設定処理
//---------------------------------------------
//ステータスの設定
void	GameObject::SetStatus()
{

}

//移動の設定
void	GameObject::SetMove(const Move* move)
{
	this->move = *move;
}

//画像管理者の生成
void	GameObject::SetImage(K_Graphics::Texture* tex, bool isde)
{
	if (image != nullptr)
		return;

	image = new ImageManager(tex, isde);
}

//サウンドの設定
void	GameObject::SetSound()
{

}

//イージングの設定
void	GameObject::SetEasing()
{

}


//---------------------------------------------
//取得処理
//---------------------------------------------
//ステータスの取得
Status&	GameObject::GetStatus()
{
	return status;
}

//移動の取得
Move&	GameObject::GetMove()
{
	return move;
}

//画像の取得
ImageManager&	GameObject::GetImage()
{
	return *image;
}

//イージングの取得
Easing&	GameObject::GetEasing()
{
	return easing;
}


//-------------------------------------------------------------
//設定処理
//内容:objectの[State]を設定する処理
//-------------------------------------------------------------

//[objectの位置]の設定
void	GameObject::SetPos(const K_Math::Vector3& vec)
{
	this->GetStatus().GetPos() = vec;
}

//[objectの傾き]の設定
void	GameObject::SetAngle(const K_Math::Vector3& vec)
{
	this->GetStatus().GetAngle() = vec;
}

//[objectの拡大縮小]の設定
void	GameObject::SetScale(const K_Math::Vector3& vec)
{
	this->GetStatus().GetScale() = vec;
}

//[objectの移動量]の設定
void	GameObject::SetMoveVec(const K_Math::Vector3& vec)
{
	this->GetMove().GetMoveVec() = vec;
}

//[objectの状態]の設定
void	GameObject::SetState(const Status::State& state)
{
	this->GetStatus().GetState() = state;
}

//[objectの向き]の設定
void	GameObject::SetDirection(const Status::Direction& dir)
{
	this->GetStatus().GetDirection() = dir;
}

//[objectの攻撃力]の設定
void	GameObject::SetAttackPoint(const int& atPoint)
{
	this->GetStatus().GetAttackPoint() = atPoint;
}

//[objectの体力]の設定
void	GameObject::SetLife(const int& life)
{
	this->GetStatus().GetLife() = life;
}


//--------------------------------------------------------------
//ステータスの取得処理
//内容:[objectのステータス]の取得
//--------------------------------------------------------------

//ステータスの取得
Status::State&		GameObject::GetState()
{
	return GetStatus().GetState();
}

//位置の取得
K_Math::Vector3&	GameObject::GetPos() 
{
	return GetStatus().GetPos();
}

//傾きの取得
K_Math::Vector3&	GameObject::GetAngle()
{
	return GetStatus().GetAngle();
}

//拡大縮小の取得
K_Math::Vector3&	GameObject::GetScale() 
{
	return GetStatus().GetScale();
}

//移動量の取得
K_Math::Vector3&	GameObject::GetMoveVec()
{
	return GetMove().GetMoveVec();
}

//向きの取得
Status::Direction&	GameObject::GetDirection()
{
	return GetStatus().GetDirection();
}

//攻撃力の取得
int&				GameObject::GetAttackPoint() 
{
	return GetStatus().GetAttackPoint();
}

//体力の取得
int&				GameObject::GetLife()
{
	return GetStatus().GetLife();
}


//---------------------------------------------------------
//!@brief	死んでいるかのチェック
//!@param[in]	ライフがない true あるなら false
bool	GameObject::IsDead()
{
	if (GetLife() <= 0)
	{
		return true;
	}
	return false;
}