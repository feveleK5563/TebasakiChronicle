#include "EnemyManager.h"

//コンストラクタ
EnemyManager::EnemyManager() {}

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
//全ての敵を更新する
void EnemyManager::UpdateAllEnemy()
{
	for (auto it : enemy)
	{
		it->Update();
	}
}

//-----------------------------------------------------------------------------
//全ての敵を描画する
void EnemyManager::RenderAllEnemy()
{
	for (auto it : enemy)
	{
		it->Render();
	}
}

//-----------------------------------------------------------------------------
//全ての敵を削除(解放)する
void EnemyManager::DeleteAllEnemy()
{
	for (auto it : enemy)
		delete it;

	enemy.clear();
	enemy.shrink_to_fit();
}