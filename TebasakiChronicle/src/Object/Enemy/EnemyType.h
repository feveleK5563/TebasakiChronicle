#pragma once
#include "EnemyMoveSet.h"
#include "../../BaseClass/Collision/CollisionCreator.h"

//EnemyMoveSetとその他敵の生成に必要となる敵情報
class EnemyType
{
public:
	EnemyMoveSet * emSet;		//動作まとめ

	const std::string			textureName;	//画像名
	const int					maxLife;		//体力上限
	const int					hitDamage;		//接触時、プレイヤーに与えるダメージ
	K_Graphics::Texture*		texture;		//テクスチャ
	K_Physics::CollisionShape*	cShape;			//接触用コリジョンの形状
												//視界用コリジョンの形状
												//攻撃動作遷移用コリジョンの形状

	//コンストラクタ
	EnemyType(std::string imgName, K_Physics::CollisionShape* cs, int ml, int atk);
	//デストラクタ
	~EnemyType();
};
