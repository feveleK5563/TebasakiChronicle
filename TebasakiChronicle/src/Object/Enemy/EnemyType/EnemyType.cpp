#include "EnemyType.h"

EnemyType::EnemyType(const ParameterData& param, const CollisionData& col) :
	paramData(param),
	collisionData(col),
	emSet(new EnemyMoveSet())
{
	textureData = CST::LoadAndGetTexture(param.textureName, param.texturePath);
}

EnemyType::~EnemyType()
{
	CST::DeleteTexture(paramData.textureName);
	delete emSet;
	CC::RemoveCollisionShape(&collisionData.baseShape);
	CC::RemoveCollisionShape(&collisionData.receiveShape);
	CC::RemoveCollisionShape(&collisionData.visibilityShape);
	CC::RemoveCollisionShape(&collisionData.attackAreaShape);
	CC::RemoveCollisionShape(&collisionData.checkShape);
}

//-----------------------------------------------------------------------------
//EnemyMoveSet���擾
EnemyMoveSet* EnemyType::GetEnemyMoveSet()
{
	return emSet;
}
//-----------------------------------------------------------------------------
//�摜�����擾
const std::string& EnemyType::GetTextureName()
{
	return paramData.textureName;
}
//-----------------------------------------------------------------------------
//�̗͏�����擾
const int EnemyType::GetMaxLife()
{
	return paramData.maxLife;
}
//-----------------------------------------------------------------------------
//�v���C���[�ɗ^����_���[�W�ʂ��擾
const int EnemyType::GetHitDamage()
{
	return paramData.hitDamage;
}
//-----------------------------------------------------------------------------
//1�t���[���̈ړ����x���擾
const float EnemyType::GetMoveSpeed()
{
	return paramData.moveSpeed;
}
//-----------------------------------------------------------------------------
//�W�����v�͂��擾
const float EnemyType::GetJumpPower()
{
	return paramData.jumpPower;
}
//-----------------------------------------------------------------------------
//�e�N�X�`�����擾
K_Graphics::Texture* EnemyType::GetTexture()
{
	return textureData;
}

//-----------------------------------------------------------------------------
//�n�`�p�R���W�����f�[�^�̐����Ǝ擾
K_Physics::CollisionData* EnemyType::CreateAndGetBaseCollisionData()
{
	return CC::CreateCollisionObject(collisionData.baseShape, false, CollisionMask::Ground, CollisionMask::Non);
}
//-----------------------------------------------------------------------------
//��_���p�R���W�����f�[�^�̐����Ǝ擾
K_Physics::CollisionData* EnemyType::CreateAndGetRecieveDamageCollisionData()
{
	return CC::CreateCollisionObject(collisionData.receiveShape, true, CollisionMask::TakeDamageEnemy, CollisionMask::EnemyCollision, collisionData.receivePos);
}
//-----------------------------------------------------------------------------
//��J�����K���p�R���W�����f�[�^�̐����Ǝ擾
K_Physics::CollisionData* EnemyType::CreateAndGetRecieveCameraCollisionData()
{
	return CC::CreateCollisionObject(collisionData.receiveShape, true, CollisionMask::CameraGunCollision, CollisionMask::EnemyCamCollision, collisionData.receivePos);
}
//-----------------------------------------------------------------------------
//���E�p�R���W�����f�[�^�̐����Ǝ擾
K_Physics::CollisionData* EnemyType::CreateAndGetFieldofviewCollisionData()
{
	return CC::CreateCollisionObject(collisionData.visibilityShape, true, CollisionMask::PlayerCollision, CollisionMask::Non, collisionData.visibilityPos);
}
//-----------------------------------------------------------------------------
//�U������J�ڗp�R���W�����̐����Ǝ擾
K_Physics::CollisionData* EnemyType::CreateAndGetAttackAreaCollisionData()
{
	return CC::CreateCollisionObject(collisionData.attackAreaShape, true, CollisionMask::PlayerCollision, CollisionMask::Non, collisionData.attackAreaPos);
}
//-----------------------------------------------------------------------------
//�����p�R���W�����̐����Ǝ擾
K_Physics::CollisionData* EnemyType::CreateAndGetCheckFootCollisionData()
{
	return CC::CreateCollisionObject(collisionData.checkShape, true, CollisionMask::Ground, CollisionMask::Non, collisionData.checkFootPos);
}
//-----------------------------------------------------------------------------
//����p�R���W�����̐����Ǝ擾
K_Physics::CollisionData* EnemyType::CreateAndGetCheckHeadCollisionData()
{
	return CC::CreateCollisionObject(collisionData.checkShape, true, CollisionMask::Ground, CollisionMask::Non, collisionData.checkHeadPos);
}