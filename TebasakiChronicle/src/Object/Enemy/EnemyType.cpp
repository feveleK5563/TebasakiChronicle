#include "EnemyType.h"

EnemyType::EnemyType(std::string texName, K_Physics::CollisionShape* cs, int ml, int hd) :
	textureName(texName),
	maxLife(ml),
	hitDamage(hd),
	emSet(new EnemyMoveSet())
{
	//テクスチャを読み込む
	texture = CST::LoadAndGetTexture(textureName, "data/image/" + textureName + ".tga");
	//コリジョンの形状を設定
	cShape = cs;
}

EnemyType::~EnemyType()
{
	delete emSet;
}