#pragma once
#include "Enemy.h"

//�{�X�p�̃N���X
class BossEnemy
{
private:
	bool isBossActive;
	std::vector<Enemy*> bossEnemy;

public:
	BossEnemy();
	~BossEnemy();

	//�{�X�G����̍쐬����
	void CreateBossEnemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction);

	//�{�X���X�V����
	void Update();

	//�{�X��`�悷��
	void Render();

	//�S�Ẵ{�X�̑��݂�L���ɂ���
	void AllActiveBoss();

	//�{�X�����݂��Ă��邩�S�Ẵ{�X�����S��Ԃ��ۂ���Ԃ�
	//�{�X�����݂��Ă��Ȃ��ꍇ��false��Ԃ�
	bool GetIsDeadBoss();

	//�S�Ẵ{�X���������
	void DeleteBoss();

	//0�Ԗڂ̃{�X�̃f�[�^���擾����
	const K_Math::Vector3& GetBossPos();
};