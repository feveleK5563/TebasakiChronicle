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
void EnemyManager::CreateEnemy(EnemyType* cpyet, const K_Math::Vector3& setPos)
{
	enemy.emplace_back(new Enemy(cpyet, setPos));
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
void EnemyManager::DrawAllEnemy()
{
	for (auto it : enemy)
	{
		it->Draw();
	}
}