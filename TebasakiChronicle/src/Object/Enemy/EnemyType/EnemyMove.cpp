#include "EnemyMove.h"

//-----------------------------------------------
//0�F�������Ȃ�
void EMove_NoMotion::FirstMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager,Status& status, Move& move)
{
	//�������Ȃ�
}
void EMove_NoMotion::EMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//�������Ȃ�
}

//-----------------------------------------------
//1�F�����Ă�������Ɉړ�����
void EMove_Movement::FirstMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//�������Ȃ�
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
//2�F�n�ʂɂ��Ă���Ƃ��̂݃W�����v
void EMove_Jump::FirstMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//�������Ȃ�
}
void EMove_Jump::EMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	if (cmanager.CheckHitSubCollisionObejct(3))
	{
		move.JumpOperation();
	}
}

//-----------------------------------------------
//3�F�O���ɍU������
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
		CollisionMask::TakeDamagePlayer,
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
	//�������Ȃ�
}