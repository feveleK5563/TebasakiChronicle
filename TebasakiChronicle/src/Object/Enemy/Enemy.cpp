#include "Enemy.h"
#include "../../CSTList.h"
#include "../../Helper.h"

//�R���X�g���N�^
Enemy::Enemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction, const int indexNum, bool isBoss) :
	behaviorId(0),
	nowMoveOrder(0),
	nowPatternOrder(0),
	beforeMoveOrder(0),
	beforePatternOrder(0),
	isBoss(isBoss),
	relativePos(0.f, 0.f, 0.f)
{
	SetEnemyType(cpyet, setPos, direction, indexNum);
}

//�f�X�g���N�^
Enemy::~Enemy()
{
	Memory::SafeDelete(skillAndChip);
}

//-----------------------------------------------------------------------------
//�G����ݒ�
void Enemy::SetEnemyType(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction, const int indexNum)
{
	ems = cpyet->GetEnemyMoveSet();
	gameObject.GetStatus().SetStatusData(	Status::State::Non,
											setPos,
											K_Math::Vector3(0, 0, 0),
											K_Math::Vector3(1, 1, 1),
											direction,
											cpyet->GetHitDamage(),
											cpyet->GetMaxLife());
	gameObject.GetStatus().SetCollisionMask(CollisionMask::TakeDamagePlayer);

	if (cpyet->GetIsUseGravity() == false)
	{
		gameObject.GetMove().SetGravity(0.f);
	}

	gameObject.GetStatus().GetInitialPos() = setPos;
	gameObject.GetStatus().GetMaxLife() = cpyet->GetMaxLife();
	gameObject.GetStatus().GetMinLife() = 0;
	isUseGravity = cpyet->GetIsUseGravity();

	gameObject.GetMove().SetAddVec(cpyet->GetMoveSpeed());
	gameObject.GetMove().SetJumpPow(cpyet->GetJumpPower());

	//�A�j���[�V�����ƕ\���摜�̐ݒ�
	gameObject.SetImage(cpyet->GetTexture(), false);
	gameObject.GetImage().ChangeAnimationPattern(nowMoveOrder);
	gameObject.GetImage().ChangeCharaChip(ems->GetNowAnimChip(nowPatternOrder));

	//�R���W�����̐ݒ�
	collisionManager.SetBaseCollisionData(cpyet->CreateAndGetBaseCollisionData(), setPos);	//�x�[�X�R���W����
	collisionManager.SetSubCollisionData(cpyet->CreateAndGetRecieveDamageCollisionData());	//0 ��_���[�W�p�R���W����
	collisionManager.SetSubCollisionData(cpyet->CreateAndGetVisibilityCollisionData());		//1 ���E�p�R���W����
	collisionManager.SetSubCollisionData(cpyet->CreateAndGetAttackAreaCollisionData());		//2 �U������J�ڗp�R���W����
	collisionManager.SetSubCollisionData(cpyet->CreateAndGetCheckFootCollisionData());		//3 ��������p�R���W����
	collisionManager.SetSubCollisionData(cpyet->CreateAndGetCheckHeadCollisionData());		//4 ���㔻��p�R���W����
	collisionManager.SetSubCollisionData(cpyet->CreateAndGetRecieveCameraCollisionData());	//5 ��J�����K���p�R���W����

	//�^�O�̐ݒ�
	skillAndChip = new SkillAndCharaChip();
	skillAndChip->pos = &gameObject.GetStatus().GetPos();
	skillAndChip->textureName = &cpyet->GetTextureName();
	skillAndChip->behaviorId = &behaviorId;
	int i = 0;
	for (; i < 5; ++i)
	{
		collisionManager.SetSubCollisionTagIndex(i, indexNum);
		collisionManager.SetSubCollisionUserData(i, &gameObject.GetStatus());
	}
	collisionManager.SetSubCollisionTagIndex(i, indexNum);
	collisionManager.SetSubCollisionUserData(i, skillAndChip);
	SetTagData();

	SetNonEnemy();
	gameObject.SetState(Status::State::Non);

	timeCnt.SetEndTime(-1);
	invalidTime.SetEndTime(20);
	invalidTime.Count(false);
}

//-----------------------------------------------------------------------------
//������Ԃɂ���
void Enemy::SetNonEnemy()
{
	//�J�����}���󂯗p�R���W�������������T�u�R���W�����̃}�X�N�𖳌��ɂ���
	collisionManager.SetMaskActive(false);
	tempCollisionManager.DeleteCollision();
}

//-----------------------------------------------------------------------------
//��Ԃ�S�ď�����Ԃɖ߂�
void Enemy::ResetAndActiveEnemy()
{
	collisionManager.SetBaseCollisionObjectPosition(gameObject.GetStatus().GetInitialPos());
	gameObject.SetState(Status::State::Active);
	timeCnt.ResetCntTime();
	gameObject.GetStatus().GetLife() = gameObject.GetStatus().GetMaxLife();
	behaviorId = 0;
	nowMoveOrder = 0;
	nowPatternOrder = 0;
	beforeMoveOrder = 0;
	beforePatternOrder = 0;
	//�J�����}���󂯗p�R���W�������������T�u�R���W�����̃}�X�N��L���ɂ���
	collisionManager.SetMaskActive(true);
	//�A�j���[�V�����̃��Z�b�g
	gameObject.GetImage().ChangeCharaChip(ems->GetNowAnimChip(nowPatternOrder));
	gameObject.GetImage().ChangeAnimationPattern(nowMoveOrder);
}

//-----------------------------------------------------------------------------
//�X�V
void Enemy::Update()
{
	if (isBoss == false)
	{
		if (DecisionInScreen())
			return;
	}
	else if (	gameObject.GetState() == Status::State::Death ||
				gameObject.GetState() == Status::State::Non)
	{
		return;
	}

	//�ړ��ʂ�������
	gameObject.GetMove().GetMoveVec() = K_Math::Vector3(0, 0, 0);

	//�d�͂����Z����
	gameObject.GetMove().GravityOperation(collisionManager.GetConflictionObjectsTag(3).size() > 0);

	//�ݒ肳��Ă��铮����s��
	*skillAndChip->behaviorId = ems->EMove(nowMoveOrder, nowPatternOrder, timeCnt, &collisionManager, tempCollisionManager, gameObject);

	//�A�j���[�V�����̍X�V
	AnimationUpdate();

	//�R���W�����𓮂���
	collisionManager.MoveBaseCollision(gameObject.GetMove().GetMoveVec(), gameObject.GetStatus().GetDirection(), true);
	gameObject.GetPos() = collisionManager.GetBaseCollisionObjectPosition();
	tempCollisionManager.Update();
	relativePos += gameObject.GetMove().GetMoveVec();
	//�^�O�����X�V
	SetTagData();

	return;
}

//-----------------------------------------------------------------------------
//���S���Ă���ۂ���Ԃ�
bool Enemy::IsDead()
{
	return gameObject.IsDead();
}

//-----------------------------------------------------------------------------
//��ʓ�����
bool Enemy::DecisionInScreen()
{
	//��ʊO�ɏo�Ă����疳��
	if (fabsf(CST::GetPerspectiveCamera()->GetPosition().x - gameObject.GetPos().x) > fabsf(Define::ScreenWidth / 2))
	{
		if (gameObject.GetState() != Status::State::Non)
		{
			gameObject.SetPos(gameObject.GetStatus().GetInitialPos());
			SetNonEnemy();
			gameObject.SetState(Status::State::Non);
		}
		return true;
	}

	//��ʓ��ɓ����Ă���A������ł��Ȃ��ꍇ�͗L���ɂ���
	if (gameObject.GetState() == Status::State::Non)
	{
		ResetAndActiveEnemy();
	}
	else if (gameObject.GetState() == Status::State::Death)
	{
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//�R���W�����Ƃ̐ڐG����
//�_���[�W���󂯂���true��Ԃ�
bool Enemy::RecieveCollisionOperation()
{
	if (gameObject.GetState() != Status::State::Active)
	{
		if (gameObject.GetState() == Status::State::Invalid)
		{
			invalidTime.Run();
			if (invalidTime.IsTimeEnd())
			{
				gameObject.SetState(Status::State::Active);
			}
		}
		return false;
	}

	std::vector<K_Physics::CollisionTag*> tag;

	int damage = 0;	//��_���[�W

	//�_���[�W���󂯂�
	tag = collisionManager.GetConflictionObjectsTag(EnemyCollisionName::RecieveDamage);
	for (auto it : tag)
	{
		Status* hitThing = (Status*)it->userData;
		if (hitThing->GetState() == Status::State::Active)
		{
			damage += hitThing->GetAttackPoint();
			hitThing->GetState() = Status::State::Death;
		}
	}

	//�J�����K�����󂯂�
	tag = collisionManager.GetConflictionObjectsTag(EnemyCollisionName::RecieveCameraGun);
	for (auto it : tag)
	{
		if (((Status*)it->userData)->GetState() == Status::State::Active)
		{
			//�J�����K������󂯂�e���������ɋL�q

		}
	}

	//�_���[�W��̗͂ɔ��f
	gameObject.GetStatus().GetLife() -= damage;

	//�̗͂�0�ȉ��ɂȂ����玀�S
	if (gameObject.GetStatus().GetLife() <= 0)
	{
		SetNonEnemy();	//�G�𖳌��ɂ���
		gameObject.SetState(Status::State::Death);	//�X�e�[�^�X��Death�ɕύX

		//(��)�����G�t�F�N�g�̔���
		Effect::CreateEffect(EffectName::Effect1, gameObject.GetPos());
	}

	//�_���[�W���󂯂����莞�Ԗ��G��ԂɂȂ�
	bool isTakeDamage = damage > 0;
	if (gameObject.GetLife() > 0 && isTakeDamage)
	{
		gameObject.GetState() = Status::State::Invalid;
		invalidTime.ResetCntTime();
	}

	return isTakeDamage;
}

//-----------------------------------------------------------------------------
//�^�O�ɏ����i�[
void Enemy::SetTagData()
{
	skillAndChip->nowCharaChip = gameObject.GetImage().GetNowAnimationCharaChip();
}

//-----------------------------------------------------------------------------
//�A�j���[�V�����̍X�V
void Enemy::AnimationUpdate()
{
	gameObject.GetImage().Animation();

	//���݂̓���ƑO�̓��삪�قȂ�ꍇ�A�j���[�V�����p�^�[����ύX����
	if (beforeMoveOrder != nowMoveOrder)
	{
		gameObject.GetImage().ChangeAnimationPattern(nowMoveOrder);
	}
	beforeMoveOrder = nowMoveOrder;

	//���݂̓���p�^�[���ƑO�̃p�^�[�����قȂ�ꍇ�L�����`�b�v��ύX����
	if (beforePatternOrder != nowPatternOrder)
	{
		gameObject.GetImage().ChangeCharaChip(ems->GetNowAnimChip(nowPatternOrder));
	}
	beforePatternOrder = nowPatternOrder;
}

//-----------------------------------------------------------------------------
//�`��
void Enemy::Render()
{
	if (gameObject.GetState() == Status::State::Non ||
		gameObject.GetState() == Status::State::Death)
	{
		return;
	}

	K_Math::Vector4 color(1.f, 1.f, 1.f, 1.f);
	if (gameObject.GetState() == Status::State::Invalid)
	{
		if ((timeCnt.GetNowCntTime() % 10) < 5)	color = { 5.f, 5.f, 2.5f, 1.f };
		else									return;
	}

	gameObject.GetImage().ImageDraw3D(gameObject.GetStatus().GetPos(),
		gameObject.GetStatus().GetAngle(),
		gameObject.GetStatus().GetScale(),
		gameObject.GetStatus().GetDirection(),
		color);
	tempCollisionManager.Render();
}


//--------------------------------------------------------


//���W��ݒ�
void Enemy::SetPos(const K_Math::Vector3& setPos)
{
	gameObject.SetPos(setPos);
	collisionManager.SetBaseCollisionPos(setPos);
	collisionManager.SetSubCollisionPos(gameObject.GetDirection());
}

//���΍��W��ݒ�
void Enemy::SetRelativePos(const K_Math::Vector3& rePos)
{
	relativePos = rePos;
}

//���W���擾����
const K_Math::Vector3& Enemy::GetPos()
{
	return gameObject.GetPos();
}

//���W���I�t�Z�b�g
void Enemy::OffsetPos(const K_Math::Vector3& offPos)
{
	K_Math::Vector3 setPos = offPos + relativePos;
	SetPos(setPos);
}


//�̗͂�ݒ肷��
void Enemy::SetLife(int life, bool isTakeDamage)
{
	gameObject.GetLife() = life;
	if (isTakeDamage)
	{
		invalidTime.ResetCntTime();
		if (gameObject.GetLife() > 0)
		{
			gameObject.SetState(Status::State::Invalid);
		}
	}
}
//�̗͂��擾����
const int& Enemy::GetLife()
{
	return gameObject.GetLife();
}