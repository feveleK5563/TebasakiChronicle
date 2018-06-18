#pragma once
#include "EnemyMoveSet.h"
#include "../../../BaseClass/Collision/CollisionManager.h"

//EnemyMoveSetとその他敵の生成に必要となる敵情報
class EnemyType
{
public:
	struct ParameterData	//敵の各種情報
	{
		std::string		texturePath;	//テクスチャのパス
		std::string		textureName;	//テクスチャ名
		int				maxLife;		//体力上限
		int				hitDamage;		//プレイヤーに与えるダメージ
		float			moveSpeed;		//移動速度
		float			jumpPower;		//ジャンプ力
		bool			isUseGravity;	//重力を利用するか否か

		ParameterData(std::string& tp, std::string& tn, int ml, int hd, float ms, float jp, bool isug):
			texturePath(tp), textureName(tn), maxLife(ml), hitDamage(hd), moveSpeed(ms), jumpPower(jp), isUseGravity(isug){}
	};
	struct CollisionData	//コリジョンの情報
	{
		K_Physics::CollisionShape*	baseShape;			//地形用コリジョンの形状
		K_Physics::CollisionShape*	receiveShape;		//被ダメ、カメラガン用コリジョンの形状
		K_Physics::CollisionShape*	visibilityShape;	//視界用コリジョンの形状
		K_Physics::CollisionShape*	attackAreaShape;	//攻撃動作遷移用コリジョンの形状
		K_Physics::CollisionShape*	checkShape;			//足元、頭上判定用コリジョンの形状
		K_Math::Vector3		receivePos;		//被ダメ、カメラガン用コリジョンの位置
		K_Math::Vector3		visibilityPos;	//視界用コリジョンの位置
		K_Math::Vector3		attackAreaPos;	//攻撃動作遷移用コリジョンの位置
		K_Math::Vector3		checkFootPos;	//足元判定コリジョンの位置
		K_Math::Vector3		checkHeadPos;	//頭上判定コリジョンの位置

		CollisionData(	K_Physics::CollisionShape* bs, K_Physics::CollisionShape* rs, K_Physics::CollisionShape* vs, K_Physics::CollisionShape* aas, K_Physics::CollisionShape* cs,
						K_Math::Vector3& rp, K_Math::Vector3& vp, K_Math::Vector3& aap, K_Math::Vector3& cfp, K_Math::Vector3& chp):
			baseShape(bs), receiveShape(rs), visibilityShape(vs), attackAreaShape(aas), checkShape(cs),
			receivePos(rp), visibilityPos(vp), attackAreaPos(aap), checkFootPos(cfp), checkHeadPos(chp){}
	};

private:
	EnemyMoveSet*			emSet;			//動作まとめ
	ParameterData			paramData;		//各種情報
	CollisionData			collisionData;	//コリジョン情報
	K_Graphics::Texture*	textureData;	//テクスチャ情報

public:
	//コンストラクタ
	EnemyType(const ParameterData& param, const CollisionData& col);
	//デストラクタ
	~EnemyType();

	//エネミーの動作設定を取得
	EnemyMoveSet* GetEnemyMoveSet();
	//画像名を取得
	const std::string& GetTextureName();
	//体力上限を取得
	const int GetMaxLife();
	//プレイヤーに与えるダメージ量を取得
	const int GetHitDamage();
	//1フレームの移動速度を取得
	const float GetMoveSpeed();
	//ジャンプ力を取得
	const float GetJumpPower();
	//重力を利用するか否かを取得
	const bool GetIsUseGravity();
	//テクスチャを取得
	K_Graphics::Texture* GetTexture();

	//地形用コリジョンデータの生成と取得
	K_Physics::CollisionData* CreateAndGetBaseCollisionData();
	//被ダメ用コリジョンデータの生成と取得
	K_Physics::CollisionData* CreateAndGetRecieveDamageCollisionData();
	//被カメラガン用コリジョンデータの生成と取得
	K_Physics::CollisionData* CreateAndGetRecieveCameraCollisionData();
	//視界用コリジョンデータの生成と取得
	K_Physics::CollisionData* CreateAndGetFieldofviewCollisionData();
	//攻撃動作遷移用コリジョンの生成と取得
	K_Physics::CollisionData* CreateAndGetAttackAreaCollisionData();
	//足元用コリジョンの生成と取得
	K_Physics::CollisionData* CreateAndGetCheckFootCollisionData();
	//頭上用コリジョンの生成と取得
	K_Physics::CollisionData* CreateAndGetCheckHeadCollisionData();
};
