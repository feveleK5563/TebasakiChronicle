#pragma once
#include "CollisionCreator.h"
#include "../../Object/GameObject.h"

//mask�̐ݒ�ɂ͂�����g�p
enum CollisionMask
{
	Non					= 0,
	Ground				= 1 << 0,
	PlayerCollision		= 1 << 1,
	EnemyCollision		= 1 << 2,
	TakeDamagePlayer	= 1 << 3,
	TakeDamageEnemy		= 1 << 4,
	CameraGunCollision	= 1 << 5,
	EnemyCamCollision	= 1 << 6,
};

//�R���W�����f�[�^�Ǘ�����
//�R���W�����̌`����͊i�[���Ȃ��̂Ŋe���ŊǗ����邱��
class CollisionManager
{
private:
	K_Physics::CollisionData*	baseCollision;	//��ƂȂ�R���W����(�n�`�Ƃ̂߂荞�ݔ���̂ݍs��)
	K_Math::Vector3				basePosition;	//��R���W�����̍��W
	struct Sub	//�T�u�R���W����
	{
		K_Physics::CollisionData*	collision;		//�T�u�ƂȂ�R���W����
		K_Math::Vector3				relativePos;	//�x�[�X�R���W�����Ƃ̑��΍��W

		Sub(K_Physics::CollisionData*	cln,
			const K_Math::Vector3&		rp) :
			collision(cln),
			relativePos(rp){}
	};
	std::vector<Sub*> subCollision;

	//�x�[�X�R���W�����̍��W����ɃT�u�R���W�����̈ʒu��ݒ肷��
	void SetSubCollisionPos(int angle);

public:
	CollisionManager();
	~CollisionManager();

	//�x�[�X�R���W�������쐬����
	//��l������false�Œn�`�Ƃ̂߂荞�ݔ�����s��Ȃ�
	void CreateBaseCollisionData(K_Physics::CollisionShape* cs, const K_Math::Vector3& pos, const K_Math::Vector3& rot, bool isJudge);
	//�x�[�X�R���W������ݒ肷��
	void SetBaseCollisionData(K_Physics::CollisionData* cd, const K_Math::Vector3& pos);

	//�n�`�Ƃ��ĐU�镑���x�[�X�R���W�������쐬����
	//�����ɗ��R���Ȃ�����g�p���Ȃ�����(��l������false�ł߂荞�ݔ���Ȃ��ʏ�x�[�X�R���W�������쐬����)
	void CreateGroundCollisionData(K_Physics::CollisionShape* cs, const K_Math::Vector3& pos, const K_Math::Vector3& rot, bool doGround);

	//�T�u�R���W�������쐬����(�w����W�̓I�u�W�F�N�g���E�������̃x�[�X�R���W�����Ƃ̑��΍��W)
	//���ghost��true
	void CreateSubCollisionData(K_Physics::CollisionShape* cs, int myselfMask, int giveMask, const K_Math::Vector3& pos);
	//�T�u�R���W������ݒ肷��
	void SetSubCollisionData(K_Physics::CollisionData* cd);

	//�w�肵���T�u�R���W�����Ƀ^�O(TagName)��ݒ肷��
	void SetSubCollisionTagName(int subNum, std::string& name);
	//�w�肵���T�u�R���W�����Ƀ^�O(TagIndex)��ݒ肷��
	void SetSubCollisionTagIndex(int subNum, int indexNum);
	//�w�肵���T�u�R���W�����Ƀ^�O(UserData)��ݒ肷��
	void SetSubCollisionUserData(int subNum, void* data);

	//�w�肵���T�u�R���W�����̃}�X�N��ݒ肷��
	void SetSubCollisionMyselfMask(int subNum, int myselfMask);
	void SetSubCollisionGiveMask(int subNum, int giveMask);
	//�w�肵���T�u�R���W�����̃}�X�N�𒲂ׂ�
	int GetSubCollisionMyselfMask(int subNum);
	int GetSubCollisionGiveMask(int subNum);

	//�x�[�X�R���W�����𓮂����A�t�����ăT�u�̍��W��ݒ肷��
	//��O������true�Ōy�ʂȏ���(�߂荞�ݔ�����s���ꍇ��false����)
	void MoveBaseCollision(K_Math::Vector3& moveVec, int direction, bool isLightness);

	//�w�肵���T�u�R���W�����̎󂯎�����^�O��Ԃ�
	std::vector<K_Physics::CollisionTag*>& GetConflictionObjectsTag(int subNum);

	//�x�[�X�R���W�������n�`�R���W�����ƏՓ˂��Ă�����true��Ԃ�
	bool CheckHitBaseCollisionObject();

	//�w�肵���T�u�R���W���������R���W�����ƏՓ˂��Ă�����true��Ԃ�
	bool CheckHitSubCollisionObejct(int subNum);

	//�x�[�X�R���W�����̍��W��Ԃ�
	K_Math::Vector3& GetBaseCollisionObjectPosition();

	//�x�[�X�R���W�����̍��W��ݒ肷��
	void SetBaseCollisionObjectPosition(const K_Math::Vector3& setpos);
};