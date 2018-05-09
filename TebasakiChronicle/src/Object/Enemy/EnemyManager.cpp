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
	enemy.emplace_back(new Enemy(cpyet, setPos, direction));
}

//-----------------------------------------------------------------------------
//全ての敵を更新する
void EnemyManager::UpdateAllEnemy()
{
	for (auto it = enemy.begin(); it != enemy.end();)
	{
		if ((*it)->Update())	//死亡したら削除
		{
			delete *(it);
			it = enemy.erase(it);
		}
		else
		{
			++it;
		}
	}
	enemy.shrink_to_fit();
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

//-----------------------------------------------------------------------------
//全ての敵を削除(解放)する
void EnemyManager::DeleteAllEnemy()
{
	for (auto it : enemy)
		delete it;

	enemy.clear();
	enemy.shrink_to_fit();
}