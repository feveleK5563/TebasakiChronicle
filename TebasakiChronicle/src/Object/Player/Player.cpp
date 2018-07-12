#include "Player.h"
#include "../src/Effect/Effect.h"
#include "../src/Helper.h"


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
	shutterSource.LoadSound("Shutter", "data/sounds/camera/shutter.ogg", ALLREAD);
	jumpSource.LoadSound("Jump", "data/sounds/player/jump.ogg", ALLREAD);
	damageSource.LoadSound("Damage", "data/sounds/player/damage.ogg", ALLREAD);
	RunSource.LoadSound("Run", "data/sounds/player/walk.ogg", ALLREAD);
	landingSource.LoadSound("landing", "data/sounds/player/landing.ogg", ALLREAD);
	cameraGunShotSource.LoadSound("cameraShot", "data/sounds/player/gunShot.ogg", ALLREAD);
	
	soundEngine.AddSource(shutterSource);
	soundEngine.AddSource(jumpSource);
	soundEngine.AddSource(damageSource);
	soundEngine.AddSource(RunSource);
	soundEngine.AddSource(landingSource);
	soundEngine.AddSource(cameraGunShotSource);

	asset = new Asset(new AssetSound("data/SoundLoadData/playerSound.txt"));
	asset->LoadEffect("data/EffectLoadData/playerEffect.txt");
}

//-----------------------------------------------
//デストラクタ
//-----------------------------------------------
Player::~Player()
{
	CC::RemoveCollisionShape(&shape);
	CC::RemoveCollisionShape(&shape2);

	Memory::SafeDelete(texture);

	soundEngine.DeleteSound("Shutter");
	soundEngine.DeleteSound("Jump");
	soundEngine.DeleteSound("Damage");
	soundEngine.DeleteSound("Run");
	soundEngine.DeleteSound("landing");
	soundEngine.DeleteSound("cameraShot");

	Memory::SafeDelete(asset);
}

//-------------------------------------------------------------------
//初期化
void	Player::Initliaze()
{
	//オブジェクトの初期化
	object.GetStatus().SetStatusData(
		Status::State::Active,
		K_Math::Vector3(100, 50, 0),
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
	maxInvicibleTime = 120;		//無敵時間
	object.GetStatus().SetMinLife(0);
	object.GetStatus().SetMaxLife(10);
	preTargetDir = object.GetDirection();
	targetDir = object.GetDirection();


	texture = new K_Graphics::Texture();
	texture->Initialize();
	texture->LoadImage("./data/image/Player/player.png");
	//画像の生成
	object.SetImage(texture, true);
	//AnimStateの状態の順番でなければアニメーションが対応しない
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 0, 64, 64), 6, 8, true);				//Idle
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 64, 64, 64), 3, 1, false);			//Walk(出だし)
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 64 * 2, 64, 64), 11, 4, true);		//Run
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 64 * 3, 64, 64), 5, 4, false);		//Jump
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 64 * 4, 64, 64), 5, 4, false);		//fall
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 64 * 3, 64, 64), 1, 1, false);		//TakeOff
	object.GetImage().CreateCharaChip(K_Math::Box2D(64 * 5, 64 * 5, 64, 64), 1, 3, false);	//landing
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 64 * 5, 64, 64), 10, 4, true);		//GunRun
	object.GetImage().CreateCharaChip(K_Math::Box2D(64, 64 * 6, 64, 64), 5, 4, false);		//GunJump
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 64 * 7, 64, 64), 5, 4, false);		//GunFall
	object.GetImage().CreateCharaChip(K_Math::Box2D(64 * 3, 64, 64, 64), 1, 5, false);		//GunIdle
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 64 * 8, 64, 64), 5, 4, false);		//Damage
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 64 * 9, 64, 64), 10, 4, true);		//GunRunBack

	//Moveの重力の設定
	object.GetMove().SetAddVec(4.f);
	object.GetMove().SetJumpPow(9.f);

	//カメラガンの初期化
	cameraGun.Initailize();

	//こりじょんの設定-------------------------------
	//ボックスの形の生成
	shape = CC::CreateBoxShape(12, 30, 1);
	shape2 = CC::CreateBoxShape(11, 1, 1);
	
	//生成した[形]でコリジョンや剛体を作成
	cManager.CreateBaseCollisionData(shape, object.GetPos(), object.GetAngle(), true);	//ベース
	cManager.CreateSubCollisionData(shape, CollisionMask::EnemyCollision | CollisionMask::TakeDamagePlayer, CollisionMask::PlayerCollision, K_Math::Vector3(0,0,0)); //被ダメ
	cManager.CreateSubCollisionData(shape2, CollisionMask::Ground, CollisionMask::Non, K_Math::Vector3(0, -30, 0)); //足元
	cManager.CreateSubCollisionData(shape2, CollisionMask::Ground, CollisionMask::Non, K_Math::Vector3(0, 30, 0)); //頭上

	//コリジョンに情報を持たせる
	cManager.SetSubCollisionUserData(0, &object.GetStatus());
}

//---------------------------------------------------------------
//更新
void	Player::UpDate()
{
	motionCnt++;

	//--------------------------------------------------------
	//思考&モーションの移動
	Think();
	Move();

	//カメラガン-----------------------
	if (object.GetState() != Status::State::Death)
	{
		ShotCameraGun();				//かめらがんを撃つ
		ReverseCameraGun();				//カメラがんを戻す
	}
	cameraGun.UpDate(object.GetPos());

	//スキルの使用---------------------
	if (skillManager.CheckRegistFlag())
	{
		RegistSkill();
	}
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
		invicibleCnt -= 1;
	}

	//ライフが0以下になる
	if (object.GetLife() <= 0)
	{
		object.SetState(Status::State::Death);
	}

	//ここはお試しで行っています
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::A))
	{
		asset->GetSound("GOGOGO2").PlaySE();
		asset->GetEffect(static_cast<int>(EffectName::Effect2)).CreateEffect(EffectName::Effect2, object.GetPos());
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

//!@brief	オブジェクトの取得
GameObject&	Player::GetGameObject()
{
	return object;
}

//入力に応じて向きを変える
void	Player::ChangeDir()
{
	//左スティックの倒れている深さ
	float stickDepth = INPUT::GetStickPower(VpadIndex::Pad0, K_Input::VpadStick::L);
	//右方向を0度とした回転度
	float stickAngle = INPUT::GetStickRotation(VpadIndex::Pad0, K_Input::VpadStick::L);

	if (stickDepth != 0 && K_Math::DegToRad(-90) != stickAngle && stickAngle != K_Math::DegToRad(90))
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

		//カメラガンを撃つ音
		cameraGunShotSource.PlaySE();
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
			if (*cameraGun.GetSkillAndCharaChip().behaviorId != 0)
			{
				skillManager.ChangeRegistFlag(true);	//登録モードへ
				//カメラガンからスキルデータを受け取る
				skillManager.ReceiveSkillAndCharaChip(cameraGun.GetSkillAndCharaChip());
				
				//仮のエフェクト*******
				//カメラがんのシャッター
				//Effect::CreateEffect(EffectName::Effect1, cameraGun.object.GetPos());
				//カメラがんからの発射光的なもの
				//プレイヤーの動きについてきてほしい
				//Effect::CreateEffect(EffectName::Effect1, K_Math::Vector3(cameraGun.GetDir() * 24 + object.GetPos().x, object.GetPos().y + 5, object.GetPos().z));

				//シャッター音
				shutterSource.PlaySE();
			}
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
		ChangeDamageMotion(nowMotion);
		if (motionCnt >= maxFrame / (maxFrame / 2))
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
		if (cManager.CheckHitSubCollisionObejct(Foot)) { nowMotion = Fall; }
		if (object.GetMove().GetFallSpeed() <= 0.0f) { nowMotion = Fall; }
		if (cManager.CheckHitSubCollisionObejct(Head)) { nowMotion = Fall; }
		ChangeSkillMotion(nowMotion, SkillAirUse);
		if (INPUT::IsStayButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = CameraGunAirUse; }
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
			if (INPUT::IsStayButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = CameraGunAirUse; }
			else { nowMotion = Jump; }
		}
		break;
	case Landing:	//着地の瞬間
		ChangeDamageMotion(nowMotion);
		if (motionCnt >= maxFrame / maxFrame)
		{
			if (INPUT::IsStayButton(VpadIndex::Pad0, VpadButton::L1)){ nowMotion = CameraGunUse; }
			else { nowMotion = Idle; }
		}
		break;
	case SkillUse:		//スキル使用中
	case SkillMoveUse:	//移動中にスキル使用
		ChangeDamageMotion(nowMotion);
		if (motionCnt > maxFrame / 6)
		{
			nowMotion = Idle;
		}
		if (controller.IsLStickInput()) { nowMotion = Run; }
		if (!cManager.CheckHitSubCollisionObejct(Foot)) { nowMotion = Fall; }
		if (cManager.CheckHitSubCollisionObejct(Head)) { nowMotion = Fall; }
		if (object.GetMove().GetFallSpeed() > 0.0f) { nowMotion = Jump; }
		break;
	case SkillAirUse:	//空中にスキル使用
		ChangeDamageMotion(nowMotion);
		if (cManager.CheckHitSubCollisionObejct(Head)) { nowMotion = Fall; }
		if (cManager.CheckHitSubCollisionObejct(Foot)) 
		{ 
			nowMotion = Landing;
		}
		else
		{
			if (motionCnt > maxFrame / 6)
			{
				nowMotion = Fall;
			}
		}
		if (object.GetMove().GetFallSpeed() > 0.0f) { nowMotion = Jump; }
		break;
	case CameraGunUse:		//カメラガン構え
		ChangeDamageMotion(nowMotion);
		if (INPUT::IsReaveButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = Idle; }
		if (controller.IsLStickInput()) { nowMotion = CameraGunMoveUse; }
		if (cManager.CheckHitSubCollisionObejct(Foot))
		{
			if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::R1)) { nowMotion = TakeOff; }
		}
		break;
	case CameraGunMoveUse:	//カメラガン移動中構え
		ChangeDamageMotion(nowMotion);
		//カメラガン使用ボタンが押されている間
		if (INPUT::IsStayButton(VpadIndex::Pad0, VpadButton::L1))
		{
			if (!controller.IsLStickInput()) { nowMotion = CameraGunUse; }
		}
		else
		{
			nowMotion = Run;
		}
		if (cManager.CheckHitSubCollisionObejct(Foot))
		{
			if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::R1)) { nowMotion = TakeOff; }
		}
		else
		{
			if (INPUT::IsStayButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = CameraGunAirUse; }
			else { nowMotion = Fall; }
		}
		break;
	case CameraGunAirUse:	//カメラガン空中構え
		ChangeDamageMotion(nowMotion);
		if (cManager.CheckHitSubCollisionObejct(Head)) { nowMotion = Fall; }
		if (cManager.CheckHitSubCollisionObejct(Foot)){	nowMotion = Landing; }
		if (INPUT::IsStayButton(VpadIndex::Pad0, VpadButton::L1))
		{
			if (cManager.CheckHitSubCollisionObejct(Foot))
			{
				nowMotion = CameraGunUse;
			}
		}
		else
		{
			if (cManager.CheckHitSubCollisionObejct(Foot))
			{
				nowMotion = Landing;
			}
			else
			{
				nowMotion = Fall;
			}
		}
		break;
	case DamageRecive:		//ダメージ受ける
		//30フレーム経過したかチェック
		if (motionCnt > maxFrame / 2)
		{
			if (cManager.CheckHitSubCollisionObejct(Foot))
			{
				//本来はここでパラメータをいじらない
				object.SetMoveVec(K_Math::Vector3(0, 0, 0));
				object.GetMove().SetFallSpeed(0.0f);
				nowMotion = Landing;
			}
			else
			{
				nowMotion = Fall;
			}
		}
		//地面と衝突したかチェック
		if (cManager.CheckHitSubCollisionObejct(Foot))
		{
			//本来はここでパラメータをいじらない
			object.SetMoveVec(K_Math::Vector3(0, 0, 0));
			object.GetMove().SetFallSpeed(0.0f);
			nowMotion = Landing;
		}
		break;
	}
	//死んでいるか判定
	if (object.IsDead())
	{
		nowMotion = Death;
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
		if (object.GetMoveVec().y <= -15.0f)
		{
			object.GetMoveVec().y = -15.0f;
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
	case Death:
		break;
	}

	switch (motion) {
	default:
		ChangeDir();			//入力に応じて向きを変える
		break;
	case Non:
	case DamageRecive:
	case Death:
	case TakeOff:
	case Landing:
	case CameraGunUse:
	case CameraGunMoveUse:
	case CameraGunAirUse:
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
		if (motionCnt == 0)
		{
			//RunSource.PlaySE();	//草むらを歩く音の例
		}
		break;
	case Jump:		//上昇中
		if (motionCnt == 0)
		{
			object.GetMove().JumpOperation();
			//仮のエフェクト発動
			//Effect::CreateEffect(EffectName::Effect1, object.GetPos()-K_Math::Vector3(0,24,0));
	
			jumpSource.PlaySE();		//ジャンプ音
		}
		//ジャンプ力の調節
		if (INPUT::IsReaveButton(VpadIndex::Pad0, K_Input::VpadButton::R1) && (object.GetMove().GetFallSpeed() > minJumpForce))
		{
			object.GetMove().SetFallSpeed(minJumpForce);
		}
		break;
	case Fall:		//落下中
		if (motionCnt == 0)
		{
			if (preMotion != Motion::DamageRecive)
			{
				object.GetMove().SetFallSpeed(0);
			}
		}
		//ダメージの横移動を残す
		if (preMotion == Motion::DamageRecive)
		{
			object.GetMove().Horizontal();
			object.GetMove().RegulationHorizon();
		}
		break;
	case TakeOff:	//飛ぶ瞬間
		break;
	case Landing:	//着地
		if (motionCnt == 0)
		{
			object.GetMove().SetFallSpeed(0);
			//着地音
			landingSource.PlaySE();
		}
		break;
	case SkillUse:		//スキル使用中
	case SkillMoveUse:	//移動中のスキル使用
		if (motionCnt == 0)
		{
			UseSkill();
		}
		break;
	case SkillAirUse:	//空中のスキル使用
		if (motionCnt == 0)
		{
			UseSkill();
		}
		if (preMotion == DamageRecive)
		{
			object.GetMove().Horizontal();
		}
		break;
	case CameraGunUse:		//カメラガン構え
	case CameraGunMoveUse:	//カメラガン移動中構え
		break;
	case CameraGunAirUse:	//カメラガン空中構え
		if (preMotion == DamageRecive)
		{
			object.GetMove().Horizontal();
		}
		if (motionCnt == 0)
		{
			if (cManager.CheckHitSubCollisionObejct(Foot))
			{
				object.GetMove().JumpOperation();
				//仮のエフェクト発動
				//Effect::CreateEffect(EffectName::Effect1, object.GetPos()-K_Math::Vector3(0,24,0));
			}
		}
		//ジャンプ力の調節
		if (INPUT::IsReaveButton(VpadIndex::Pad0, K_Input::VpadButton::R1) && (object.GetMove().GetFallSpeed() > minJumpForce))
		{
			object.GetMove().SetFallSpeed(minJumpForce);
		}
		break;
	case DamageRecive:		//ダメージ処理
		//点滅するフラグをOnにする
		if (motionCnt == 0)
		{
			object.GetMove().SetFallSpeed(0.0f);
			ReciveDamage();
			invicibleCnt = maxInvicibleTime;
			object.GetMove().Vertical();	//ジャンプ作用を与える

			damageSource.PlaySE(0.7f);		//ダメージ音
		}
		object.GetMove().Horizontal();
		break;
	case Death:
		break;
	}

	AnimState	nowAnimState = animState;
	//------------------------------------------------
	//モーション固有のアニメーション
	switch (motion) {
	case Idle:
		ChangeAnimState(AnimState::Idle);
		break;
	case Walk:
		ChangeAnimState(AnimState::Walk);
		break;
	case Run:
		if (motionCnt == 0)
		{
			motionCnt = preMotionCnt;
		}
		ChangeAnimState(AnimState::Run);
		break;
	case Jump:
		ChangeAnimState(AnimState::Jump);
		break;
	case Fall:
		ChangeAnimState(AnimState::Fall);
		break;
	case Landing:
		ChangeAnimState(AnimState::Landing);
		break;
	case CameraGunUse:
		ChangeAnimState(AnimState::GunIdle);
		break;
	case CameraGunMoveUse:
		if (motionCnt == 0)
		{
			motionCnt = preMotionCnt;
		}
		CameraGunMoveAnimation();
		break;
	case CameraGunAirUse:
		if (object.GetMove().GetFallSpeed() > 0)
		{
			ChangeAnimState(AnimState::GunJump);
		}
		else
		{
			ChangeAnimState(AnimState::GunFall);
		}
		//カメラガンが左右どちらにあるか判断
		preTargetDir = targetDir;
		targetDir = this->IsTargetDir(cameraGun.object.GetPos());
		if (preTargetDir != targetDir)
		{
			if (motionCnt >= maxFrame / 10)
			{
				object.SetDirection(targetDir);
				motionCnt = 0;
			}
		}
		if (targetDir != object.GetDirection())
		{
			object.SetDirection(targetDir);
		}
		break;
	case SkillUse:		
		ChangeAnimState(AnimState::Idle);
		break;
	case SkillMoveUse:	
		if (motionCnt == 0)
		{
			motionCnt = preMotionCnt;
		}
		ChangeAnimState(AnimState::GunRun);
		break;
	case SkillAirUse:
		if (object.GetMove().GetFallSpeed() > 0)
		{
			ChangeAnimState(AnimState::Jump);
		}
		else
		{
			ChangeAnimState(AnimState::Fall);
		}
		break;
	case DamageRecive:
		ChangeAnimState(AnimState::Damage);
		break;
	case Death:
		ChangeAnimState(AnimState::Idle);
		break;
	}
	UpDateAnimState(nowAnimState);

}


//------------------------------------------------
//モーションの更新
bool	Player::UpDateMotion(const Motion& nowMotion)
{
	if (motion == nowMotion) { return false; }
	//1つ前のモーションを保持し、次のモーションへ
	preMotion = motion;
	motion = nowMotion;
	//1つ前のモーション時間を保持
	preMotionCnt = motionCnt;
	motionCnt = 0;
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
		object.GetMove().SetHorizontal(+3.0f);
	}
	else
	{
		object.GetMove().SetHorizontal(-3.0f);
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


//!@brief	アニメーション状態の変更
//!@param[in]	animState	アニメーション状態
void	Player::ChangeAnimState(const AnimState& animState)
{
	this->animState = animState;
}

//!@brief	アニメーション状態の更新
//!@param[in]	animState	アニメーション状態
void	Player::UpDateAnimState(const AnimState& animState)
{
	if (this->animState != animState)
	{
		return;
	}
	this->preAnimState = this->animState;
	this->animState = animState;
	object.GetImage().ChangeAnimationPattern(static_cast<int>(animState), true);
}


//!@brief	アニメーション切り替え
//!@brief	2つのアニメーションを切り替える処理
//!@param[in]	animState1	アニメーション状態1
//!@param[in]	animState2	アニメーション状態2
//!@param[in]	frameCnt	切り替えるフレーム数
void	Player::SwitchAnimState(const AnimState& animState1, const AnimState& animState2, const float frameCnt)
{
	if (motionCnt == 0)
	{
		motionCnt = preMotionCnt;
	}
	if ((motionCnt / frameCnt) == 0)
	{
		ChangeAnimState(animState1);
	}
	if ((motionCnt / frameCnt) == 1)
	{
		ChangeAnimState(animState2);
	}
	if ((motionCnt / frameCnt) >= 2)
	{
		motionCnt = 0;
	}
}


////////////////////////////////////////////////////////////////////////////////////
//カメラガン関連
////////////////////////////////////////////////////////////////////////////////////

//!@brief	ターゲット位置が左右どちらにあるか判断
//!@param[in]	targetPos	ターゲット位置
//!@return	ターゲット位置が自分の位置より左なら Left
//!@return	ターゲット位置が自分の位置より右なら Right
const Status::Direction	Player::IsTargetDir(const K_Math::Vector3 targetPos)
{
	float offset = 0.0f;
	if (object.GetDirection() == Status::Direction::Left){	offset = -10.0f; }
	else{	offset = 10.0f; }

	if (object.GetPos().x < targetPos.x + offset)
	{
		return Status::Direction::Right;
	}
	else
	{
		return Status::Direction::Left;
	}
}

//!@brief	カメラガンのMoveアニメーション
//!@brief	プレイヤーがカメラガンを持って走っている際の向きアニメーションの切り替えなど
void	Player::CameraGunMoveAnimation()
{
	//カメラガンが左右どちらにあるか判断
	preTargetDir = targetDir;
	targetDir = this->IsTargetDir(cameraGun.object.GetPos());
	if (targetDir == Status::Direction::Left)
	{
		//右を押したら、反対向き
		if (controller.IsStickRight())
		{
			//std::cout << "向き反転" << std::endl;
			ChangeAnimState(AnimState::GunRunBack);
		}
		else
		{
			ChangeAnimState(AnimState::GunRun);
		}
	}
	else
	{
		//左を押したら、反対向き
		if (controller.IsStickLeft())
		{
			//std::cout << "向き反転" << std::endl;
			ChangeAnimState(AnimState::GunRunBack);
		}
		else
		{
			ChangeAnimState(AnimState::GunRun);
		}
	}
	if (preTargetDir != targetDir)
	{
		if (motionCnt >= maxFrame / 10)
		{
			object.SetDirection(targetDir);
			motionCnt = 0;
		}
	}
	if (targetDir != object.GetDirection())
	{
		object.SetDirection(targetDir);
	}
}