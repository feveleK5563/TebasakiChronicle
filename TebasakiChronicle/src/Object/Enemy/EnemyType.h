#pragma once
#include "EnemyMoveSet.h"

//EnemyMoveSetとその他敵の生成に必要となる敵情報
class EnemyType
{
public:
	EnemyMoveSet*	emSet;		//動作まとめ

	const std::string			imageName;	//画像名
	const int					maxLife;	//体力上限
	const int					hitDamage;	//接触時、プレイヤーに与えるダメージ
	K_Graphics::Texture*		texture;	//テクスチャ
	//接触用コリジョンのサイズ
	//視界用コリジョンのサイズ
	//攻撃動作遷移用コリジョンのサイズ


	//コンストラクタ
	EnemyType(std::string imgName, int ml, int atk);
	//デストラクタ
	~EnemyType();
};
