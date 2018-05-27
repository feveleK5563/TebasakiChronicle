#include "CharacterBehavior.h"

CharacterBehaviorAbstract::~CharacterBehaviorAbstract(){}

CharacterBehavior::CharacterBehavior(int moveNum)
{
	SetBehavior(moveNum);
}
CharacterBehavior::~CharacterBehavior()
{
	delete behavior;
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
	}
}
//-----------------------------------------------
//最初の処理
void CharacterBehavior::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	timeCnt.ResetCntTime();
	behavior->Initialize(tempmanager, status, move);
}
//-----------------------------------------------
//動作の実行
void CharacterBehavior::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	timeCnt.Run();
	behavior->Action(tempmanager, status, move, timeCnt);
}
//-----------------------------------------------
//終了処理
void CharacterBehavior::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	behavior->Finalize(tempmanager, status, move);
}


/* テンプレ

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

//---------------------------------------------- -
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
//一回だけジャンプする
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
	K_Math::Vector3 relative(16, 0, 0);
	if (status.GetDirection() == Status::Direction::Left)
		relative.x *= -1;

	//攻撃用コリジョンを作成
	tempmanager.CreateTemporaryCollision(
		CC::CreateBoxShape(14.f, 20.f, 10.f),
		CollisionMask::Non,
		CollisionMask::TakeDamagePlayer,
		status.GetPos() + relative,
		K_Math::Vector3(0, 0, 0),
		status.GetDirection(),
		status.GetAttackPoint(),
		60,
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