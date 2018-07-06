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
	isBoss(isBoss)
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

	initialPos = setPos;
	gameObject.GetStatus().GetMaxLife() = cpyet->GetMaxLife();
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

	for (int i = 0; i < subCollisionNum; ++i)
	{
		collisionGiveMask[i] = collisionManager.GetSubCollisionGiveMask(i);
		collisionMyselfMask[i] = collisionManager.GetSubCollisionMyselfMask(i);
	}

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
	SetTugData();

	SetNonEnemy();
	gameObject.SetState(Status::State::Non);
}

//-----------------------------------------------------------------------------
//������Ԃɂ���
void Enemy::SetNonEnemy()
{
	//�J�����}���󂯗p�R���W�������������T�u�R���W�����̃}�X�N�𖳌��ɂ���
	for (int i = 0; i < subCollisionNum; ++i)
	{
		collisionManager.SetSubCollisionGiveMask(i, CollisionMask::Non);
		collisionManager.SetSubCollisionMyselfMask(i, CollisionMask::Non);
	}
	tempCollisionManager.DeleteCollision();
}

//-----------------------------------------------------------------------------
//��Ԃ�S�ď�����Ԃɖ߂�
void Enemy::ResetAndActiveEnemy()
{
	collisionManager.SetBaseCollisionObjectPosition(initialPos);
	gameObject.SetState(Status::State::Active);
	timeCnt.ResetCntTime();
	gameObject.GetStatus().GetLife() = gameObject.GetStatus().GetMaxLife();
	behaviorId = 0;
	nowMoveOrder = 0;
	nowPatternOrder = 0;
	beforeMoveOrder = 0;
	beforePatternOrder = 0;
	//�J�����}���󂯗p�R���W�������������T�u�R���W�����̃}�X�N��L���ɂ���
	for (int i = 0; i < subCollisionNum; ++i)
	{
		collisionManager.SetSubCollisionGiveMask(i, collisionGiveMask[i]);
		collisionManager.SetSubCollisionMyselfMask(i, collisionMyselfMask[i]);
	}
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
	else if (gameObject.GetState() != Status::State::Active)
	{
		return;
	}

	//�ړ��ʂ��[���N���A
	gameObject.GetMove().GetMoveVec() = K_Math::Vector3(0, 0, 0);

	//�d�͂����Z����
	gameObject.GetMove().GravityOperation(collisionManager.GetConflictionObjectsTag(3).size() > 0);

	//�ڐG���Ă���R���W�����𒲂ׂă_���[�W���󂯂�
	bool isTakeDamage = RecieveCollisionOperation();

	//�ݒ肳��Ă��铮����s��
	*skillAndChip->behaviorId = ems->EMove(nowMoveOrder, nowPatternOrder, timeCnt, collisionManager, tempCollisionManager, gameObject.GetStatus(), gameObject.GetMove(), isTakeDamage);

	//�A�j���[�V�����̍X�V
	AnimationUpdate();

	//�R���W�����𓮂���
	collisionManager.MoveBaseCollision(gameObject.GetMove().GetMoveVec(), gameObject.GetStatus().GetDirection(), true);
	gameObject.GetPos() = collisionManager.GetBaseCollisionObjectPosition();
	tempCollisionManager.Update();
	//�^�O�����X�V
	SetTugData();

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
			gameObject.SetPos(initialPos);
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
	if (gameObject.GetState() == Status::State::Invalid)
		return false;

	std::vector<K_Physics::CollisionTag*> tag;

	int damage = 0;	//��_���[�W

	//�_���[�W���󂯂�
	tag = collisionManager.GetConflictionObjectsTag(Enemy::EnemyCollisionName::RecieveDamage);
	for (auto it : tag)
	{
		if (((Status*)it->userData)->GetState() == Status::State::Active)
		{
			damage += ((Status*)it->userData)->GetAttackPoint();
		}
	}

	//�J�����K�����󂯂�
	tag = collisionManager.GetConflictionObjectsTag(Enemy::EnemyCollisionName::RecieveCameraGun);
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

	return damage > 0;
}

//-----------------------------------------------------------------------------
//�^�O�ɏ����i�[
void Enemy::SetTugData()
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
	if (gameObject.GetState() != Status::State::Active ||
		(gameObject.GetState() == Status::State::Invalid && (timeCnt.GetNowCntTime() % 2) == 0))
		return;

	gameObject.GetImage().ImageDraw3D(	gameObject.GetStatus().GetPos(),
										gameObject.GetStatus().GetAngle(),
										gameObject.GetStatus().GetScale(),
										gameObject.GetStatus().GetDirection());
	tempCollisionManager.Render();
}