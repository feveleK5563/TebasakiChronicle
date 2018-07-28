#define NOMINMAX
#include <algorithm>
#include "BossEnemy.h"

BossEnemy::BossEnemy():
	isBossActive(false)
{

}

BossEnemy::~BossEnemy()
{
	DeleteBoss();
}

//ボス敵を一体作成する
void BossEnemy::CreateBossEnemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction)
{
	int indexNum = (int)bossEnemy.size();
	bossEnemy.emplace_back(new Enemy(cpyet, setPos, direction, indexNum, true));
}

//ボスを更新する
void BossEnemy::Update()
{
	if (!isBossActive)
		return;

	//ライフとダメージを受けたか否かを共有する
	int shareLife = bossEnemy[0]->GetLife();
	bool isTakeDamage = false;

	for (size_t i = 0; i < bossEnemy.size(); ++i)
	{
		isTakeDamage = isTakeDamage || bossEnemy[i]->RecieveCollisionOperation();
		shareLife = std::min(shareLife, bossEnemy[i]->GetLife());
	}

	for (size_t i = 0; i < bossEnemy.size(); ++i)
	{
		bossEnemy[i]->SetLife(shareLife, isTakeDamage);
		bossEnemy[i]->Update();
	}
}

//ボスを描画する
void BossEnemy::Render()
{
	for (auto& it : bossEnemy)
	{
		it->Render();
	}
}

//全てのボスの存在を有効にする
void BossEnemy::AllActiveBoss()
{
	isBossActive = true;
	for (auto& it : bossEnemy)
	{
		it->ResetAndActiveEnemy();
	}
}

//ボスが存在しているかつ全てのボスが死亡状態か否かを返す
//ボスが存在していない場合はfalseを返す
bool BossEnemy::GetIsDeadBoss()
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

//全てのボスを解放する
void BossEnemy::DeleteBoss()
{
	for (auto& it : bossEnemy)
		delete it;
	bossEnemy.clear();
	bossEnemy.shrink_to_fit();
}

//0番目のボスの座標を取得する
const K_Math::Vector3& BossEnemy::GetBossPos() const
{
	return bossEnemy[0]->GetPos();
}

//0番目のボスの体力を取得する
const int& BossEnemy::GetBossLife() const
{
	return bossEnemy[0]->GetLife();
}