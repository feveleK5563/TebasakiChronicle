#include "CollisionManager.h"

//�R���X�g���N�^
CollisionManager::CollisionManager() :
	baseCollision(nullptr) {}

//�f�X�g���N�^
CollisionManager::~CollisionManager()
{
	for (auto it : subCollision)
	{
		delete it->relativePos;
		delete it;
	}
}

//-----------------------------------------------------------------------------
//�x�[�X�R���W������ݒ肷��
void CollisionManager::CreateBaseCollisionData(K_Physics::CollisionShape* cs, const K_Math::Vector3& pos, const K_Math::Vector3& rot, bool isJudge)
{
	if (baseCollision != nullptr)
		return;

	if (isJudge == true)
	{
		//�n�`�Ƃ̂߂荞�ݏ������s��
		baseCollision = CC::CreateCollisionObject(cs, false, 1, pos, rot);
	}
	else
	{
		//�������s��Ȃ�
		baseCollision = CC::CreateCollisionObject(cs, false, 1, pos, rot);
	}
}

//-----------------------------------------------------------------------------
//�T�u�R���W������ݒ肷��
void CollisionManager::CreateSubCollisionData(K_Physics::CollisionShape* cs, int mask, const K_Math::Vector3& pos, const K_Math::Vector3& rot)
{
	if (baseCollision == nullptr)
		return;

	subCollision.emplace_back(	new Sub(CC::CreateCollisionObject(cs, true, mask, pos + baseCollision->GetCollisionPosition(), rot),
								new K_Math::Vector3(pos)));
}

//-----------------------------------------------------------------------------
//�T�u�R���W�����̃^�O��ݒ肷��
void CollisionManager::SetSubCollisionTug(int subNum, void* tug)
{
	subCollision[subNum]->collision->tag.userData = tug;
}

//-----------------------------------------------------------------------------
//�x�[�X�R���W�����𓮂����A�t�����ăT�u�̍��W��ݒ肷��
void CollisionManager::MoveBaseCollision(K_Math::Vector3 moveVec, int angle, bool isLightness)
{
	if (isLightness == true)
	{
		//�y��&��G�c
		CC::MoveCharacterDiscrete(baseCollision, moveVec);
	}
	else
	{
		//�d��&���m
		CC::MoveCharacter(baseCollision, moveVec);
	}

	//�x�[�X�R���W��������Ɋe�T�u�R���W�����̈ʒu��ݒ�
	SetSubCollisionPos(angle);
}

//-----------------------------------------------------------------------------
//�x�[�X�R���W�����̍��W����ɃT�u�R���W�����̈ʒu��ݒ肷��
void CollisionManager::SetSubCollisionPos(int angle)
{
	for (auto it : subCollision)
	{
		K_Math::Vector3 setPos = *it->relativePos;

		if (angle == 180)	//���������������ꍇ�ʒu�𔽓]
			setPos.x() *= -1.f;

		it->collision->SetCollisionPosition(setPos + baseCollision->GetCollisionPosition());
	}
}

//-----------------------------------------------------------------------------
//�w�肵���T�u�R���W�����̎󂯎�����^�O�̓��AuserData�݂̂𒊏o���ĕԂ�
std::vector<void*> CollisionManager::GetConflictionObjectsUserData(int subNum)
{
	std::vector<void*> userData;
	std::vector<K_Physics::CollisionTag*> fco = CC::FindConfrictionObjects(subCollision[subNum]->collision);
	for (auto it : fco)
	{
		//tagIndex�����̃R���W�����Ɠ���
		if (it->tagIndex == subCollision[subNum]->collision->tag.tagIndex)
		{
			continue;
		}
		userData.emplace_back(it->userData);
	}
	return userData;
}