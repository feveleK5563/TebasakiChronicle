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

	case 5:		//�d�̗͂L����؂�ւ���
		behavior = new Behavior_SwitchingGravity();
		break;

	case 6:		//�d�͂𖳌��ɂ��ĕ���
		behavior = new Behavior_DisableGravityAndFloat();
		break;

	case 7:		//�d�͂��ꎞ�I�ɔ{�ɂ���
		behavior = new Behavior_ToDoubleGravity();
		break;

	case 8:		//�d�͂��ꎞ�I�ɔ����ɂ���
		behavior = new Behavior_ToHarfGravity();
		break;

	case 9:		//�󒆂ŏ㉺�ɗh���
		behavior = new Behavior_AirIdle();
		break;

	case 10:	//�󒆂ŗh��Ȃ�������Ă�������Ɉړ�����
		behavior = new Behavior_AirMovementToDirection();
		break;

	case 11:	//Y���W�̐^�񒆂���e�𔭎˂���
		behavior = new Behavior_ShotBulletFromMiddle();
		break;

	case 12:	//�d�̓A���̔��e�𓊂���
		behavior = new Behavior_ThrowBomb();
		break;
	}
}
//-----------------------------------------------
//�ŏ��̏���
void CharacterBehavior::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	behavior->Initialize(tempmanager, status, move);
}
//-----------------------------------------------
//����̎��s
void CharacterBehavior::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	behavior->Action(tempmanager, status, move, timeCnt);
}
//-----------------------------------------------
//�I������
void CharacterBehavior::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	behavior->Finalize(tempmanager, status, move);
}


/* ����ǉ��̂��߂̃e���v��

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

//-----------------------------------------------
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
//�������Ɉ�񂾂��W�����v����
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
	K_Math::Vector3 relative(30, 0, 0);
	if (status.GetDirection() == Status::Direction::Left)
		relative.x *= -1;

	//�U���p�R���W�������쐬
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
	//�������Ȃ�
}
void Behavior_FrontAttack::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//�������Ȃ�
}

//-----------------------------------------------
//�d�̗͂L����؂�ւ���
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
	//�������Ȃ�
}
void Behavior_SwitchingGravity::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//�������Ȃ�
}

//-----------------------------------------------
//�d�͂𖳌��ɂ��ĕ���
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
	//�������Ȃ�
}

//-----------------------------------------------
//�}���ɗ�������
void Behavior_ToDoubleGravity::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	move.SetDefaultGravity();
	move.SetGravity(move.GetGravity() * 2.f);
}
void Behavior_ToDoubleGravity::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	//�������Ȃ�
}
void Behavior_ToDoubleGravity::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	move.SetDefaultGravity();
}

//-----------------------------------------------
//�d�͂��ꎞ�I�ɔ����ɂ���
void Behavior_ToHarfGravity::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	move.SetDefaultGravity();
	move.SetGravity(move.GetGravity() / 2.f);
}
void Behavior_ToHarfGravity::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	//�������Ȃ�
}
void Behavior_ToHarfGravity::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	move.SetDefaultGravity();
}

//-----------------------------------------------
//�󒆂ŏ㉺�ɗh���
void Behavior_AirIdle::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//�������Ȃ�
}
void Behavior_AirIdle::Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt)
{
	move.GetMoveVec().y += sin(K_Math::DegToRad((float)timeCnt.GetNowCntTime() * 4.f)) / move.GetAddVec();
}
void Behavior_AirIdle::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//�������Ȃ�
}

//-----------------------------------------------
//�󒆂ŗh��Ȃ�������Ă�������Ɉړ�����
void Behavior_AirMovementToDirection::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//�������Ȃ�
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
	//�������Ȃ�
}

//-----------------------------------------------
//Y���W�̐^�񒆂���O���ɒe�𔭎˂���
void Behavior_ShotBulletFromMiddle::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	K_Math::Vector3 relative(16, 0, 0);
	K_Math::Vector3 moveVec(6, 0, 0);
	if (status.GetDirection() == Status::Direction::Left)
	{
		relative.x *= -1;
		moveVec.x *= -1;
	}

	//�U���p�R���W�������쐬
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
	//�������Ȃ�
}
void Behavior_ShotBulletFromMiddle::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//�������Ȃ�
}

//-----------------------------------------------
//�d�̓A���̔��e�𓊂���
void Behavior_ThrowBomb::Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	K_Math::Vector3 relative(16, 16, 0);
	K_Math::Vector3 moveVec(10, 10, 0);
	if (status.GetDirection() == Status::Direction::Left)
	{
		relative.x *= -1;
		moveVec.x *= -1;
	}

	//�U���p�R���W�������쐬
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
	//�������Ȃ�
}
void Behavior_ThrowBomb::Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move)
{
	//�������Ȃ�
}