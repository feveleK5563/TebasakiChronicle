#include "EnemyManager.h"

//コンストラクタ
EnemyManager::EnemyManager() {}

//デストラクタ
EnemyManager::~EnemyManager()
{
	DeleteAllEnemy();
}

//-----------------------------------------------------------------------------
//敵を一体作成する
void EnemyManager::CreateEnemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction)
{
	int indexNum = (int)enemy.size();
	enemy.emplace_back(new Enemy(cpyet, setPos, direction, indexNum));
}
//-----------------------------------------------------------------------------
//ボス敵を一体作成する
void EnemyManager::CreateBossEnemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction)
{
	int indexNum = (int)enemy.size();
	bossEnemy.emplace_back(new Enemy(cpyet, setPos, direction, indexNum, true));
}

//-----------------------------------------------------------------------------
//全ての敵を更新する
void EnemyManager::UpdateAllEnemy()
{
	for (auto& it : enemy)
	{
		it->Update();
	}

	for (auto& it : bossEnemy)
	{
		it->Update();
	}
}

//-----------------------------------------------------------------------------
//全ての敵を描画する
void EnemyManager::RenderAllEnemy()
{
	for (auto& it : enemy)
	{
		it->Render();
	}

	for (auto& it : bossEnemy)
	{
		it->Render();
	}
}

//-----------------------------------------------------------------------------
//全てのボスの存在を有効にする
void EnemyManager::AllActiveBoss()
{
	for (auto& it : bossEnemy)
	{
		it->ResetAndActiveEnemy();
	}
}
//-----------------------------------------------------------------------------
//ボスが存在しているかつ全てのボスが死亡状態か否かを返す
//ボスが存在していない場合はfalseを返す
bool EnemyManager::GetIsDeadBoss()
{
	if (bossEnemy.size() <= 0)
		return false;

	for (auto& it : bossEnemy)
	{
		if (!it->IsDead())
			return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
//全ての敵を削除(解放)する
void EnemyManager::DeleteAllEnemy()
{
	for (auto& it : enemy)
		delete it;
	enemy.clear();
	enemy.shrink_to_fit();

	for (auto& it : bossEnemy)
		delete it;
	bossEnemy.clear();
	bossEnemy.shrink_to_fit();
}