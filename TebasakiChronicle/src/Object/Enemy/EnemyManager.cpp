#include "EnemyManager.h"

//�R���X�g���N�^
EnemyManager::EnemyManager()
{
	//�G�t�F�N�g�쐬
	Effect::CreateEffectData(	//�{�X��1, �U�艺�낵�p
		EffectName::BossKnockEffect,
		"BossButtleEffect1",
		"data/image/Enemy/BossA.png",
		new AnimationCharaChip(K_Math::Box2D(0, 544, 128, 128), 3, 5.f, false)
	);
	Effect::CreateEffectData(	//�{�X��1, �r�[���p1
		EffectName::BossBeamEffect1,
		"BossButtleEffect1",
		"data/image/Enemy/BossA.png",
		new AnimationCharaChip(K_Math::Box2D(0, 448, 64, 96), 4, 3.f, false)
	);
	Effect::CreateEffectData(	//�{�X��1, �r�[���p2
		EffectName::BossBeamEffect2,
		"BossButtleEffect1",
		"data/image/Enemy/BossA.png",
		new AnimationCharaChip(K_Math::Box2D(256, 448, 64, 96), 4, 3.f, false)
	);
}

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
	bossEnemy.CreateBossEnemy(cpyet, setPos, direction);
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
			enemyTypeManager.CreateEnemyData(enemyLoader.LoadEnemyData("data/EnemyData/" + enemyDataPath));
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
			bool isBoss;
			K_Math::Vector3 pos;

			ifs >> enemyId >> isBoss >> direction >> pos.x >> pos.y >> pos.z;

			if (isBoss)
			{
				CreateBossEnemy(
					enemyTypeManager.GetEnemyTypeData(enemyId),
					pos,
					direction == 0 ? Status::Direction::Left : Status::Direction::Right
				);
			}
			else
			{
				CreateEnemy(
					enemyTypeManager.GetEnemyTypeData(enemyId),
					pos,
					direction == 0 ? Status::Direction::Left : Status::Direction::Right
				);
			}
		}
	}
}

//-----------------------------------------------------------------------------
//�S�Ă̓G���X�V����
void EnemyManager::UpdateAllEnemy()
{
	for (auto& it : enemy)
	{
		it->RecieveCollisionOperation();
		it->Update();
	}

	bossEnemy.Update();
}

//-----------------------------------------------------------------------------
//�S�Ă̓G��`�悷��
void EnemyManager::RenderAllEnemy()
{
	for (auto& it : enemy)
	{
		it->Render();
	}

	bossEnemy.Render();
}

//-----------------------------------------------------------------------------
//�S�Ẵ{�X�̑��݂�L���ɂ���
void EnemyManager::AllActiveBoss(bool activeBoss)
{
	if (!activeBoss)
		return;

	bossEnemy.AllActiveBoss();
}
//-----------------------------------------------------------------------------
//�{�X�����݂��Ă��邩�S�Ẵ{�X�����S��Ԃ��ۂ���Ԃ�
//�{�X�����݂��Ă��Ȃ��ꍇ��false��Ԃ�
bool EnemyManager::GetIsDeadBoss()
{
	return bossEnemy.GetIsDeadBoss();
}

//-----------------------------------------------------------------------------
//�S�Ă̓G���폜(���)����
void EnemyManager::DeleteAllEnemy()
{
	for (auto& it : enemy)
		delete it;
	enemy.clear();
	enemy.shrink_to_fit();

	bossEnemy.DeleteBoss();
}

//-----------------------------------------------------------------------------
//�{�X�̍��W���擾����
const K_Math::Vector3& EnemyManager::GetBossPos() const
{
	return bossEnemy.GetBossPos();
}

//-----------------------------------------------------------------------------
//�{�X�̍ő�̗͂��擾����
const int& EnemyManager::GetBossLife() const
{
	return bossEnemy.GetBossLife();
}