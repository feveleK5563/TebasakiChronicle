#include "EnemyManager.h"

//�R���X�g���N�^
EnemyManager::EnemyManager():
	isDeadBoss(false){}

//�f�X�g���N�^
EnemyManager::~EnemyManager()
{
	for (auto it : enemy)
		delete it;
}

//-----------------------------------------------------------------------------
//�G����̍쐬����
void EnemyManager::CreateEnemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction)
{
	int indexNum = (int)enemy.size();
	enemy.emplace_back(new Enemy(cpyet, setPos, direction, indexNum));
}
//-----------------------------------------------------------------------------
//�{�X�G����̍쐬����
void EnemyManager::CreateBossEnemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction)
{
	int indexNum = (int)enemy.size();
	bossEnemy.emplace_back(new Enemy(cpyet, setPos, direction, indexNum));
}

//-----------------------------------------------------------------------------
//�S�Ă̓G���X�V����
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
//�S�Ă̓G��`�悷��
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
//�{�X�����݂��Ă��邩�S�Ẵ{�X�����S��Ԃ��ۂ���Ԃ�
//�{�X�����݂��Ă��Ȃ��ꍇ��false��Ԃ�
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
//�S�Ă̓G���폜(���)����
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