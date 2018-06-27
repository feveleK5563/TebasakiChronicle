#pragma once
#include "Enemy.h"

class EnemyManager
{
private:
	std::vector<Enemy*> enemy;
	std::vector<Enemy*> bossEnemy;

public:
	EnemyManager();
	~EnemyManager();

	//敵を一体作成する
	void CreateEnemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction);
	//ボス敵を一体作成する
	void CreateBossEnemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction);

	//作成した全ての敵を更新する
	void UpdateAllEnemy();
	//全ての敵を描画する
	void RenderAllEnemy();

	//全てのボスの存在を有効にする
	void AllActiveBoss();
	//ボスが存在しているかつ全てのボスが死亡状態か否かを返す
	//ボスが存在していない場合はfalseを返す
	bool GetIsDeadBoss();

	//全ての敵を削除(解放)する
	void DeleteAllEnemy();
};