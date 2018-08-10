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

//�{�X�G����̍쐬����
void BossEnemy::CreateBossEnemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction)
{
	int indexNum = (int)bossEnemy.size();
	if (bossEnemy.size() > 0)
	{
		bossEnemy.emplace_back(new Enemy(cpyet, K_Math::Vector3(0.f, 0.f, 0.f), direction, indexNum, true));
		bossEnemy.back()->SetRelativePos(setPos);
	}
	else
	{
		bossEnemy.emplace_back(new Enemy(cpyet, setPos, direction, indexNum, true));
	}
}

//�{�X���X�V����
void BossEnemy::Update()
{
	if (!isBossActive)
		return;

	//���C�t�ƃ_���[�W���󂯂����ۂ������L����
	int shareLife = bossEnemy[0]->GetLife();
	bool isTakeDamage = false;

	//�_���[�W��������L
	for (size_t i = 0; i < bossEnemy.size(); ++i)
	{
		isTakeDamage = isTakeDamage || bossEnemy[i]->RecieveCollisionOperation();
		shareLife = std::min(shareLife, bossEnemy[i]->GetLife());
	}

	//�̗͂����L
	for (size_t i = 0; i < bossEnemy.size(); ++i)
	{
		bossEnemy[i]->SetLife(shareLife, isTakeDamage);
		bossEnemy[i]->Update();
	}

	K_Math::Vector3 sharePos = bossEnemy[0]->GetPos();
	//���W�����L
	for (size_t i = 1; i < bossEnemy.size(); ++i)
	{
		bossEnemy[i]->OffsetPos(sharePos);
	}
}

//�{�X��`�悷��
void BossEnemy::Render()
{
	for (auto& it : bossEnemy)
	{
		it->Render();
	}
}

//�S�Ẵ{�X�̑��݂�L���ɂ���
void BossEnemy::AllActiveBoss()
{
	isBossActive = true;
	for (auto& it : bossEnemy)
	{
		it->ResetAndActiveEnemy();
	}
}

//�{�X�����݂��Ă��邩�S�Ẵ{�X�����S��Ԃ��ۂ���Ԃ�
//�{�X�����݂��Ă��Ȃ��ꍇ��false��Ԃ�
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

//�S�Ẵ{�X���������
void BossEnemy::DeleteBoss()
{
	for (auto& it : bossEnemy)
		delete it;
	bossEnemy.clear();
	bossEnemy.shrink_to_fit();
}

//0�Ԗڂ̃{�X�̍��W���擾����
const K_Math::Vector3& BossEnemy::GetBossPos() const
{
	return bossEnemy[0]->GetPos();
}

//0�Ԗڂ̃{�X�̗̑͂��擾����
const int& BossEnemy::GetBossLife() const
{
	return bossEnemy[0]->GetLife();
}