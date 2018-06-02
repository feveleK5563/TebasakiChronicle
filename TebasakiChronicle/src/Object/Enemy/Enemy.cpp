#include "Enemy.h"
#include "../../Helper.h"

//�R���X�g���N�^
Enemy::Enemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction, const int indexNum) :
	behaviorId(0),
	nowMoveOrder(0),
	nowPatternOrder(0),
	beforeMoveOrder(0),
	beforePatternOrder(0)
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
	gameObject.GetStatus().SetStatusData(	Status::State::Active,
											setPos,
											K_Math::Vector3(0, 0, 0),
											K_Math::Vector3(1, 1, 1),
											direction,
											cpyet->GetHitDamage(),
											cpyet->GetMaxLife());
	if (cpyet->GetIsUseGravity() == false)
	{
		gameObject.GetMove().SetGravity(0.f);
	}

	gameObject.GetMove().SetAddVec(cpyet->GetMoveSpeed());
	gameObject.GetMove().SetJumpPow(cpyet->GetJumpPower());

	//�A�j���[�V�����ƕ\���摜�̐ݒ�
	gameObject.SetImage(cpyet->GetTexture(), false);
	gameObject.GetImage().ChangeAnimationPattern(nowMoveOrder);
	gameObject.GetImage().ChangeCharaChip(ems->GetNowAnimChip(nowPatternOrder));

	//�R���W�����̐ݒ�
	collisionManager.SetBaseCollisionData(cpyet->CreateAndGetBaseCollisionData(), setPos);	//�x�[�X�R���W����
	collisionManager.SetSubCollisionData(cpyet->CreateAndGetRecieveDamageCollisionData());	//0 ��_���[�W�p�R���W����
	collisionManager.SetSubCollisionData(cpyet->CreateAndGetFieldofviewCollisionData());	//1 ���E�p�R���W����
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
	SetTugData();
}

//-----------------------------------------------------------------------------
//�X�V
bool Enemy::Update()
{
	//�ړ��ʂ��[���N���A
	gameObject.GetMove().GetMoveVec() = K_Math::Vector3(0, 0, 0);

	//�d�͂����Z����
	gameObject.GetMove().GravityOperation(collisionManager.GetConflictionObjectsTag(3).size() > 0);

	//�ݒ肳��Ă��铮����s��
	ems->EMove(nowMoveOrder, nowPatternOrder, timeCnt, collisionManager, tempCollisionManager, gameObject.GetStatus(), gameObject.GetMove());

	//�A�j���[�V�����̍X�V
	AnimationUpdate();

	//�R���W�����𓮂���
	collisionManager.MoveBaseCollision(gameObject.GetMove().GetMoveVec(), gameObject.GetStatus().GetDirection(), true);
	gameObject.GetPos() = collisionManager.GetBaseCollisionObjectPosition();
	tempCollisionManager.Update();
	//�^�O�����X�V
	SetTugData();

	return RecieveCollisionOperation();
}

//-----------------------------------------------------------------------------
//�R���W�����Ƃ̐ڐG����
//��_���[�W�ɂ���đ̗͂�0�ɂȂ�����true��Ԃ�
bool Enemy::RecieveCollisionOperation()
{
	std::vector<K_Physics::CollisionTag*> tag;

	//�_���[�W���󂯂�
	tag = collisionManager.GetConflictionObjectsTag(EnemyCollisionName::RecieveDamage);
	for (auto it : tag)
	{
		if (((Status*)it->userData)->GetState() == Status::State::Active)
		{
			gameObject.GetStatus().GetLife() -= ((Status*)it->userData)->GetAttackPoint();
		}
	}
	int hp = gameObject.GetStatus().GetLife();

	//�J�������󂯂�
	tag = collisionManager.GetConflictionObjectsTag(EnemyCollisionName::RecieveCameraGan);
	for (auto it : tag)
	{
		if (((Status*)it->userData)->GetState() == Status::State::Active)
		{
			//�J�����K������󂯂�e���������ɏ����Ȃ���

		}
	}

	return gameObject.GetStatus().GetLife() <= 0;
}

//-----------------------------------------------------------------------------
//�^�O�ɏ����i�[
void Enemy::SetTugData()
{
	skillAndChip->nowCharaChip = gameObject.GetImage().GetNowAnimationCharaChip();
}

//-----------------------------------------------------------------------------
//�`��A�A�j���[�V�����̍X�V
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
	gameObject.GetImage().ImageDraw3D(	gameObject.GetStatus().GetPos(),
										gameObject.GetStatus().GetAngle(),
										gameObject.GetStatus().GetScale(),
										gameObject.GetStatus().GetDirection());
	tempCollisionManager.Render();
}