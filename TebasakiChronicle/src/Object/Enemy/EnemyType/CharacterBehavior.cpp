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

	case 1:		//向いている方向に移動する
		behavior = new Behavior_MovementToDirection();
		break;

	case 2:		//地面でジャンプする
		behavior = new Behavior_JumpAtGround();
		break;

	case 3:		//前方に攻撃する
		behavior = new Behavior_FrontAttack();
		break;
	}
}
//-----------------------------------------------
//最初の処理
void CharacterBehavior::Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	timeCnt.ResetCntTime();
	behavior->Initialize(cmanager, tempmanager, status, move);
}
//-----------------------------------------------
//動作の実行
void CharacterBehavior::Action(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	timeCnt.Run();
	behavior->Action(cmanager, tempmanager, status, move, timeCnt);
}
//-----------------------------------------------
//終了処理
void CharacterBehavior::Finalize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	behavior->Finalize(cmanager, tempmanager, status, move);
}


//-----------------------------------------------
//0：何もしない
void Behavior_NoMotion::Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager,Status& status, Move& move)
{
	//何もしない
}
void Behavior_NoMotion::Action(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	//何もしない
}
void Behavior_NoMotion::Finalize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}

//-----------------------------------------------
//1：向いている方向に移動する
void Behavior_MovementToDirection::Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}
void Behavior_MovementToDirection::Action(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
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
void Behavior_MovementToDirection::Finalize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}

//-----------------------------------------------
//2：地面でジャンプ
void Behavior_JumpAtGround::Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}
void Behavior_JumpAtGround::Action(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	if (cmanager.CheckHitSubCollisionObejct(3))
	{
		move.JumpOperation();
	}
}
void Behavior_JumpAtGround::Finalize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}

//-----------------------------------------------
//3：前方に攻撃する
void Behavior_FrontAttack::CreateAttackCollision()
{
	//何もしない
}
void Behavior_FrontAttack::Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
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
void Behavior_FrontAttack::Action(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	//何もしない
}
void Behavior_FrontAttack::Finalize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}