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

	case 7:		//�ꎞ�I�ɏd�͂𖳌��ɂ��A��葬�x�ŗ�������
		behavior = new Behavior_Fall();
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

	case 13:	//���E���̃v���C���[��X���ɍ��킹��
		behavior = new Behavior_MovePlayerPosX();
		break;

	case 14:	//���E���̃v���C���[��Y���ɍ��킹��
		behavior = new Behavior_MovePlayerPosY();
		break;

	case 15:	//�����z�u���̍��W�Ɉړ�����
		behavior = new Behavior_MoveInitPos();
		break;

	case 16:	//�ꎞ�I�ɏd�͂𖳌��ɂ��}�������A����I�����ɃG�t�F�N�g�𔭐�������
		behavior = new Behavior_HighSpeedFall();
		break;

	case 17:	//�R���W�����}�X�N��S�Ė����ɂ���
		behavior = new Behavior_NonActiveCollisionMask();
		break;

	case 18:	//�R���W�����}�X�N��S�ėL���ɂ���
		behavior = new Behavior_ActiveCollisionMask();
		break;

	case 19:	//�r�[��������
		behavior = new Behavior_Beam();
		break;

	case 20:	//�����Ă�������ɍ����ňړ�����
		behavior = new Behavior_HighSpeedMove();
		break;
	}
}
//-----------------------------------------------
//�ŏ��̏���
void CharacterBehavior::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject, TimeCount& timeCnt)
{
	timeCnt.ResetCntTime();
	behavior->Initialize(tempmanager, gameObject);
}
//-----------------------------------------------
//����̎��s
void CharacterBehavior::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, TimeCount& timeCnt)
{
	timeCnt.Run();
	behavior->Action(tempmanager, gameObject, collmanager, timeCnt);
}
//-----------------------------------------------
//�I������
void CharacterBehavior::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	behavior->Finalize(tempmanager, gameObject);
}


/* ����ǉ��̂��߂̃e���v��

//-----------------------------------------------
//
void Behavior_::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
//�������Ȃ�
}
void Behavior_::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
//�������Ȃ�
}
void Behavior_::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
//�������Ȃ�
}

*/

//-----------------------------------------------
//�������Ȃ�
void Behavior_NoMotion::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//�������Ȃ�
}
void Behavior_NoMotion::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	//�������Ȃ�
}
void Behavior_NoMotion::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//�������Ȃ�
}

//---------------------------------------------- -
//������ύX����
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
	//�������Ȃ�
}
void Behavior_ChangeDirection::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//�������Ȃ�
}

//-----------------------------------------------
//�����Ă�������Ɉړ�����
void Behavior_MovementToDirection::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//�������Ȃ�
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
	//�������Ȃ�
}

//-----------------------------------------------
//�������Ɉ�񂾂��W�����v����
void Behavior_OnceJump::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	gameObject.GetMove().JumpOperation();
}
void Behavior_OnceJump::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	//�������Ȃ�
}
void Behavior_OnceJump::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//�������Ȃ�
}

//-----------------------------------------------
//�O���ɍU������
void Behavior_FrontAttack::CreateAttackCollision()
{
	//�������Ȃ�
}
void Behavior_FrontAttack::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	K_Math::Vector3 relative(40, 0, 0);
	if (gameObject.GetStatus().GetDirection() == Status::Direction::Left)
		relative.x *= -1;

	//�U���p�R���W�������쐬
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
	//�������Ȃ�
}
void Behavior_FrontAttack::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//�������Ȃ�
}

//-----------------------------------------------
//�d�̗͂L����؂�ւ���
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
	//�������Ȃ�
}
void Behavior_SwitchingGravity::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//�������Ȃ�
}

//-----------------------------------------------
//�d�͂𖳌��ɂ��ĕ���
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
	//�������Ȃ�
}

//-----------------------------------------------
//�ꎞ�I�ɏd�͂𖳌��ɂ��A��葬�x�ŗ�������
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
//�d�͂��ꎞ�I�ɔ����ɂ���
void Behavior_ToHarfGravity::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	gameObject.GetMove().SetGravity(gameObject.GetMove().GetGravity() / 2.f);
}
void Behavior_ToHarfGravity::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	//�������Ȃ�
}
void Behavior_ToHarfGravity::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	gameObject.GetMove().SetDefaultGravity();
}

//-----------------------------------------------
//�󒆂ŏ㉺�ɗh���
void Behavior_AirIdle::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//�������Ȃ�
}
void Behavior_AirIdle::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	gameObject.GetMove().GetMoveVec().y += sin(K_Math::DegToRad((float)timeCnt.GetNowCntTime() * 4.f)) / gameObject.GetMove().GetAddVec();
}
void Behavior_AirIdle::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//�������Ȃ�
}

//-----------------------------------------------
//�󒆂ŗh��Ȃ�������Ă�������Ɉړ�����
void Behavior_AirMovementToDirection::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//�������Ȃ�
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
	//�������Ȃ�
}

//-----------------------------------------------
//Y���W�̐^�񒆂���O���ɒe�𔭎˂���
void Behavior_ShotBulletFromMiddle::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	K_Math::Vector3 relative(16, 0, 0);
	K_Math::Vector3 moveVec(10, 0, 0);
	if (gameObject.GetStatus().GetDirection() == Status::Direction::Left)
	{
		relative.x *= -1;
		moveVec.x *= -1;
	}

	//�U���p�R���W�������쐬
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
	//�������Ȃ�
}
void Behavior_ShotBulletFromMiddle::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//�������Ȃ�
}

//-----------------------------------------------
//�d�̓A���̔��e�𓊂���
void Behavior_ThrowBomb::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	K_Math::Vector3 relative(16, 0, 0);
	K_Math::Vector3 moveVec(10, 10, 0);
	if (gameObject.GetStatus().GetDirection() == Status::Direction::Left)
	{
		relative.x *= -1;
		moveVec.x *= -1;
	}

	//�U���p�R���W�������쐬
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
	//�������Ȃ�
}
void Behavior_ThrowBomb::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//�������Ȃ�
}

//-----------------------------------------------
//���E���̃v���C���[��X���ɍ��킹��
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
//���E���̃v���C���[��Y���ɍ��킹��
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
//�����z�u���̍��W�Ɉړ�����
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
//�d�͂𖳌��ɂ��}�������A����I�����ɃG�t�F�N�g�𔭐�������
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
//�R���W�����}�X�N��S�Ė����ɂ���
void Behavior_NonActiveCollisionMask::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//�������Ȃ�
}
void Behavior_NonActiveCollisionMask::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	collmanager->SetMaskActive(false);
}
void Behavior_NonActiveCollisionMask::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//�������Ȃ�
}

//-----------------------------------------------
//�R���W�����}�X�N��S�ėL���ɂ���
void Behavior_ActiveCollisionMask::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//�������Ȃ�
}
void Behavior_ActiveCollisionMask::Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt)
{
	collmanager->SetMaskActive(true);
}
void Behavior_ActiveCollisionMask::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//�������Ȃ�
}

//-----------------------------------------------
//�r�[��������
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

	//�R���W�������쐬
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

	//�G�t�F�N�g���쐬
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
	//�������Ȃ�
}
void Behavior_Beam::Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//�������Ȃ�
}

//-----------------------------------------------
//�����Ă�������ɍ����ňړ�����
void Behavior_HighSpeedMove::Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject)
{
	//�������Ȃ�
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
	//�������Ȃ�
}