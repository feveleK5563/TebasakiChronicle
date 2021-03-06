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
	CC::RemoveCollisionShape(&collisionData.receiveDamShape);
	CC::RemoveCollisionShape(&collisionData.receiveCamShape);
	CC::RemoveCollisionShape(&collisionData.visibilityShape);
	CC::RemoveCollisionShape(&collisionData.attackAreaShape);
	CC::RemoveCollisionShape(&collisionData.checkShape);
}

//-----------------------------------------------------------------------------
//EnemyMoveSetを取得
EnemyMoveSet* EnemyType::GetEnemyMoveSet()
{
	return emSet;
}
//-----------------------------------------------------------------------------
//画像名を取得
const std::string& EnemyType::GetTextureName()
{
	return paramData.textureName;
}
//-----------------------------------------------------------------------------
//体力上限を取得
const int EnemyType::GetMaxLife()
{
	return paramData.maxLife;
}
//-----------------------------------------------------------------------------
//プレイヤーに与えるダメージ量を取得
const int EnemyType::GetHitDamage()
{
	return paramData.hitDamage;
}
//-----------------------------------------------------------------------------
//1フレームの移動速度を取得
const float EnemyType::GetMoveSpeed()
{
	return paramData.moveSpeed;
}
//-----------------------------------------------------------------------------
//ジャンプ力を取得
const float EnemyType::GetJumpPower()
{
	return paramData.jumpPower;
}
//-----------------------------------------------------------------------------
//重力を利用するか否かを取得
const bool EnemyType::GetIsUseGravity()
{
	return paramData.isUseGravity;
}
//-----------------------------------------------------------------------------
//テクスチャを取得
K_Graphics::Texture* EnemyType::GetTexture()
{
	return textureData;
}

//-----------------------------------------------------------------------------
//地形用コリジョンデータの生成と取得
K_Physics::CollisionData* EnemyType::CreateAndGetBaseCollisionData()
{
	return CC::CreateCollisionObject(collisionData.baseShape, false, CollisionMask::Ground, CollisionMask::Non);
}
//-----------------------------------------------------------------------------
//被ダメ用コリジョンデータの生成と取得
K_Physics::CollisionData* EnemyType::CreateAndGetRecieveDamageCollisionData()
{
	return CC::CreateCollisionObject(collisionData.receiveDamShape, true, CollisionMask::TakeDamageEnemy, CollisionMask::EnemyCollision, collisionData.receiveDamPos);
}
//-----------------------------------------------------------------------------
//被カメラガン用コリジョンデータの生成と取得
K_Physics::CollisionData* EnemyType::CreateAndGetRecieveCameraCollisionData()
{
	return CC::CreateCollisionObject(collisionData.receiveCamShape, true, CollisionMask::CameraGunCollision, CollisionMask::EnemyCamCollision, collisionData.receiveCamPos);
}
//-----------------------------------------------------------------------------
//視界用コリジョンデータの生成と取得
K_Physics::CollisionData* EnemyType::CreateAndGetVisibilityCollisionData()
{
	return CC::CreateCollisionObject(collisionData.visibilityShape, true, CollisionMask::PlayerCollision, CollisionMask::Non, collisionData.visibilityPos);
}
//-----------------------------------------------------------------------------
//攻撃動作遷移用コリジョンの生成と取得
K_Physics::CollisionData* EnemyType::CreateAndGetAttackAreaCollisionData()
{
	return CC::CreateCollisionObject(collisionData.attackAreaShape, true, CollisionMask::PlayerCollision, CollisionMask::Non, collisionData.attackAreaPos);
}
//-----------------------------------------------------------------------------
//足元用コリジョンの生成と取得
K_Physics::CollisionData* EnemyType::CreateAndGetCheckFootCollisionData()
{
	return CC::CreateCollisionObject(collisionData.checkShape, true, CollisionMask::Ground, CollisionMask::Non, collisionData.checkFootPos);
}
//-----------------------------------------------------------------------------
//頭上用コリジョンの生成と取得
K_Physics::CollisionData* EnemyType::CreateAndGetCheckHeadCollisionData()
{
	return CC::CreateCollisionObject(collisionData.checkShape, true, CollisionMask::Ground, CollisionMask::Non, collisionData.checkHeadPos);
}