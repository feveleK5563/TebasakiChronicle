#include "EnemyType.h"

EnemyType::EnemyType(std::string imgName, K_Physics::CollisionShape* cs, int ml, int hd) :
	imageName(imgName),
	maxLife(ml),
	hitDamage(hd),
	emSet(new EnemyMoveSet())
{
	//テクスチャを読み込む
	texture = CST::LoadAndGetTexture(imageName, "data/image/" + imgName + ".tga");
	//コリジョンの形状を設定
	cShape = cs;
}

EnemyType::~EnemyType()
{
	delete emSet;
}
