#pragma once
#include "K_Physics\BulletPhysics.h"
#include "K_Graphics\CameraClass.h"
#include "K_Graphics\ShaderClass.h"

class CollisionCreator
{
private:
	static CollisionCreator* cCreator;
	CollisionCreator() {}

public:
	K_Physics::BulletPhysics bPhysics;

	//�C���X�^���X�𓾂�
	static CollisionCreator* GetInstance();
	//�������
	void Destroy();
};

//�֐��Q
namespace CC
{
	//�R���W�������Ǘ����镨���N���X�̎Q�Ƃ��擾
	K_Physics::BulletPhysics*	GetBulletPhysics();
	//�I������
	void Delete();

	//������(BulletPhysics���쐬)
	void Initialize();

	//���̌`����쐬���A�A�h���X�l�𓾂�
	K_Physics::CollisionShape* CreateSphereShape(float radius);
	//�J�v�Z���̌`����쐬���A�A�h���X�l�𓾂�
	K_Physics::CollisionShape* CreateCapsuleShape(float radius, float height);
	//�����̂̌`����쐬���A�A�h���X�l�𓾂�
	K_Physics::CollisionShape* CreateBoxShape(float halfWidth, float halfHeight, float halfDepth);

	//�R���W�����I�u�W�F�N�g���쐬���A�A�h���X�l�𓾂�
	K_Physics::CollisionData* CreateCollisionObject(btCollisionShape* shape, bool ghost, int myselfMask, int giveMask, const K_Math::Vector3 &pos = K_Math::Vector3(0, 0, 0), const K_Math::Vector3 &rot = K_Math::Vector3(0, 0, 0));

	//�������E���X�V���A���W��ύX����(�t���[���̍ŏ��ɌĂ�)
	void Run();

	//�R���W�����̈ړ��Ɠ����蔻��(���m&�d��)
	void MoveCharacter(K_Physics::CollisionData* obj, const K_Math::Vector3 &move, float vLimitAngle = 40.0f, float hLimitAngle = 0.0f);
	//�R���W�����̈ړ��Ɠ����蔻��(��G�c&�y��)
	void MoveCharacterDiscrete(K_Physics::CollisionData* obj, const K_Math::Vector3& move, bool vLimitDirection = true, bool hLimitDirection = false);
	//�Փ˂̃`�F�b�N
	std::vector<K_Physics::CollisionTag*>& FindConfrictionObjects(K_Physics::CollisionData *myself);

	//�R���W�����f�[�^���������
	void RemoveCollision(K_Physics::CollisionData** data);
	//�R���W�����̌`������������
	void RemoveCollisionShape(K_Physics::CollisionShape** shape);

	//�R���W�����̕`��
	void DebugDraw(K_Graphics::ShaderClass* sc, K_Graphics::CameraClass* cc);
}