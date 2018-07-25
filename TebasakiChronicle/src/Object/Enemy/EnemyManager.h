#pragma once
#include "Enemy.h"
#include "BossEnemy.h"
#include "../../Loader/EnemyLoader.h"
#include "EnemyType/EnemyTypeManager.h"

class EnemyManager
{
private:
	std::vector<Enemy*> enemy;
	BossEnemy			bossEnemy;
	EnemyLoader			enemyLoader;
	EnemyTypeManager	enemyTypeManager;

public:
	~EnemyManager();

	//敵を一体作成する
	void CreateEnemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction);
	//ボス敵を一体作成する
	void CreateBossEnemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction);

	//敵の配置情報を読み込み、敵を作成する
	void LayoutEnemy(const std::string& enemyLayoutPath);

	//作成した全ての敵を更新する
	void UpdateAllEnemy();
	//全ての敵を描画する
	void RenderAllEnemy();

	//全てのボスの存在を有効にする
	void AllActiveBoss(bool activeBoss);
	//ボスが存在しているかつ全てのボスが死亡状態か否かを返す
	//ボスが存在していない場合はfalseを返す
	bool GetIsDeadBoss();

	//全ての敵を削除(解放)する
	void DeleteAllEnemy();

	//ボスの座標を取得する
	const K_Math::Vector3& GetBossPos();
};