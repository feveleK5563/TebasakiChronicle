#include "CollisionCreator.h"

CollisionCreator* CollisionCreator::cCreator = nullptr;
//-------------------------------------------------------------------
//�C���X�^���X�𓾂�
CollisionCreator* CollisionCreator::GetInstance()
{
	if (cCreator == nullptr)
		cCreator = new CollisionCreator();

	return cCreator;
}
//-------------------------------------------------------------------
//�������
void CollisionCreator::Destroy()
{
	delete cCreator;
}

CollisionCreator* cc = CollisionCreator::GetInstance();

namespace CC
{
	//�R���W�������Ǘ����镨���N���X�̎Q�Ƃ��擾
	K_Physics::BulletPhysics*	GetBulletPhysics()
	{
		return cc->bPhysics;
	}

	//�I������
	void Delete()
	{
		if (cc != nullptr)
		{
			cc->Destroy();
			cc = nullptr;
		}
	}

	//����������
	void Initialize()
	{
		if (cc->bPhysics == nullptr)
		{
			cc->bPhysics = new K_Physics::BulletPhysics();
			return;
		}
		cc->bPhysics->Initialize();
	}

	//���̌`����쐬���A�A�h���X�l�𓾂�
	K_Physics::CollisionShape* CreateSphereShape(float radius)
	{
		return cc->bPhysics->CreateSphereShape(radius);
	}
	//�J�v�Z���̌`����쐬���A�A�h���X�l�𓾂�
	K_Physics::CollisionShape* CreateCapsuleShape(float radius, float height)
	{
		return cc->bPhysics->CreateCapsuleShape(radius, height);
	}
	//�����̂̌`����쐬���A�A�h���X�l�𓾂�
	K_Physics::CollisionShape* CreateBoxShape(float halfWidth, float halfHeight, float halfDepth)
	{
		return cc->bPhysics->CreateBoxShape(halfWidth, halfHeight, halfDepth);
	}

	//�R���W�����I�u�W�F�N�g���쐬���A�A�h���X�l�𓾂�
	K_Physics::CollisionData* CreateCollisionObject(btCollisionShape* shape, bool ghost, int myselfMask, int giveMask, const K_Math::Vector3 &pos, const K_Math::Vector3 &rot)
	{
		return cc->bPhysics->CreateCollisionObject(shape, ghost, myselfMask, giveMask, pos, rot);
	}

	//�������E���X�V���A���W��ύX����(�t���[���̍ŏ��ɌĂ�)
	void Run()
	{
		cc->bPhysics->Run();
	}

	//�R���W�����̈ړ��Ɠ����蔻��(���m&�d��)
	void MoveCharacter(K_Physics::CollisionData* obj, const K_Math::Vector3 &move, float vLimitAngle, float hLimitAngle)
	{
		cc->bPhysics->MoveCharacter(obj, move, vLimitAngle, hLimitAngle);
	}
	//�R���W�����̈ړ��Ɠ����蔻��(��G�c&�y��)
	void MoveCharacterDiscrete(K_Physics::CollisionData* obj, const K_Math::Vector3& move, bool vLimitDirection, bool hLimitDirection)
	{
		cc->bPhysics->MoveCharacterDiscrete(obj, move, vLimitDirection, hLimitDirection);
	}
	//�Փ˂̃`�F�b�N
	std::vector<K_Physics::CollisionTag*>& FindConfrictionObjects(K_Physics::CollisionData *myself)
	{
		return cc->bPhysics->FindConfrictionObjects(myself);
	}

	//�R���W�����f�[�^���������
	void RemoveCollision(K_Physics::CollisionData** data)
	{
		cc->bPhysics->RemoveCollision(data);
	}
	//�R���W�����̌`������������
	void RemoveCollisionShape(K_Physics::CollisionShape** shape)
	{
		cc->bPhysics->RemoveCollisionShape(shape);
	}

	//�R���W�����̕`��
	void DebugDraw(K_Graphics::ShaderClass* shaderc, K_Graphics::CameraClass* camerac)
	{
		cc->bPhysics->DebugDraw(shaderc, camerac);
	}
}