#pragma once
#include "EnemyType/EnemyType.h"
#include "EnemyController.h"
#include "../../BaseClass/Collision/CollisionManager.h"

//以下のincludeはGameObjectで代替する
#include "../GameObject.h"

class Enemy
{
	EnemyController*	eController;		//動作管理
	int					nowMoveOrder;		//現在の動作順番
	int					nowPatternOrder;	//現在の動作パターン番号
	int					beforeMoveOrder;	//前の動作順番
	int					beforePatternOrder;	//前の動作パターン番号

	CollisionManager	collisionManager;	//コリジョンの管理
	GameObject			gameObject;			//ゲームオブジェクト

public:
	//スキル番号と現在のテクスチャ名、キャラチップ番号を格納
	//これをカメラ受け用コリジョンのタグに指定する
	struct SkillAndCharaChip
	{
		K_Math::Vector3*	pos;
		std::string*		textureName;
		int*				skillId;
		AnimationCharaChip* nowCharaChip;
	};
	SkillAndCharaChip skillAndChip;

	//コンストラクタ
	Enemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction);
	//デストラクタ
	~Enemy();

	//敵情報を設定
	void SetEnemyType(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction);

	//更新(死亡したか否かを返す)
	bool Update();

	//スキル情報を格納
	void SetTugData();

	//描画、アニメーションの更新
	void AnimationUpdate();
	
	//描画
	void Draw();
};
