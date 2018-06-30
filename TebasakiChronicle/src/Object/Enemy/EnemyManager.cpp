#include "EnemyManager.h"

//�R���X�g���N�^
EnemyManager::EnemyManager() {}

//�f�X�g���N�^
EnemyManager::~EnemyManager()
{
	DeleteAllEnemy();
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
	int indexNum = (int)bossEnemy.size();
	bossEnemy.emplace_back(new Enemy(cpyet, setPos, direction, indexNum, true));
}

//-----------------------------------------------------------------------------
//�G�̔z�u����ǂݍ��݁A�G���쐬����
void EnemyManager::LayoutEnemy(const std::string& enemyLayoutPath)
{
	std::ifstream ifs(enemyLayoutPath);
	if (!ifs)
	{
		return;
	}

	//�S�G�f�[�^�̓ǂݍ���
	{
		int enemyTypeNum;
		ifs >> enemyTypeNum;
		std::string enemyDataPath;
		for (int i = 0; i < enemyTypeNum; ++i)
		{
			ifs >> enemyDataPath;
			enemyTypeManager.CreateEnemyData(enemyLoader.LoadEnemyData(enemyDataPath));
		}
	}

	//�G�̔z�u���̓ǂݍ���
	{
		int enemyNum;
		ifs >> enemyNum;
		for (int i = 0; i < enemyNum; ++i)
		{
			int enemyId;
			int direction;
			K_Math::Vector3 pos;

			ifs >> enemyId >> direction >> pos.x >> pos.y >> pos.z;

			CreateEnemy(
				enemyTypeManager.GetEnemyTypeData(enemyId),
				pos,
				direction == 0 ? Status::Direction::Left : Status::Direction::Right
			);
		}
	}
}

//-----------------------------------------------------------------------------
//�S�Ă̓G���X�V����
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
//�S�Ẵ{�X�̑��݂�L���ɂ���
void EnemyManager::AllActiveBoss()
{
	for (auto& it : bossEnemy)
	{
		it->ResetAndActiveEnemy();
	}
}
//-----------------------------------------------------------------------------
//�{�X�����݂��Ă��邩�S�Ẵ{�X�����S��Ԃ��ۂ���Ԃ�
//�{�X�����݂��Ă��Ȃ��ꍇ��false��Ԃ�
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
	bossEnemy.shrink_to_fit();
}