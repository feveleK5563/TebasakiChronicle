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

	case 1:		//������ύX����
		behavior = new Behavior_ChangeDirection();
		break;

	case 2:		//�����Ă�������Ɉړ�����
		behavior = new Behavior_MovementToDirection();
		break;

	case 3:		//��񂾂��W�����v����
		behavior = new Behavior_OnceJump();
		break;

	case 4:		//�O���ɍU������
		behavior = new Behavior_FrontAttack();
		break;
	}
}
//-----------------------------------------------
//�ŏ��̏���
void CharacterBehavior::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	timeCnt.ResetCntTime();
	behavior->Initialize(tempmanager, status, move);
}
//-----------------------------------------------
//����̎��s
void CharacterBehavior::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	timeCnt.Run();
	behavior->Action(tempmanager, status, move, timeCnt);
}
//-----------------------------------------------
//�I������
void CharacterBehavior::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	behavior->Finalize(tempmanager, status, move);
}


/* �e���v��

//-----------------------------------------------
//
void Behavior_::Initialize(TemporaryCollisionManager& tempmanager,Status& status, Move& move)
{
//�������Ȃ�
}
void Behavior_::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
//�������Ȃ�
}
void Behavior_::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
//�������Ȃ�
}

*/

//-----------------------------------------------
//�������Ȃ�
void Behavior_NoMotion::Initialize(TemporaryCollisionManager& tempmanager,Status& status, Move& move)
{
	//�������Ȃ�
}
void Behavior_NoMotion::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	//�������Ȃ�
}
void Behavior_NoMotion::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//�������Ȃ�
}

//---------------------------------------------- -
//������ύX����
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
	//�������Ȃ�
}
void Behavior_ChangeDirection::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//�������Ȃ�
}

//-----------------------------------------------
//�����Ă�������Ɉړ�����
void Behavior_MovementToDirection::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//�������Ȃ�
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
	//�������Ȃ�
}

//-----------------------------------------------
//��񂾂��W�����v����
void Behavior_OnceJump::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	move.JumpOperation();
}
void Behavior_OnceJump::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	//�������Ȃ�
}
void Behavior_OnceJump::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//�������Ȃ�
}

//-----------------------------------------------
//�O���ɍU������
void Behavior_FrontAttack::CreateAttackCollision()
{
	//�������Ȃ�
}
void Behavior_FrontAttack::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
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
void Behavior_FrontAttack::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	//�������Ȃ�
}
void Behavior_FrontAttack::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//�������Ȃ�
}