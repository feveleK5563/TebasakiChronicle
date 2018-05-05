#include "Player.h"


//--------------------------------------------------------------
//概要:プレイヤーの実装
//製作者:日比野
//--------------------------------------------------------------

//-----------------------------------------------
//コンストラクタ
//-----------------------------------------------
Player::Player()
{

}

//-----------------------------------------------
//デストラクタ
//-----------------------------------------------
Player::~Player()
{

}

//初期化
void	Player::Initliaze()
{
	//オブジェクトの初期化
	//-----まとめて処理をしたい--------
	K_Math::Vector3 vec = { 0,0,0 };
	object.GetStatus()->GetPos() = vec;
	object.GetStatus()->GetAngle() = vec;
	object.GetStatus()->GetScale() = K_Math::Vector3(1,1,1);
	object.GetStatus()->GetDirection() = Status::Direction::Left;
	object.GetStatus()->GetAttackPoint() = 1.0f;
	object.GetStatus()->GetState() = Status::State::Jump;

	//コントローラーの初期化

	//カメラガンの初期化
}

//更新
void	Player::UpDate()
{
	cameraGun.UpDate();			//カメラガンの更新
	controller.UpDate();		//入力処理の更新
}

//描画
void	Player::Render()
{

}