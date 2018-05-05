#pragma once
#include "EnemyMoveSet.h"
#include "../../../BaseClass/Collision/CollisionManager.h"

//EnemyMoveSetとその他敵の生成に必要となる敵情報
class EnemyType
{
private:
	EnemyMoveSet* emSet;		//動作まとめ

	const std::string			textureName;	//画像名
	K_Graphics::Texture*		texture;		//テクスチャ
	const int					maxLife;		//体力上限
	const int					hitDamage;		//接触時、プレイヤーに与えるダメージ

	K_Physics::CollisionShape*	baseShape;			//地形用コリジョンの形状
	K_Physics::CollisionShape*	receiveShape;		//被ダメ、カメラガン用コリジョンの形状
	K_Physics::CollisionShape*	fovShape;			//視界用コリジョンの形状
	K_Physics::CollisionShape*	attackAreaShape;	//攻撃動作遷移用コリジョンの形状
	K_Physics::CollisionShape*	checkShape;			//足元、頭上判定用コリジョンの形状

	K_Math::Vector3		receivePos;		//被ダメ、カメラガン用コリジョンの位置
	K_Math::Vector3		fovPos;			//視界用コリジョンの位置
	K_Math::Vector3		attackAreaPos;	//攻撃動作遷移用コリジョンの位置
	K_Math::Vector3		checkFootPos;	//足元判定コリジョンの位置
	K_Math::Vector3		checkHeadPos;	//頭上判定コリジョンの位置

public:
	//コンストラクタ
	EnemyType(	std::string texName,
				int maxlife,
				int hitdamage,
				K_Physics::CollisionShape* sBase,
				K_Physics::CollisionShape* sReceive,
				K_Physics::CollisionShape* sFieldofview,
				K_Physics::CollisionShape* sAttackArea,
				K_Physics::CollisionShape* sCheck,
				K_Math::Vector3& pRecieve,
				K_Math::Vector3& pFieldofview,
				K_Math::Vector3& pAttackArea,
				K_Math::Vector3& pCheckFoot,
				K_Math::Vector3& pCheckHead);
	//デストラクタ
	~EnemyType();

	//EnemyMoveSetを取得
	EnemyMoveSet* GetEnemyMoveSet();
	//画像名を取得
	const std::string& GetTextureName();
	//体力上限を取得
	const int GetMaxLife();
	//プレイヤーに与えるダメージ量を取得
	const int GetHitDamage();
	//テクスチャを取得
	K_Graphics::Texture* GetTexture();

	//地形用コリジョンデータの生成と取得
	K_Physics::CollisionData* GetBaseCollisionData();
	//被ダメ用コリジョンデータの生成と取得
	K_Physics::CollisionData* GetRecieveDamageCollisionData();
	//被カメラガン用コリジョンデータの生成と取得
	K_Physics::CollisionData* GetRecieveCameraCollisionData();
	//視界用コリジョンデータの生成と取得
	K_Physics::CollisionData* GetFieldofviewCollisionData();
	//攻撃動作遷移用コリジョンの生成と取得
	K_Physics::CollisionData* GetAttackAreaCollisionData();
	//足元用コリジョンの生成と取得
	K_Physics::CollisionData* GetCheckFootCollisionData();
	//頭上用コリジョンの生成と取得
	K_Physics::CollisionData* GetCheckHeadCollisionData();
};
