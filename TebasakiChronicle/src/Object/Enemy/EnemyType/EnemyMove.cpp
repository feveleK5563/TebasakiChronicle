#include "EnemyMove.h"

//-----------------------------------------------
//何もしない
void EMove_NoMotion::FirstMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager,Status& status, Move& move)
{
	//何もしない
}
void EMove_NoMotion::EMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}

//-----------------------------------------------
//向いている方向に移動する
void EMove_Movement::FirstMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}
void EMove_Movement::EMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	if (status.GetDirection() == status.Right)
	{
		move.GetMoveVec().x() += move.GetAddVec();
	}
	else
	{
		move.GetMoveVec().x() -= move.GetAddVec();
	}
}

//-----------------------------------------------
//地面についているときのみジャンプ
void EMove_Jump::FirstMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}
void EMove_Jump::EMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	if (cmanager.CheckHitSubCollisionObejct(3))
	{
		move.JumpOperation();
	}
}

//-----------------------------------------------
//前方に攻撃する
void EMove_FrontAttack::CreateAttackCollision()
{

}
void EMove_FrontAttack::FirstMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	K_Math::Vector3 relative(16, 0, 0);
	if (status.GetDirection() == Status::Direction::Left)
		relative.x() *= -1;

	tempmanager.CreateTemporaryCollision(
		CC::CreateBoxShape(14.f, 20.f, 10.f),
		CollisionMask::Non,
		CollisionMask::TakeDamageEnemy,
		status.GetPos() + relative,
		K_Math::Vector3(0, 0, 0),
		status.GetDirection(),
		status.GetAttackPoint(),
		60,
		false,
		false);
}
void EMove_FrontAttack::EMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//何もしない
}