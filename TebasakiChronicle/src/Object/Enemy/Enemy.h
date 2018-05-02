#pragma once
#include "EnemyType.h"
#include "EnemyController.h"

//以下のincludeはGameObjectで代替する
#include "../../BaseClass/ImageManager/ImageManager.h"

class Enemy
{
	EnemyController*	eController;		//動作管理くん
	int					nowMoveOrder;		//現在の動作順番
	int					nowPatternOrder;	//現在の動作パターン番号
	int					beforeMoveOrder;	//前の動作順番
	int					beforePatternOrder;	//前の動作パターン番号

	//以下のメンバ変数はGameObjectやMoveクラスとかが持ってるものだと思う
	int							life;
	K_Math::Vector3				pos;
	K_Math::Vector3				angle;
	K_Math::Vector3				scale;
	K_Math::Vector3				moveVec;
	ImageManager*				imgManager;
	
	K_Physics::CollisionData*	cData;		//プレイヤー接触用コリジョン情報
											//カメラ撮影用コリジョン情報(形状は接触用と同じ)
											//地形判定用コリジョン情報(形状は接触用と同じ)
											//頭上判定用コリジョン情報(接触用の真上)
											//足元判定用コリジョン情報(接触用の真下)
											//視界判定用コリジョン情報
											//攻撃動作遷移用コリジョン情報(アタックエリア)

public:
	//スキル番号と現在のテクスチャ名、キャラチップ番号を格納
	//これをカメラ受け用コリジョンのタグに指定する
	struct SkillAndCharaChip
	{
		int					skillId;
		std::string*		textureName;
		AnimationCharaChip* nowCharaChip;
	};
	SkillAndCharaChip skillAndChip;

	//コンストラクタ
	Enemy(EnemyType* cpyet, const K_Math::Vector3& setPos);
	//デストラクタ
	~Enemy();

	//敵情報を設定
	void SetEnemyType(EnemyType* cpyet, const K_Math::Vector3& setPos);

	//スキル情報を格納
	void SetSkillData();

	//更新
	void Update();

	//描画
	void Draw();
};
