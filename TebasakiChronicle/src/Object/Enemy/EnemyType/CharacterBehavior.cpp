#include "CharacterBehavior.h"

CharacterBehaviorAbstract::~CharacterBehaviorAbstract(){}

CharacterBehavior::CharacterBehavior(int moveNum)
{
	SetBehavior(moveNum);
}
CharacterBehavior::~CharacterBehavior()
{
	Memory::SafeDelete(behavior);
}

//-----------------------------------------------------------------------------
//動作を設定する
void CharacterBehavior::SetBehavior(int moveNum)
{
	switch (moveNum)
	{
	case 0:		//何もしない
		behavior = new Behavior_NoMotion();
		break;

	case 1:		//向きを変更する
		behavior = new Behavior_ChangeDirection();
		break;

	case 2:		//向いている方向に移動する
		behavior = new Behavior_MovementToDirection();
		break;

	case 3:		//一回だけジャンプする
		behavior = new Behavior_OnceJump();
		break;

	case 4:		//前方に攻撃する
		behavior = new Behavior_FrontAttack();
		break;

	case 5:		//重力の有無を切り替える
		behavior = new Behavior_SwitchingGravity();
		break;

	case 6:		//重力を無効にして浮く
		behavior = new Behavior_DisableGravityAndFloat();
		break;

	case 7:		//一時的に重力を無効にし、一定速度で落下する
		behavior = new Behavior_Fall();
		break;

	case 8:		//重力を一時的に半分にする
		behavior = new Behavior_ToHarfGravity();
		break;

	case 9:		//空中で上下に揺れる
		behavior = new Behavior_AirIdle();
		break;

	case 10:	//空中で揺れながら向いている方向に移動する
		behavior = new Behavior_AirMovementToDirection();
		break;

	case 11:	//Y座標の真ん中から弾を発射する
		behavior = new Behavior_ShotBulletFromMiddle();
		break;

	case 12:	//重力アリの爆弾を投げる
		behavior = new Behavior_ThrowBomb();
		break;

	case 13:	//視界内のプレイヤーのX軸に合わせる
		behavior = new Behavior_MovePlayerPosX();
		break;

	case 14:	//視界内のプレイヤーのY軸に合わせる
		behavior = new Behavior_MovePlayerPosY();
		break;

	case 15:	//初期配置時の座標に移動する
		behavior = new Behavior_MoveInitPos();
		break;

	case 16:	//一時的に重力を無効にし急速落下、動作終了時にエフェクトを発生させる
		behavior = new Behavior_HighSpeedFall();
		break;

	case 17:	//コリジョンマスクを全て無効にする
		behavior = new Behavior_NonActiveCollisionMask();
		break;

	case 18:	//コリジョンマスクを全て有効にする
		behavior = new Behavior_ActiveCollisionMask();
		break;

	case 19:	//ビームを撃つ
		behavior = new Behavior_Beam();
		break;

	case 20:	//向いている方向に高速で移動する
		behavior = new Behavior_HighSpeedMove();
		break;
	}
}
//-----------------------------------------------
//最初の処理
void CharacterBehavior::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject, TimeCount& timeCnt)
{
	timeCnt.ResetCntTime();
	behavior->Initialize(tempmanager, gameObject);
}
//-----------------------------------------------
//動作の実行
void CharacterBehavior::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, TimeCount& timeCnt)
{
	timeCnt.Run();
	behavior->Action(tempmanager, gameObject, collmanager, timeCnt);
}
//-----------------------------------------------
//終了処理
void CharacterBehavior::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	behavior->Finalize(tempmanager, gameObject);
}


/* 動作追加のためのテンプレ

//-----------------------------------------------
//
void Behavior_::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
//何もしない
}
void Behavior_::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
//何もしない
}
void Behavior_::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
//何もしない
}

*/

//-----------------------------------------------
//何もしない
void Behavior_NoMotion::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}
void Behavior_NoMotion::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	//何もしない
}
void Behavior_NoMotion::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}

//---------------------------------------------- -
//向きを変更する
void Behavior_ChangeDirection::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	if (gameObject.GetStatus().GetDirection() == Status::Direction::Right)
	{
		gameObject.GetStatus().GetDirection() = Status::Direction::Left;
	}
	else
	{
		gameObject.GetStatus().GetDirection() = Status::Direction::Right;
	}
}
void Behavior_ChangeDirection::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	//何もしない
}
void Behavior_ChangeDirection::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}

//-----------------------------------------------
//向いている方向に移動する
void Behavior_MovementToDirection::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}
void Behavior_MovementToDirection::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	if (gameObject.GetStatus().GetDirection() == gameObject.GetStatus().Right)
	{
		gameObject.GetMove().GetMoveVec().x += gameObject.GetMove().GetAddVec();
	}
	else
	{
		gameObject.GetMove().GetMoveVec().x -= gameObject.GetMove().GetAddVec();
	}
}
void Behavior_MovementToDirection::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}

//-----------------------------------------------
//無条件に一回だけジャンプする
void Behavior_OnceJump::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	gameObject.GetMove().JumpOperation();
}
void Behavior_OnceJump::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	//何もしない
}
void Behavior_OnceJump::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}

//-----------------------------------------------
//前方に攻撃する
void Behavior_FrontAttack::CreateAttackCollision()
{
	//何もしない
}
void Behavior_FrontAttack::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	K_Math::Vector3 relative(40, 0, 0);
	if (gameObject.GetStatus().GetDirection() == Status::Direction::Left)
		relative.x *= -1;

	//攻撃用コリジョンを作成
	tempmanager.CreateTemporaryCollision(
		CC::CreateBoxShape(12.f, 20.f, 10.f),
		CollisionMask::Non,
		(CollisionMask)gameObject.GetStatus().GetCollisiomMask(),
		gameObject.GetStatus().GetPos() + relative,
		K_Math::Vector3(0, 0, 0),
		gameObject.GetStatus().GetDirection(),
		gameObject.GetStatus().GetAttackPoint(),
		30,
		0,
		false,
		false);
}
void Behavior_FrontAttack::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	//何もしない
}
void Behavior_FrontAttack::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}

//-----------------------------------------------
//重力の有無を切り替える
void Behavior_SwitchingGravity::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	if (gameObject.GetMove().GetGravity() > 0)
	{
		gameObject.GetMove().SetGravity(0);
	}
	else
	{
		gameObject.GetMove().SetDefaultGravity();
	}
}
void Behavior_SwitchingGravity::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	//何もしない
}
void Behavior_SwitchingGravity::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}

//-----------------------------------------------
//重力を無効にして浮く
void Behavior_DisableGravityAndFloat::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	gameObject.GetMove().SetGravity(0);
}
void Behavior_DisableGravityAndFloat::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	gameObject.GetMove().GetMoveVec().y += gameObject.GetMove().GetAddVec();
}
void Behavior_DisableGravityAndFloat::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}

//-----------------------------------------------
//一時的に重力を無効にし、一定速度で落下する
void Behavior_Fall::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	gameObject.GetMove().SetGravity(0);
}
void Behavior_Fall::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	gameObject.SetMoveVec(K_Math::Vector3(0, 5, 0));
}
void Behavior_Fall::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	gameObject.GetMove().SetDefaultGravity();
}

//-----------------------------------------------
//重力を一時的に半分にする
void Behavior_ToHarfGravity::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	gameObject.GetMove().SetGravity(gameObject.GetMove().GetGravity() / 2.f);
}
void Behavior_ToHarfGravity::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	//何もしない
}
void Behavior_ToHarfGravity::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	gameObject.GetMove().SetDefaultGravity();
}

//-----------------------------------------------
//空中で上下に揺れる
void Behavior_AirIdle::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}
void Behavior_AirIdle::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	gameObject.GetMove().GetMoveVec().y += sin(K_Math::DegToRad((float)timeCnt.GetNowCntTime() * 4.f)) / gameObject.GetMove().GetAddVec();
}
void Behavior_AirIdle::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}

//-----------------------------------------------
//空中で揺れながら向いている方向に移動する
void Behavior_AirMovementToDirection::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}
void Behavior_AirMovementToDirection::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	gameObject.GetMove().GetMoveVec().y += sin(K_Math::DegToRad((float)timeCnt.GetNowCntTime() * 4.f)) / gameObject.GetMove().GetAddVec();
	if (gameObject.GetStatus().GetDirection() == gameObject.GetStatus().Right)
	{
		gameObject.GetMove().GetMoveVec().x += gameObject.GetMove().GetAddVec();
	}
	else
	{
		gameObject.GetMove().GetMoveVec().x -= gameObject.GetMove().GetAddVec();
	}
}
void Behavior_AirMovementToDirection::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}

//-----------------------------------------------
//Y座標の真ん中から前方に弾を発射する
void Behavior_ShotBulletFromMiddle::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	K_Math::Vector3 relative(16, 0, 0);
	K_Math::Vector3 moveVec(10, 0, 0);
	if (gameObject.GetStatus().GetDirection() == Status::Direction::Left)
	{
		relative.x *= -1;
		moveVec.x *= -1;
	}

	//攻撃用コリジョンを作成
	tempmanager.CreateTemporaryCollision(
		CC::CreateBoxShape(10.f, 10.f, 10.f),
		CollisionMask::Non,
		(CollisionMask)gameObject.GetStatus().GetCollisiomMask(),
		gameObject.GetStatus().GetPos() + relative,
		moveVec,
		gameObject.GetStatus().GetDirection(),
		gameObject.GetStatus().GetAttackPoint(),
		60,
		0,
		true,
		true);

	tempmanager.SetAnimationCharaChip(
		CST::GetTexture("Effect"),
		K_Math::Box2D(0, 64, 48, 48),
		3,
		10.f,
		true);
}
void Behavior_ShotBulletFromMiddle::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	//何もしない
}
void Behavior_ShotBulletFromMiddle::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}

//-----------------------------------------------
//重力アリの爆弾を投げる
void Behavior_ThrowBomb::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	K_Math::Vector3 relative(16, 0, 0);
	K_Math::Vector3 moveVec(10, 10, 0);
	if (gameObject.GetStatus().GetDirection() == Status::Direction::Left)
	{
		relative.x *= -1;
		moveVec.x *= -1;
	}

	//攻撃用コリジョンを作成
	tempmanager.CreateTemporaryCollision(
		CC::CreateBoxShape(10.f, 10.f, 10.f),
		CollisionMask::Non,
		(CollisionMask)gameObject.GetStatus().GetCollisiomMask(),
		gameObject.GetStatus().GetPos() + relative,
		moveVec,
		gameObject.GetStatus().GetDirection(),
		gameObject.GetStatus().GetAttackPoint(),
		180,
		-0.5f,
		true,
		true);
}
void Behavior_ThrowBomb::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	//何もしない
}
void Behavior_ThrowBomb::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}

//-----------------------------------------------
//視界内のプレイヤーのX軸に合わせる
void Behavior_MovePlayerPosX::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{

}
void Behavior_MovePlayerPosX::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	auto player = collmanager->GetConflictionObjectsTag(EnemyCollisionName::Visibility);
	if (player.size() > 0)
	{
		Status* psta = static_cast<Status*>(player[0]->userData);
		K_Math::Vector3 dist((psta->GetPos().x - gameObject.GetPos().x) / 10.f, 0.f, 0.f);
		gameObject.GetMove().GetMoveVec() += dist;
	}
}
void Behavior_MovePlayerPosX::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{

}

//-----------------------------------------------
//視界内のプレイヤーのY軸に合わせる
void Behavior_MovePlayerPosY::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{

}
void Behavior_MovePlayerPosY::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	auto player = collmanager->GetConflictionObjectsTag(EnemyCollisionName::Visibility);
	if (player.size() > 0)
	{
		Status* psta = static_cast<Status*>(player[0]->userData);
		K_Math::Vector3 dist(0.f, (psta->GetPos().y - gameObject.GetPos().y) / 10.f, 0.f);
		gameObject.GetMove().GetMoveVec() += dist;
	}
}
void Behavior_MovePlayerPosY::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{

}

//-----------------------------------------------
//初期配置時の座標に移動する
void Behavior_MoveInitPos::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{

}
void Behavior_MoveInitPos::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	K_Math::Vector3 dist((gameObject.GetStatus().GetInitialPos().x - gameObject.GetPos().x) / 30.f, (gameObject.GetStatus().GetInitialPos().y - gameObject.GetPos().y) / 30.f, 0.f);
	gameObject.GetMove().GetMoveVec() += dist;
}
void Behavior_MoveInitPos::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{

}

//-----------------------------------------------
//重力を無効にし急速落下、動作終了時にエフェクトを発生させる
void Behavior_HighSpeedFall::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	gameObject.GetMove().SetGravity(0);
}
void Behavior_HighSpeedFall::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	gameObject.SetMoveVec(K_Math::Vector3(0, -20, 0));
}
void Behavior_HighSpeedFall::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	Effect::CreateEffect(EffectName::BossKnockEffect, gameObject.GetPos() + K_Math::Vector3(80, 0, 0), Status::Direction::Left);
	Effect::CreateEffect(EffectName::BossKnockEffect, gameObject.GetPos() + K_Math::Vector3(-80, 0, 0), Status::Direction::Right);
}

//-----------------------------------------------
//コリジョンマスクを全て無効にする
void Behavior_NonActiveCollisionMask::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}
void Behavior_NonActiveCollisionMask::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	collmanager->SetMaskActive(false);
}
void Behavior_NonActiveCollisionMask::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}

//-----------------------------------------------
//コリジョンマスクを全て有効にする
void Behavior_ActiveCollisionMask::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}
void Behavior_ActiveCollisionMask::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	collmanager->SetMaskActive(true);
}
void Behavior_ActiveCollisionMask::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}

//-----------------------------------------------
//ビームを撃つ
void Behavior_Beam::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	float size = 32.f * 15;
	float effectpos = 32.f;
	K_Math::Vector3 relative(0, 0, 0);
	if (gameObject.GetDirection() == Status::Direction::Left)
	{
		relative.x = size;
	}
	else
	{
		relative.x = -size;
		effectpos *= -1.f;
	}

	//コリジョンを作成
	tempmanager.CreateTemporaryCollision(
		CC::CreateBoxShape(size, 10.f, 10.f),
		CollisionMask::Non,
		(CollisionMask)gameObject.GetStatus().GetCollisiomMask(),
		gameObject.GetStatus().GetPos() + relative,
		K_Math::Vector3(0, 0, 0),
		gameObject.GetStatus().GetDirection(),
		gameObject.GetStatus().GetAttackPoint(),
		10,
		0.f,
		false,
		false);

	//エフェクトを作成
	Effect::CreateEffect(
		EffectName::BossBeamEffect1,
		gameObject.GetStatus().GetPos() + K_Math::Vector3(effectpos, 0, -1),
		gameObject.GetDirection());

	for (int i = 1; i < 15; ++i)
	{
		Effect::CreateEffect(
			EffectName::BossBeamEffect2,
			gameObject.GetStatus().GetPos() + K_Math::Vector3(i * (effectpos * 2), 0, -1),
			gameObject.GetDirection());
	}
}
void Behavior_Beam::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	//何もしない
}
void Behavior_Beam::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}

//-----------------------------------------------
//向いている方向に高速で移動する
void Behavior_HighSpeedMove::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}
void Behavior_HighSpeedMove::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	if (gameObject.GetStatus().GetDirection() == gameObject.GetStatus().Right)
	{
		gameObject.GetMove().GetMoveVec().x += gameObject.GetMove().GetAddVec() * 2.f;
	}
	else
	{
		gameObject.GetMove().GetMoveVec().x -= gameObject.GetMove().GetAddVec() * 2.f;
	}
}
void Behavior_HighSpeedMove::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//何もしない
}