#include "GameObject.h"

//------------------------------------------------------------
//概要:ゲームオブジェクトの処理
//製作者:日比野
//------------------------------------------------------------

//---------------------------------------------
//コンストラクタ
//---------------------------------------------
GameObject::GameObject()
{

}

//---------------------------------------------
//デストラクタ
//---------------------------------------------
GameObject::~GameObject()
{

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

//画像の設定
void	GameObject::SetImage()
{

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
Status*	GameObject::GetStatus()
{
	return &status;
}

//移動の取得
Move*	GameObject::GetMove()
{
	return &move;
}

//画像の取得
ImageManager*	GameObject::GetImage()
{
	return image;
}

//イージングの取得
Easing*	GameObject::GetEasing()
{
	return &easing;
}