#pragma once
#include "Enemy.h"

//ボス用のクラス
class BossEnemy
{
private:
	bool isBossActive;
	std::vector<Enemy*> bossEnemy;

public:
	BossEnemy();
	~BossEnemy();

	//ボス敵を一体作成する
	void CreateBossEnemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction);

	//ボスを更新する
	void Update();

	//ボスを描画する
	void Render();

	//全てのボスの存在を有効にする
	void AllActiveBoss();

	//ボスが存在しているかつ全てのボスが死亡状態か否かを返す
	//ボスが存在していない場合はfalseを返す
	bool GetIsDeadBoss();

	//全てのボスを解放する
	void DeleteBoss();

	//0番目のボスのデータを取得する
	const K_Math::Vector3& GetBossPos();
};