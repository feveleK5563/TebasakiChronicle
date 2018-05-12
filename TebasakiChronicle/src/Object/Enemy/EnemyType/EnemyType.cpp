#include "EnemyType.h"

EnemyType::EnemyType(const std::string& texPath, const ParameterData& param, const CollisionData& col) :
	paramData(param),
	collisionData(col),
	emSet(new EnemyMoveSet())
{
	textureData = CST::LoadAndGetTexture(param.textureName, texPath);
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
//テクスチャを取得
K_Graphics::Texture* EnemyType::GetTexture()
{
	return textureData;
}

//-----------------------------------------------------------------------------
//地形用コリジョンデータの生成と取得
K_Physics::CollisionData* EnemyType::GetBaseCollisionData()
{
	return CC::CreateCollisionObject(collisionData.baseShape, false, CollisionMask::Ground, CollisionMask::Non);
}
//-----------------------------------------------------------------------------
//被ダメ用コリジョンデータの生成と取得
K_Physics::CollisionData* EnemyType::GetRecieveDamageCollisionData()
{
	return CC::CreateCollisionObject(collisionData.receiveShape, true, CollisionMask::TakeDamageEnemy, CollisionMask::EnemyCollision, collisionData.receivePos);
}
//-----------------------------------------------------------------------------
//被カメラガン用コリジョンデータの生成と取得
K_Physics::CollisionData* EnemyType::GetRecieveCameraCollisionData()
{
	return CC::CreateCollisionObject(collisionData.receiveShape, true, CollisionMask::CameraGunCollision, CollisionMask::EnemyCamCollision, collisionData.receivePos);
}
//-----------------------------------------------------------------------------
//視界用コリジョンデータの生成と取得
K_Physics::CollisionData* EnemyType::GetFieldofviewCollisionData()
{
	return CC::CreateCollisionObject(collisionData.visibilityShape, true, CollisionMask::PlayerCollision, CollisionMask::Non, collisionData.visibilityPos);
}
//-----------------------------------------------------------------------------
//攻撃動作遷移用コリジョンの生成と取得
K_Physics::CollisionData* EnemyType::GetAttackAreaCollisionData()
{
	return CC::CreateCollisionObject(collisionData.attackAreaShape, true, CollisionMask::PlayerCollision, CollisionMask::Non, collisionData.attackAreaPos);
}
//-----------------------------------------------------------------------------
//足元用コリジョンの生成と取得
K_Physics::CollisionData* EnemyType::GetCheckFootCollisionData()
{
	return CC::CreateCollisionObject(collisionData.checkShape, true, CollisionMask::Ground, CollisionMask::Non, collisionData.checkFootPos);
}
//-----------------------------------------------------------------------------
//頭上用コリジョンの生成と取得
K_Physics::CollisionData* EnemyType::GetCheckHeadCollisionData()
{
	return CC::CreateCollisionObject(collisionData.checkShape, true, CollisionMask::Ground, CollisionMask::Non, collisionData.checkHeadPos);
}