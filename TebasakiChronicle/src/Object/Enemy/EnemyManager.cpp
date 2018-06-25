#include "EnemyManager.h"

//コンストラクタ
EnemyManager::EnemyManager():
	isDeadBoss(false){}

//デストラクタ
EnemyManager::~EnemyManager()
{
	for (auto it : enemy)
		delete it;
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
	bossEnemy.emplace_back(new Enemy(cpyet, setPos, direction, indexNum));
}

//-----------------------------------------------------------------------------
//全ての敵を更新する
void EnemyManager::UpdateAllEnemy()
{
	for (auto& it : enemy)
	{
		it->Update();
	}

	isDeadBoss = true;
	for (auto& it : bossEnemy)
	{
		it->Update();
		if (!it->IsDead())
		{
			isDeadBoss = false;
		}
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
//ボスが存在しているかつ全てのボスが死亡状態か否かを返す
//ボスが存在していない場合はfalseを返す
bool EnemyManager::GetIsDeadBoss()
{
	if (bossEnemy.size() > 0)
	{
		return isDeadBoss;
	}
	else
	{
		return false;
	}
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
	enemy.shrink_to_fit();
}