#pragma once
#include "Enemy.h"
#include "BossEnemy.h"
#include "../../Loader/EnemyLoader.h"
#include "EnemyType/EnemyTypeManager.h"

class EnemyManager
{
private:
	std::vector<Enemy*> enemy;
	BossEnemy			bossEnemy;
	EnemyLoader			enemyLoader;
	EnemyTypeManager	enemyTypeManager;

public:
	~EnemyManager();

	//�G����̍쐬����
	void CreateEnemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction);
	//�{�X�G����̍쐬����
	void CreateBossEnemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction);

	//�G�̔z�u����ǂݍ��݁A�G���쐬����
	void LayoutEnemy(const std::string& enemyLayoutPath);

	//�쐬�����S�Ă̓G���X�V����
	void UpdateAllEnemy();
	//�S�Ă̓G��`�悷��
	void RenderAllEnemy();

	//�S�Ẵ{�X�̑��݂�L���ɂ���
	void AllActiveBoss(bool activeBoss);
	//�{�X�����݂��Ă��邩�S�Ẵ{�X�����S��Ԃ��ۂ���Ԃ�
	//�{�X�����݂��Ă��Ȃ��ꍇ��false��Ԃ�
	bool GetIsDeadBoss();

	//�S�Ă̓G���폜(���)����
	void DeleteAllEnemy();

	//�{�X�̍��W���擾����
	const K_Math::Vector3& GetBossPos();
};