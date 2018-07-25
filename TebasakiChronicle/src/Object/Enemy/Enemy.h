#pragma once
#include "EnemyType/EnemyType.h"
#include "../GameObject.h"

class Enemy
{
private:
	EnemyMoveSet*	ems;			//動作(delete禁止)
	TimeCount		timeCnt;		//時間計測
	int				behaviorId;		//現在の敵から読み取れる動作番号
	bool			isBoss;			//こいつがボスか否か

	K_Math::Vector3	initialPos;		//初期位置
	bool	isUseGravity;			//重力を使用するか否か

	bool	isTakeDamage;			//ダメージを受けたか否か

	static const int subCollisionNum = 6;			//サブコリジョンの数
	int		collisionGiveMask[subCollisionNum];		//サブコリジョンの与マスク
	int		collisionMyselfMask[subCollisionNum];	//サブコリジョンの受マスク

	int					nowMoveOrder;		//現在の動作順番
	int					nowPatternOrder;	//現在の動作パターン番号
	int					beforeMoveOrder;	//前の動作順番
	int					beforePatternOrder;	//前の動作パターン番号

	CollisionManager			collisionManager;		//コリジョンの管理
	TemporaryCollisionManager	tempCollisionManager;	//一時的に生成するコリジョンクラス
	GameObject					gameObject;				//ゲームオブジェクト
	K_Math::Vector3				standerdPos;			//基準となる座標		

	//敵に割り当てられているサブコリジョンの名前一覧
	enum EnemyCollisionName
	{
		RecieveDamage,
		Visibility,
		AttackArea,
		CheckFoot,
		CheckHead,
		RecieveCameraGun,
	};

public:
	//スキル番号と現在のテクスチャ名、キャラチップ番号を格納
	//これをカメラ受け用コリジョンのタグに指定する
	struct SkillAndCharaChip
	{
		K_Math::Vector3*		pos;
		const std::string*		textureName;
		int*					behaviorId;
		AnimationCharaChip*		nowCharaChip;
	};
	SkillAndCharaChip* skillAndChip;

	//コンストラクタ
	Enemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction, const int indexNum, bool isBoss = false);
	//デストラクタ
	~Enemy();

	//敵情報を設定
	void SetEnemyType(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction, const int indexNum);

	//無効状態にする
	void SetNonEnemy();

	//状態を全て初期状態に戻す
	void ResetAndActiveEnemy();

	//更新
	void Update();

	//死亡している否かを返す
	bool IsDead();

	//画面内判定
	bool DecisionInScreen();

	//コリジョンとの接触処理
	//ダメージを受けたらtrueを返す
	bool RecieveCollisionOperation();

	//タグに情報を格納
	//体力が0になったらtrueを返す
	void SetTugData();

	//アニメーションの更新
	void AnimationUpdate();
	
	//描画
	void Render();


	//--------------------------------------------------------

	//座標をオフセットする
	void OffSetPos(const K_Math::Vector3& pos);
	//座標を取得する
	const K_Math::Vector3& GetPos();

	//時間を設定する
	void SetTime(int time);
	//時間を取得する
	int GetTime();

	//体力を設定する
	void SetLife(int life, bool isTakeDamage);
	//体力を取得する
	const int& GetLife();
	//ダメージを受けたか否かを取得する
	const bool& GetIsTakeDamage();
};
