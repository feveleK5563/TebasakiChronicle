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
	enemyData = nullptr;
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
		10
		);

	motion = Idle;
	motionCnt = 0;
	maxFrame = 60;
	minJumpForce = 1.5f;
	invicibleCnt = 0;
	maxInvicibleTime = 300;	//300フレーム無敵時間
	object.GetStatus().SetMinLife(0);
	object.GetStatus().SetMaxLife(10);

	//画像の生成
	object.SetImage(CST::LoadAndGetTexture("Player", "data/image/resource2.png"), true);
	//Motionの状態の順番でなければアニメーションが対応しない
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 0, 32, 48), 6, 6, true);		//Idle
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 48, 32, 48), 10, 8, true);	//Walk
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 48, 32, 48), 10, 6, true);	//Run
	object.GetImage().CreateCharaChip(K_Math::Box2D(192, 0, 32, 48), 2, 1, false);	//Jump
	object.GetImage().CreateCharaChip(K_Math::Box2D(256, 0, 32, 48), 2, 3, false);	//Fall
	object.GetImage().CreateCharaChip(K_Math::Box2D(320, 0, 32, 48), 2, 6, false);	//TakeOff
	object.GetImage().CreateCharaChip(K_Math::Box2D(320, 0, 32, 48), 2, 6, false);	//Landing
	object.GetImage().CreateCharaChip(K_Math::Box2D(320, 48, 32, 48), 4, 4, false);	//SkillUse
	object.GetImage().CreateCharaChip(K_Math::Box2D(320, 48, 32, 48), 4, 4, false);	//SkillMoveUse //キャラチップの変更有
	object.GetImage().CreateCharaChip(K_Math::Box2D(320, 48, 32, 48), 4, 4, false);	//SkillAirUse //キャラチップの変更有
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 96, 32, 48), 4, 4, false);	//CameraGunUse //キャラチップの変更有
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 96, 32, 48), 4, 4, false);	//CameraGunMoveUse //キャラチップの変更有
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 96, 32, 48), 4, 4, false);	//CameraGunAirUse //キャラチップの変更有
	object.GetImage().CreateCharaChip(K_Math::Box2D(416, 0, 32, 48), 3, 4, false);	//ReciveDamage	//キャラチップの変更有

	//Moveの重力の設定
	object.GetMove().SetAddVec(4.f);
	object.GetMove().SetJumpPow(9.f);

	//カメラガンの初期化
	cameraGun.Initailize();

	//こりじょんの設定-------------------------------
	//ボックスの形の生成
	shape = CC::CreateBoxShape(14, 22, 1);
	shape2 = CC::CreateBoxShape(13, 1, 1);
	
	//生成した[形]でコリジョンや剛体を作成
	cManager.CreateBaseCollisionData(shape, object.GetPos(), object.GetAngle(), true);	//ベース
	cManager.CreateSubCollisionData(shape, CollisionMask::EnemyCollision | CollisionMask::TakeDamagePlayer, CollisionMask::PlayerCollision, object.GetPos()); //被ダメ
	cManager.CreateSubCollisionData(shape2, CollisionMask::Ground, CollisionMask::Non, K_Math::Vector3(0, -22, 0)); //足元
	cManager.CreateSubCollisionData(shape2, CollisionMask::Ground, CollisionMask::Non, K_Math::Vector3(0, 22, 0)); //頭上

	//コリジョンに情報を持たせる
	cManager.SetSubCollisionUserData(0, &object.GetStatus());
}

//更新
void	Player::UpDate()
{
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
	RegistSkill();
	//skillManager.UpDate();
	skillManager.UpDate(object);

	//当たり判定動作-------------------
	cManager.MoveBaseCollision(object.GetMoveVec(), object.GetDirection(), false);

	//位置同期処理---------------------
	object.SetPos(cManager.GetBaseCollisionObjectPosition());
	cManager.SetBaseCollisionObjectPosition(object.GetPos());

	//アニメーション-------------------
	object.GetImage().Animation();

	if (invicibleCnt > 0)
	{
		invicibleCnt--;
	}
}

//-----------------------------------------------------------------
//描画
//-----------------------------------------------------------------
void	Player::Render()
{
	//カメラがんの描画
	cameraGun.Render();
	//スキルの描画----------------------------
	skillManager.Render();

	if (Flashing())
	{
		object.GetImage().ImageDraw3D(object.GetPos(), object.GetAngle(), object.GetScale(), object.GetDirection());
	}
}

//ダメージを与える
int		Player::GiveDamage()
{
	return object.GetAttackPoint();
}

//ダメージの受ける処理
void	Player::ReciveDamage()
{
	std::vector<K_Physics::CollisionTag*> data = cManager.GetConflictionObjectsTag(CollisionKind::Base);

	if (data.size() > 0)
	{
		int index = data[0]->tagIndex;
		enemyData = (Status*)data[0]->userData;
		object.GetStatus().GetLife() -= enemyData->GetAttackPoint();
		KnockBack(enemyData->GetPos());
	}
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
		if (object.GetMoveVec().x != 0)
		{
			cameraGun.SetMoveSpeed(7.0f);
		}
		cameraGun.SetDirection(object.GetDirection());	//方向を同期させる
		cameraGun.SetCameraGun(true);
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
			skillManager.ChangeRegistFlag(true);	//登録モードへ
			//カメラガンからスキルデータを受け取る
			skillManager.ReceiveSkillAndCharaChip(cameraGun.GetSkillAndCharaChip());
		}
		//カメラマーカーをプレイヤーの位置に戻す
		cameraGun.SetCameraGun(false);
	}
}


//ジャンプ処理
void	Player::JumpMove()
{
	if (INPUT::IsPressButton(VpadIndex::Pad0,K_Input::VpadButton::R1))
	{
		object.GetMove().JumpOperation();
	}
	if (INPUT::IsReaveButton(VpadIndex::Pad0, K_Input::VpadButton::R1) && (object.GetMove().GetFallSpeed() > 1.5f))
	{
		object.GetMove().SetFallSpeed(1.5f);
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
		ChangeDamageMotion(nowMotion);
		if (controller.IsLStickInput()) { nowMotion = Walk; }
		if (cManager.CheckHitSubCollisionObejct(Foot))
		{
			if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::R1)) { nowMotion = TakeOff; }
		}
		ChangeSkillMotion(nowMotion,SkillUse);
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = CameraGunUse; }
		if (!cManager.CheckHitSubCollisionObejct(Foot)) { nowMotion = Fall; }
		break;
	case Walk:	//歩く
		ChangeDamageMotion(nowMotion);		//1フレーム
		if (motionCnt >= maxFrame / 3)
		{
			nowMotion = Run;
		}
		if (!cManager.CheckHitSubCollisionObejct(Foot)) { nowMotion = Fall; }
		if (!controller.IsLStickInput()) { nowMotion = Idle; }
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::R1)) { nowMotion = TakeOff; }
		ChangeSkillMotion(nowMotion, SkillMoveUse);
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = CameraGunMoveUse; }
		break;
	case Run:	//走る
		ChangeDamageMotion(nowMotion);		
		if (!cManager.CheckHitSubCollisionObejct(Foot)) { nowMotion = Fall; }
		if (!controller.IsLStickInput()) { nowMotion = Idle; }
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::R1)) { nowMotion = TakeOff; }
		ChangeSkillMotion(nowMotion, SkillMoveUse);
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = CameraGunMoveUse; }
		break;
	case Jump:	//上昇中
		ChangeDamageMotion(nowMotion);		
		if (object.GetMove().GetFallSpeed() <= 0.0f) { nowMotion = Fall; }
		if (cManager.CheckHitSubCollisionObejct(Head)) { nowMotion = Fall; }
		ChangeSkillMotion(nowMotion, SkillAirUse);
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = CameraGunAirUse; }
		if (cManager.CheckHitSubCollisionObejct(Foot)) { nowMotion = Fall; }
		break;
	case Fall:	//落下中
		ChangeDamageMotion(nowMotion);		
		if (cManager.CheckHitSubCollisionObejct(Foot)) { nowMotion = Landing; }
		ChangeSkillMotion(nowMotion, SkillAirUse);
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = CameraGunAirUse; }
		break;
	case TakeOff:	//飛ぶ瞬間
		ChangeDamageMotion(nowMotion);
		if (motionCnt >= maxFrame / maxFrame)
		{
			nowMotion = Jump;
		}
		break;
	case Landing:	//着地の瞬間
		ChangeDamageMotion(nowMotion);
		if (motionCnt >= maxFrame / maxFrame)
		{
			nowMotion = Idle;
		}
		break;
	case SkillUse:		//スキル使用中
	case SkillMoveUse:	//移動中にスキル使用
		ChangeDamageMotion(nowMotion);
		if (motionCnt > maxFrame / 6)
		{
			nowMotion = Idle;
		}
		break;
	case SkillAirUse:	//空中にスキル使用
		ChangeDamageMotion(nowMotion);
		if (motionCnt > maxFrame / 6)
		{
			nowMotion = Idle;
		}
		if (cManager.CheckHitSubCollisionObejct(Head)) { nowMotion = Fall; }
		break;
	case CameraGunUse:		//カメラガン構え
	case CameraGunMoveUse:	//カメラガン移動中構え
		ChangeDamageMotion(nowMotion);
		if (motionCnt > maxFrame / 6)
		{
			nowMotion = Idle;
		}
		break;
	case CameraGunAirUse:	//カメラガン空中構え
		ChangeDamageMotion(nowMotion);
		if (motionCnt > maxFrame / 6)
		{
			nowMotion = Idle;
		}
		if (cManager.CheckHitSubCollisionObejct(Head)) { nowMotion = Fall; }
		break;
	case DamageRecive:		//ダメージ受ける
		if (motionCnt > maxFrame / 6 && cManager.CheckHitSubCollisionObejct(Foot))
		{
			//本来はここでパラメータをいじらない
			object.SetMoveVec(K_Math::Vector3(0,0,0));
			object.GetMove().SetFallSpeed(0.0f);
			nowMotion = Idle;
		}
		break;
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
		object.SetMoveVec(K_Math::Vector3(0, 0, 0));
		
		//上昇中もしくは足元に地面がない
		if (object.GetMoveVec().y > 0.0f || !cManager.CheckHitSubCollisionObejct(Foot))
		{
			object.GetMove().GravityOperation(cManager.CheckHitSubCollisionObejct(Foot));
		}

		break;
		//重力を無効にするモーション(今はなし)
	case Non:
		break;
	}

	//移動コントローラー
	switch (motion) {
	default:
		controller.UpDate(object.GetMove());
		break;
		//コントローラーで移動を無効にする
	case Non:
	case DamageRecive:	//ダメージ受けてる際は反応しない
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
		if (INPUT::IsReaveButton(VpadIndex::Pad0, K_Input::VpadButton::R1) && (object.GetMove().GetFallSpeed() > minJumpForce))
		{
			object.GetMove().SetFallSpeed(minJumpForce);
		}
		break;
	case Fall:		//落下中
		if (motionCnt == 0)
		{
			object.GetMove().SetFallSpeed(0);
		}
		break;
	case TakeOff:	//飛ぶ瞬間
		break;
	case Landing:	//着地
		if (motionCnt == 0)
		{
			object.GetMove().SetFallSpeed(0);
		}
		break;
	case SkillUse:		//スキル使用中
	case SkillMoveUse:	//移動中のスキル使用
	case SkillAirUse:	//空中のスキル使用
		if (motionCnt == 0)
		{
			UseSkill();
		}
		break;
	case CameraGunUse:		//カメラガン構え
	case CameraGunMoveUse:	//カメラガン移動中構え
	case CameraGunAirUse:	//カメラガン空中構え
		break;
	case DamageRecive:		//ダメージ処理
		//点滅するフラグをOnにする
		if (motionCnt == 0)
		{
			object.GetMove().SetFallSpeed(0.0f);
			ReciveDamage();
			invicibleCnt = maxInvicibleTime;
		}
		object.GetMove().Horizontal();
		object.GetMove().Vertical();
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



//------------------------------------
//プレイヤー側が登録か使用かを判断

//!@brief スキルの登録処理
void	Player::RegistSkill()
{
	//0番 = Y
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::Y))
	{
		skillManager.RegistSkillData(0);
	}
	//1番 = X
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::X))
	{
		skillManager.RegistSkillData(1);
	}
	//2番 = B
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::B))
	{
		skillManager.RegistSkillData(2);
	}
	//3番 = A
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::A))
	{
		skillManager.RegistSkillData(3);
	}
}

//!@brief スキルの使用処理
void		Player::UseSkill()
{
	//0番 = Y
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::Y))
	{
		skillManager.UseSkillData(0, object);
	}
	//1番 = X
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::X))
	{
		skillManager.UseSkillData(1, object);
	}
	//2番 = B
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::B))
	{
		skillManager.UseSkillData(2, object);
	}
	//3番 = A
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::A))
	{
		skillManager.UseSkillData(3, object);
	}
}


//!@brief スキルの状態変異
void	Player::SkillState(Motion& nowMotion,const Motion& nextMotion,const int& btnNum)
{
	if (!skillManager.CheckRegistFlag())
	{
		if (skillManager.CheckExistSkill(btnNum))
		{
			nowMotion = nextMotion;
		}
	}
}

//!@brief スキルの状態へ
void	Player::ChangeSkillMotion(Motion& nowMotion,const Motion& nextMotion)
{
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::A))
	{
		SkillState(nowMotion, nextMotion, 3);
	}
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::B))
	{
		SkillState(nowMotion, nextMotion, 2);
	}
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::X))
	{
		SkillState(nowMotion, nextMotion, 1);
	}
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::Y))
	{
		SkillState(nowMotion, nextMotion, 0);
	}
}


//!@brief ダメージモーションへチェンジ
void	Player::ChangeDamageMotion(Motion& motion)
{
	if (invicibleCnt <= 0)
	{
		if (cManager.CheckHitSubCollisionObejct(CollisionKind::Base)) { motion = DamageRecive; }
	}
}


//!@brief ノックバック処理
//!@param[in] 相手の座標
void	Player::KnockBack(const K_Math::Vector3& pos_)
{
	object.GetMove().SetVertical(6.0f);
	if (object.GetPos().x > pos_.x)
	{
		object.GetMove().SetHorizontal(-3.0f);
	}
	else
	{
		object.GetMove().SetHorizontal(+3.0f);
	}
}


//!@brief	点滅処理
bool	Player::Flashing()
{
	if (invicibleCnt > 0)
	{
		if ((invicibleCnt / 4) % 2 == 0)
		{
			return false;
		}
	}
	return true;
}