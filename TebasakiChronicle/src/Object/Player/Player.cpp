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
	CC::RemoveCollisionShape(&shape);
	CC::RemoveCollisionShape(&shape2);
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
		0
	);

	//画像の生成
	object.SetImage("Player", CST::LoadAndGetTexture("Player", "data/image/resource2.png"), true);
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 0, 32, 48), 5, 6, true);
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 0, 160, 48), 4, 6, false);
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 48, 32, 48), 10, 6, true);

	//Moveの重力の設定
	object.GetMove().SetAddVec(2.f);
	object.GetMove().SetJumpPow(5.f);

	//カメラガンの初期化
	cameraGun.Initailize();

	//こりじょんの設定-------------------------------
	//ボックスの形の生成
	shape = CC::CreateBoxShape(16, 24, 1);
	shape2 = CC::CreateBoxShape(15, 1, 1);

	//生成した[形]でコリジョンや剛体を作成
	cManager.CreateBaseCollisionData(shape, object.GetPos(), object.GetAngle(), true);	//ベース
	cManager.CreateSubCollisionData(shape, CollisionMask::EnemyCollision | CollisionMask::TakeDamagePlayer, CollisionMask::PlayerCollision, object.GetPos()); //被ダメ
	cManager.CreateSubCollisionData(shape2, CollisionMask::Ground, CollisionMask::Non, K_Math::Vector3(0, -24, 0)); //足元
	cManager.CreateSubCollisionData(shape2, CollisionMask::Ground, CollisionMask::Non, K_Math::Vector3(0, 24, 0)); //頭上

	//コリジョンに情報を持たせる
	cManager.SetSubCollisionUserData(0, &object.GetStatus());
}

//更新
void	Player::UpDate()
{
	
	//動作をゼロクリア
	object.GetMove().GetMoveVec() = K_Math::Vector3(0, 0, 0);

	//重力動作
	object.GetMove().GravityOperation(cManager.CheckHitSubCollisionObejct(1));

	//ジャンプボタンを押す
	if (cManager.CheckHitSubCollisionObejct(1) &&
		INPUT::IsPressButton(VpadIndex::Pad0, K_Input::VpadButton::R1))
	{
		object.GetMove().JumpOperation();
	}

	//撮影ボタンを押すとカメラを前方に射出する
	if (INPUT::IsPressButton(VpadIndex::Pad0,K_Input::VpadButton::L1))
	{
		cameraGun.SetDirection(object.GetDirection());	//方向を同期させる
		cameraGun.SetCameraGun(true);
	}

	//撮影ボタンを離す
	if (INPUT::IsReaveButton(VpadIndex::Pad0,K_Input::VpadButton::L1))
	{
		//カメラマーカーをプレイヤーの位置に戻す
		cameraGun.SetCameraGun(false);
	}

	//入力に応じて向きを変える
	ChangeDir();

	//カメラガンの更新
	cameraGun.UpDate(object.GetPos());
	
	//コントローラーの更新
	controller.UpDate(object.GetMove());
	
	//コリジョンを動かす
	cManager.MoveBaseCollision(object.GetMoveVec(), object.GetDirection(), false);
	//プレイヤーとコリジョンの座標を同期させる
	object.GetPos() = cManager.GetBaseCollisionObjectPosition();
	//アニメーション
	object.GetImage().Animation();
}



//描画
void	Player::Render()
{
	cameraGun.Render();
	object.GetImage().ImageDraw3D(object.GetPos(), object.GetAngle(), object.GetScale(), object.GetDirection());
}




//入力に応じて向きを変える
void	Player::ChangeDir()
{
	//左スティックの倒れている深さ
	float stickDepth = INPUT::GetStickPower(VpadIndex::Pad0,K_Input::VpadStick::L);
	//右方向を0度とした回転度
	float stickAngle = INPUT::GetStickRotation(VpadIndex::Pad0,K_Input::VpadStick::L);

	if (stickDepth != 0)
	{
		if ((K_Math::DegToRad(-90) < stickAngle) && (stickAngle < K_Math::DegToRad(90)))
		{
			object.SetDirection(Status::Direction::Right);
		}
		else
		{
			object.SetDirection(Status::Direction::Left);
		}

		object.GetImage().ChangeAnimationPattern(2, true);
	}
	else
	{
		object.GetImage().ChangeAnimationPattern(0, true);
	}
}


//カメラガンを前に飛ばす
void	Player::ShotCameraGun()
{
	//撮影ボタンを押すとカメラを前方に射出する
	if (INPUT::IsPressButton(VpadIndex::Pad0,K_Input::VpadButton::L1))
	{
		cameraGun.SetDirection(object.GetDirection());	//方向を同期させる
		cameraGun.SetCameraGun(true);
		cameraGun.object.SetState(Status::State::Active);
	}
}

//カメラガンを元に戻す
void	Player::ReverseCameraGun()
{
	//撮影ボタンを離す
	if (INPUT::IsReaveButton(VpadIndex::Pad0,K_Input::VpadButton::L1))
	{
		//カメラマーカーをプレイヤーの位置に戻す
		cameraGun.SetCameraGun(false);
		cameraGun.object.SetState(Status::State::Non);
	}
}


//ジャンプ処理
void	Player::Jump()
{
	if (INPUT::IsPressButton(VpadIndex::Pad0,K_Input::VpadButton::R1))
	{
		object.GetMove().JumpOperation();
	}
}