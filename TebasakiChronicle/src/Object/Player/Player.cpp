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
	object.GetStatus().SetStatusData(
		Status::State::Active,
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(1, 1, 1),
		Status::Direction::Right,
		1,
		0
	);

	motion = Idle;
	motionCnt = 0;
	maxFrame = 60;

	//画像の生成
	object.SetImage("Player", CST::LoadAndGetTexture("Player", "data/image/resource2.png"), true);
	//Motionの状態の順番でなければアニメーションが対応しない
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 0, 32, 48), 6, 6, true);		//Idle
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 48, 32, 48), 10, 8, true);	//Walk
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 48, 32, 48), 10, 6, true);	//Run
	object.GetImage().CreateCharaChip(K_Math::Box2D(192, 0, 32, 48), 2, 1, false);	//Jump
	object.GetImage().CreateCharaChip(K_Math::Box2D(256, 0, 32, 48), 2, 3, false);	//Fall
	object.GetImage().CreateCharaChip(K_Math::Box2D(320, 0, 32, 48), 2, 6, false);	//TakeOff
	object.GetImage().CreateCharaChip(K_Math::Box2D(320, 0, 32, 48), 2, 6, false);	//Landing
	object.GetImage().CreateCharaChip(K_Math::Box2D(320, 48, 32, 48), 4, 4, false);	//SkillUse


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
	object.GetMove().GetMoveVec() = K_Math::Vector3(0, 0, 0);
	motionCnt++;

	ChangeDir();			//入力に応じて向きを変える
	//--------------------------------------------------------
	//思考&モーションの移動
	Think();
	Move();

	//カメラガン-----------------------
	ShotCameraGun();				//かめらがんを撃つ
	ReverseCameraGun();				//カメラがんを戻す
	cameraGun.UpDate(object.GetPos());

	//スキルの使用---------------------
	SkillBtnDown();
	skillManager.UpDate();

	//当たり判定動作-------------------
	cManager.MoveBaseCollision(object.GetMoveVec(), object.GetDirection(), false);

	//位置同期処理---------------------
	object.GetPos() = cManager.GetBaseCollisionObjectPosition();

	//アニメーション-------------------
	object.GetImage().Animation();
}

//-----------------------------------------------------------------
//描画
//-----------------------------------------------------------------
void	Player::Render()
{
	cameraGun.Render();
	object.GetImage().ImageDraw3D(object.GetPos(), object.GetAngle(), object.GetScale(), object.GetDirection());

	//スキルの描画----------------------------
	skillManager.Render();
}



//入力に応じて向きを変える
void	Player::ChangeDir()
{
	//左スティックの倒れている深さ
	float stickDepth = INPUT::GetStickPower(VpadIndex::Pad0, K_Input::VpadStick::L);
	//右方向を0度とした回転度
	float stickAngle = INPUT::GetStickRotation(VpadIndex::Pad0, K_Input::VpadStick::L);

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
		//---------------------------------------------------
		if (&cameraGun.GetSkillAndCharaChip() != nullptr)
		{
			skillManager.ChangeSkillFlag(true);
			//カメラガンからスキルデータを受け取る
			skillManager.ReceiveSkillAndCharaChip(cameraGun.GetSkillAndCharaChip());
		}
		//カメラマーカーをプレイヤーの位置に戻す
		cameraGun.SetCameraGun(false);
		cameraGun.object.SetState(Status::State::Non);
	}
}


//ジャンプ処理
void	Player::JumpMove()
{
	if (INPUT::IsPressButton(VpadIndex::Pad0,K_Input::VpadButton::R1))
	{
		object.GetMove().JumpOperation();
	}
}




//----------------------------------------------------------
//思考処理(モーション決定)
void	Player::Think()
{
	Motion nowMotion = motion;

	//モーションの変更のみを行う
	switch (nowMotion) {
	case Idle:	//待機
		if (controller.IsLStickInput()) { nowMotion = Walk; }
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::R1)) { nowMotion = TakeOff; }
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::A)) { nowMotion = SkillUse; }
		break;
	case Walk:	//歩く
		//1フレーム
		if (motionCnt >= maxFrame / 3)
		{
			nowMotion = Run;
		}
		if (!cManager.CheckHitSubCollisionObejct(Foot)) { nowMotion = Fall; }
		if (!controller.IsLStickInput()) { nowMotion = Idle; }
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::R1)) { nowMotion = TakeOff; }
		break;
	case Run:	//走る
		if (!cManager.CheckHitSubCollisionObejct(Foot)) { nowMotion = Fall; }
		if (!controller.IsLStickInput()) { nowMotion = Idle; }
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::R1)) { nowMotion = TakeOff; }
		break;
	case Jump:	//上昇中
		if (object.GetMove().GetFallSpeed() <= 0.0f) { nowMotion = Fall; }
		if (cManager.CheckHitSubCollisionObejct(Head)) { nowMotion = Fall; }
		break;
	case Fall:	//落下中
		if (cManager.CheckHitSubCollisionObejct(Foot)) { nowMotion = Landing; }
		break;
	case TakeOff:	//飛ぶ瞬間
		if (motionCnt >= maxFrame / maxFrame)
		{
			nowMotion = Jump;
		}
		break;
	case Landing:	//着地の瞬間
		if (motionCnt >= maxFrame / maxFrame)
		{
			nowMotion = Idle;
		}
	case SkillUse:	//スキル使用中
		if (motionCnt > maxFrame / 3)
		{
			nowMotion = Idle;
		}
	}
	//モーションの更新
	UpDateMotion(nowMotion);
}


//---------------------------------------------------
//モーションに対応した処理
void	Player::Move()
{
	//重力加速
	switch (motion) {
	default:

		//上昇中もしくは足元に地面がない
		if (object.GetMoveVec().y() > 0.0f ||
			!cManager.CheckHitSubCollisionObejct(Foot))
		{
			object.GetMove().GravityOperation(cManager.CheckHitSubCollisionObejct(Foot));
		}
		else //地面と接している
		{
			object.GetMoveVec().y() = 0.0f;
		}

		break;
		//重力を無効にするモーション(今はなし)
	case Non:
		break;
	}
	//移動 & カメラガンをSkillUse中は使用しない
	switch (motion) {
	default:

		controller.UpDate(object.GetMove());
		break;
		//移動操作を無視するモーション
	case SkillUse:
		//**********スキル使用中は移動をさせるかは未定**********
		break;
	}

	//-------------------------------------------------
	//モーション固有の処理
	switch (motion) {
	case Idle:		//待機
		break;
	case Walk:		//歩く
		break;
	case Run:		//走る
		break;
	case Jump:		//上昇中
		if (motionCnt == 0)
		{
			object.GetMove().JumpOperation();
		}
		break;
	case Fall:		//落下中
		break;
	case TakeOff:	//飛ぶ瞬間
		break;
	case Landing:	//着地
		break;
	case SkillUse:	//スキル使用中
		break;
	}
}


//------------------------------------------------
//モーションの更新
bool	Player::UpDateMotion(const Motion& nowMotion)
{
	if (motion == nowMotion) { return false; }
	//更新処理
	motion = nowMotion;
	motionCnt = 0;
	object.GetImage().ChangeAnimationPattern(motion, true);
	return true;
}




//!@brief スキルのためのボタン
void	Player::SkillBtnDown()
{
	//0番 = Y
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::Y))
	{
		skillManager.Process(0);
	}
	//1番 = X
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::X))
	{
		skillManager.Process(1);
	}
	//2番 = B
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::B))
	{
		skillManager.Process(2);
	}
	//3番 = A
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::A))
	{
		skillManager.Process(3);
	}
}