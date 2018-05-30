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

	case 7:		//重力を一時的に倍にする
		behavior = new Behavior_ToDoubleGravity();
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
	}
}
//-----------------------------------------------
//最初の処理
void CharacterBehavior::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	behavior->Initialize(tempmanager, status, move);
}
//-----------------------------------------------
//動作の実行
void CharacterBehavior::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	behavior->Action(tempmanager, status, move, timeCnt);
}
//-----------------------------------------------
//終了処理
void CharacterBehavior::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	behavior->Finalize(tempmanager, status, move);
}


/* 動作追加のためのテンプレ

//-----------------------------------------------
//
void Behavior_::Initialize(TemporaryCollisionManager& tempmanager,Status& status, Move& move)
{
//何もしない
}
void Behavior_::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
//何もしない
}
void Behavior_::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
//何もしない
}

*/

//-----------------------------------------------
//何もしない
void Behavior_NoMotion::Initialize(TemporaryCollisionManager& tempmanager,Status& status, Move& move)
{
	//何もしない
}
void Behavior_NoMotion::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	//何もしない
}
void Behavior_NoMotion::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}

//-----------------------------------------------
//向きを変更する
void Behavior_ChangeDirection::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	if (status.GetDirection() == Status::Direction::Right)
	{
		status.GetDirection() = Status::Direction::Left;
	}
	else
	{
		status.GetDirection() = Status::Direction::Right;
	}
}
void Behavior_ChangeDirection::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	//何もしない
}
void Behavior_ChangeDirection::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}

//-----------------------------------------------
//向いている方向に移動する
void Behavior_MovementToDirection::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}
void Behavior_MovementToDirection::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	if (status.GetDirection() == status.Right)
	{
		move.GetMoveVec().x += move.GetAddVec();
	}
	else
	{
		move.GetMoveVec().x -= move.GetAddVec();
	}
}
void Behavior_MovementToDirection::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}

//-----------------------------------------------
//無条件に一回だけジャンプする
void Behavior_OnceJump::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	move.JumpOperation();
}
void Behavior_OnceJump::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	//何もしない
}
void Behavior_OnceJump::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}

//-----------------------------------------------
//前方に攻撃する
void Behavior_FrontAttack::CreateAttackCollision()
{
	//何もしない
}
void Behavior_FrontAttack::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	K_Math::Vector3 relative(30, 0, 0);
	if (status.GetDirection() == Status::Direction::Left)
		relative.x *= -1;

	//攻撃用コリジョンを作成
	tempmanager.CreateTemporaryCollision(
		CC::CreateBoxShape(17.f, 20.f, 10.f),
		CollisionMask::Non,
		CollisionMask::TakeDamagePlayer,
		status.GetPos() + relative,
		K_Math::Vector3(0, 0, 0),
		status.GetDirection(),
		status.GetAttackPoint(),
		10,
		0,
		false,
		false);
}
void Behavior_FrontAttack::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	//何もしない
}
void Behavior_FrontAttack::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}

//-----------------------------------------------
//重力の有無を切り替える
void Behavior_SwitchingGravity::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	if (move.GetGravity() < 0)
	{
		move.SetGravity(0);
	}
	else
	{
		move.SetDefaultGravity();
	}
	move.SetFallSpeed(0);
}
void Behavior_SwitchingGravity::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	//何もしない
}
void Behavior_SwitchingGravity::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}

//-----------------------------------------------
//重力を無効にして浮く
void Behavior_DisableGravityAndFloat::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	move.SetGravity(0);
}
void Behavior_DisableGravityAndFloat::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	move.GetMoveVec().y += move.GetAddVec();
}
void Behavior_DisableGravityAndFloat::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}

//-----------------------------------------------
//急速に落下する
void Behavior_ToDoubleGravity::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	move.SetDefaultGravity();
	move.SetGravity(move.GetGravity() * 2.f);
}
void Behavior_ToDoubleGravity::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	//何もしない
}
void Behavior_ToDoubleGravity::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	move.SetDefaultGravity();
}

//-----------------------------------------------
//重力を一時的に半分にする
void Behavior_ToHarfGravity::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	move.SetDefaultGravity();
	move.SetGravity(move.GetGravity() / 2.f);
}
void Behavior_ToHarfGravity::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	//何もしない
}
void Behavior_ToHarfGravity::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	move.SetDefaultGravity();
}

//-----------------------------------------------
//空中で上下に揺れる
void Behavior_AirIdle::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}
void Behavior_AirIdle::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	move.GetMoveVec().y += sin(K_Math::DegToRad((float)timeCnt.GetNowCntTime() * 4.f)) / move.GetAddVec();
}
void Behavior_AirIdle::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}

//-----------------------------------------------
//空中で揺れながら向いている方向に移動する
void Behavior_AirMovementToDirection::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}
void Behavior_AirMovementToDirection::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	move.GetMoveVec().y += sin(K_Math::DegToRad((float)timeCnt.GetNowCntTime() * 4.f)) / move.GetAddVec();
	if (status.GetDirection() == status.Right)
	{
		move.GetMoveVec().x += move.GetAddVec();
	}
	else
	{
		move.GetMoveVec().x -= move.GetAddVec();
	}
}
void Behavior_AirMovementToDirection::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}

//-----------------------------------------------
//Y座標の真ん中から前方に弾を発射する
void Behavior_ShotBulletFromMiddle::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	K_Math::Vector3 relative(16, 0, 0);
	K_Math::Vector3 moveVec(6, 0, 0);
	if (status.GetDirection() == Status::Direction::Left)
	{
		relative.x *= -1;
		moveVec.x *= -1;
	}

	//攻撃用コリジョンを作成
	tempmanager.CreateTemporaryCollision(
		CC::CreateBoxShape(10.f, 10.f, 10.f),
		CollisionMask::Non,
		CollisionMask::TakeDamagePlayer,
		status.GetPos() + relative,
		moveVec,
		status.GetDirection(),
		status.GetAttackPoint(),
		60,
		0,
		true,
		false);
}
void Behavior_ShotBulletFromMiddle::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	//何もしない
}
void Behavior_ShotBulletFromMiddle::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}

//-----------------------------------------------
//重力アリの爆弾を投げる
void Behavior_ThrowBomb::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	K_Math::Vector3 relative(16, 16, 0);
	K_Math::Vector3 moveVec(10, 10, 0);
	if (status.GetDirection() == Status::Direction::Left)
	{
		relative.x *= -1;
		moveVec.x *= -1;
	}

	//攻撃用コリジョンを作成
	tempmanager.CreateTemporaryCollision(
		CC::CreateBoxShape(10.f, 10.f, 10.f),
		CollisionMask::Non,
		CollisionMask::TakeDamagePlayer,
		status.GetPos() + relative,
		moveVec,
		status.GetDirection(),
		status.GetAttackPoint(),
		180,
		-0.5f,
		true,
		false);
}
void Behavior_ThrowBomb::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	//何もしない
}
void Behavior_ThrowBomb::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}