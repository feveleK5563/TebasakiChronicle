#include "CollisionManager.h"

//�R���X�g���N�^
CollisionManager::CollisionManager() :
	baseCollision(nullptr),
	basePosition(K_Math::Vector3(0, 0, 0)){}

//�f�X�g���N�^
CollisionManager::~CollisionManager()
{
	for (auto it : subCollision)
	{
		CC::RemoveCollision(&it->collision);
		delete it;
	}
	CC::RemoveCollision(&baseCollision);
}

//-----------------------------------------------------------------------------
//�x�[�X�R���W�������쐬����
void CollisionManager::CreateBaseCollisionData(K_Physics::CollisionShape* cs, const K_Math::Vector3& pos, const K_Math::Vector3& rot, bool isJudge)
{
	if (baseCollision != nullptr)
		return;

	if (isJudge == true)
	{
		//�n�`�Ƃ̂߂荞�ݔ�����s���R���W�������쐬
		baseCollision = CC::CreateCollisionObject(cs, false, CollisionMask::Ground, CollisionMask::Non, pos, rot);
	}
	else
	{
		//�߂荞�ݔ�����s��Ȃ��R���W�������쐬
		baseCollision = CC::CreateCollisionObject(cs, true, CollisionMask::Ground, CollisionMask::Non, pos, rot);
	}
}
//-----------------------------------------------------------------------------
//�x�[�X�R���W������ݒ肷��
void CollisionManager::SetBaseCollisionData(K_Physics::CollisionData* cd, const K_Math::Vector3& pos)
{
	if (baseCollision != nullptr)
		return;

	baseCollision = cd;
	baseCollision->SetCollisionPosition(pos);
}

//-----------------------------------------------------------------------------
//�n�`�Ƃ��ĐU�镑���x�[�X�R���W�������쐬����
//�����ɗ��R���Ȃ�����g�p���Ȃ�����(��l������false�Œʏ�̃x�[�X�R���W�������쐬����)
void CollisionManager::CreateGroundCollisionData(K_Physics::CollisionShape* cs, const K_Math::Vector3& pos, const K_Math::Vector3& rot, bool doGround)
{
	if (doGround == false)
	{
		CreateBaseCollisionData(cs, pos, rot, false);
		return;
	}

	if (baseCollision != nullptr)
		return;

	//�n�`�Ƃ��ĐU�镑���R���W�������쐬
	baseCollision = CC::CreateCollisionObject(cs, false, CollisionMask::Non, CollisionMask::Ground, pos, rot);
}


//-----------------------------------------------------------------------------
//�T�u�R���W�������쐬����
void CollisionManager::CreateSubCollisionData(K_Physics::CollisionShape* cs, int myselfMask, int giveMask, const K_Math::Vector3& pos)
{
	if (baseCollision == nullptr)
		return;

	subCollision.emplace_back(new Sub(CC::CreateCollisionObject(cs, true, myselfMask, giveMask, pos + baseCollision->GetCollisionPosition()), pos));
}
//-----------------------------------------------------------------------------
//�T�u�R���W������ݒ肷��
void CollisionManager::SetSubCollisionData(K_Physics::CollisionData* cd)
{
	if (baseCollision == nullptr)
		return;

	K_Math::Vector3* ccd = &cd->GetCollisionPosition();
	subCollision.emplace_back(new Sub(cd, *ccd));
	subCollision.back()->collision->SetCollisionPosition(*ccd + baseCollision->GetCollisionPosition());
}

//-----------------------------------------------------------------------------
//�w�肵���T�u�R���W�����Ƀ^�O(TagName)��ݒ肷��
void CollisionManager::SetSubCollisionTagName(int subNum, std::string& name)
{
	subCollision[subNum]->collision->tag.tagName = name;
}
//-----------------------------------------------------------------------------
//�w�肵���T�u�R���W�����Ƀ^�O(TagIndex)��ݒ肷��
void CollisionManager::SetSubCollisionTagIndex(int subNum, int indexNum)
{
	subCollision[subNum]->collision->tag.tagIndex = indexNum;
}
//-----------------------------------------------------------------------------
//�w�肵���T�u�R���W�����̃^�O(UserData)��ݒ肷��
void CollisionManager::SetSubCollisionUserData(int subNum, void* data)
{
	subCollision[subNum]->collision->tag.userData = data;
}

//-----------------------------------------------------------------------------
//�w�肵���T�u�R���W�����̃}�X�N��ݒ肷��
void CollisionManager::SetSubCollisionMyselfMask(int subNum, int myselfMask)
{
	subCollision[subNum]->collision->SetMyselfMask(myselfMask);
}
void CollisionManager::SetSubCollisionGiveMask(int subNum, int giveMask)
{
	subCollision[subNum]->collision->SetGiveMask(giveMask);
}
//-----------------------------------------------------------------------------
//�w�肵���T�u�R���W�����̃}�X�N�𒲂ׂ�
int CollisionManager::GetSubCollisionMyselfMask(int subNum)
{
	return subCollision[subNum]->collision->GetMyselfMask();
}
int CollisionManager::GetSubCollisionGiveMask(int subNum)
{
	return subCollision[subNum]->collision->GetGiveMask();
}

//-----------------------------------------------------------------------------
//�x�[�X�R���W�����𓮂����A�t�����ăT�u�̍��W��ݒ肷��
void CollisionManager::MoveBaseCollision(K_Math::Vector3& moveVec, int direction, bool isLightness)
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
	SetSubCollisionPos(direction);
}

//-----------------------------------------------------------------------------
//�x�[�X�R���W�����̍��W����ɃT�u�R���W�����̈ʒu��ݒ肷��
void CollisionManager::SetSubCollisionPos(int angle)
{
	for (auto it : subCollision)
	{
		K_Math::Vector3 setPos = it->relativePos;

		if (angle == 180)	//���������������ꍇ�ʒu�𔽓]
			setPos.x *= -1.f;

		it->collision->SetCollisionPosition(setPos + baseCollision->GetCollisionPosition());
	}
}

//-----------------------------------------------------------------------------
//�w�肵���T�u�R���W�����̎󂯎�����^�O��Ԃ�
std::vector<K_Physics::CollisionTag*>& CollisionManager::GetConflictionObjectsTag(int subNum)
{
	return CC::FindConfrictionObjects(subCollision[subNum]->collision);
}

//-----------------------------------------------------------------------------
//�x�[�X�R���W�������n�`�R���W�����ƏՓ˂��Ă�����true��Ԃ�
bool CollisionManager::CheckHitBaseCollisionObject()
{
	return CC::FindConfrictionObjects(baseCollision).size() > 0;
}

//-----------------------------------------------------------------------------
//�w�肵���T�u�R���W���������R���W�����ƏՓ˂��Ă�����true��Ԃ�
bool CollisionManager::CheckHitSubCollisionObejct(int subNum)
{
	return CC::FindConfrictionObjects(subCollision[subNum]->collision).size() > 0;
}

//-----------------------------------------------------------------------------
//�x�[�X�R���W�����̍��W��Ԃ�
K_Math::Vector3& CollisionManager::GetBaseCollisionObjectPosition()
{
	//���W���擾(����baseCollision->GeteCollisionPosition��Ԃ��Ǝ������s���邽��)
	basePosition = baseCollision->GetCollisionPosition();

	return basePosition;
}

//-----------------------------------------------------------------------------
//�x�[�X�R���W�����̍��W��ݒ肷��
void CollisionManager::SetBaseCollisionObjectPosition(const K_Math::Vector3& setpos)
{
	baseCollision->SetCollisionPosition(setpos);
}