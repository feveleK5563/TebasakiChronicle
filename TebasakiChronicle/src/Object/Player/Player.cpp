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
	object.GetStatus().SetStatusData(
		Status::State::Active,
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(1, 1, 1),
		Status::Direction::Right,
		1,
		0);
	object.GetMove().SetAddVec(2.f);

	//コントローラーの初期化
	controller.SetInput();

	//カメラガンの初期化
	cameraGun.Initailize();

	//画像管理の初期化
	object.SetImage("resource2", CST::GetTexture("resource2"), true);
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 0, 32, 48), 6, 10.f, true);
}

//更新
void	Player::UpDate()
{
	cameraGun.UpDate();			//カメラガンの更新
	controller.UpDate();		//入力処理の更新
	object.GetImage().Animation();
}

//描画
void	Player::Render()
{
	object.GetImage().ImageDraw3D(object.GetPos(), object.GetAngle(), object.GetScale(), object.GetDirection());
}