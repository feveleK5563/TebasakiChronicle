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
//�����ݒ肷��
void CharacterBehavior::SetBehavior(int moveNum)
{
	switch (moveNum)
	{
	case 0:		//�������Ȃ�
		behavior = new Behavior_NoMotion();
		break;

	case 1:		//�����Ă�������Ɉړ�����
		behavior = new Behavior_MovementToDirection();
		break;

	case 2:		//�n�ʂŃW�����v����
		behavior = new Behavior_JumpAtGround();
		break;

	case 3:		//�O���ɍU������
		behavior = new Behavior_FrontAttack();
		break;
	}
}
//-----------------------------------------------
//�ŏ��̏���
void CharacterBehavior::Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	timeCnt.ResetCntTime();
	behavior->Initialize(cmanager, tempmanager, status, move);
}
//-----------------------------------------------
//����̎��s
void CharacterBehavior::Action(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	timeCnt.Run();
	behavior->Action(cmanager, tempmanager, status, move, timeCnt);
}
//-----------------------------------------------
//�I������
void CharacterBehavior::Finalize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	behavior->Finalize(cmanager, tempmanager, status, move);
}


//-----------------------------------------------
//0�F�������Ȃ�
void Behavior_NoMotion::Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager,Status& status, Move& move)
{
	//�������Ȃ�
}
void Behavior_NoMotion::Action(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	//�������Ȃ�
}
void Behavior_NoMotion::Finalize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//�������Ȃ�
}

//-----------------------------------------------
//1�F�����Ă�������Ɉړ�����
void Behavior_MovementToDirection::Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//�������Ȃ�
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
	//�������Ȃ�
}

//-----------------------------------------------
//2�F�n�ʂŃW�����v
void Behavior_JumpAtGround::Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//�������Ȃ�
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
	//�������Ȃ�
}

//-----------------------------------------------
//3�F�O���ɍU������
void Behavior_FrontAttack::CreateAttackCollision()
{
	//�������Ȃ�
}
void Behavior_FrontAttack::Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	K_Math::Vector3 relative(16, 0, 0);
	if (status.GetDirection() == Status::Direction::Left)
		relative.x *= -1;

	//�U���p�R���W�������쐬
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
	//�������Ȃ�
}
void Behavior_FrontAttack::Finalize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//�������Ȃ�
}