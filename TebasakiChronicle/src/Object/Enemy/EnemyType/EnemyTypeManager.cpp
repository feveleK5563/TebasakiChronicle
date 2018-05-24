#include "EnemyTypeManager.h"

//�R���X�g���N�^
EnemyTypeManager::EnemyTypeManager() {}

//�f�X�g���N�^
EnemyTypeManager::~EnemyTypeManager()
{
	for (auto it : eType)
		delete it;
}

//-----------------------------------------------------------------------------
//�t�@�C����ǂݍ���œG�̃f�[�^�����
//�����F�ǂݍ��ރt�@�C���ւ̃p�X(string)
void EnemyTypeManager::CreateEnemyData(EnemyData* ed)
{
	if (ed == nullptr)
		return;

	eType.emplace_back(new EnemyType(*(ed->paramater), *(ed->collision)));	//�p�����[�^�ƃR���W�����̔z�u��ݒ�

	for (auto it : ed->movesetupdata)
	{
		eType.back()->GetEnemyMoveSet()->CreateMotionPattern(*it);	//����p�^�[������ݒ�
	}

	delete ed;
}

//-----------------------------------------------------------------------------
//�w��ԍ��̓G�f�[�^�̃A�h���X�l��Ԃ�
EnemyType* EnemyTypeManager::GetEnemyTypeData(int enemyNum)
{
	if (enemyNum < (int)eType.size())
	{
		return eType[enemyNum];
	}
	return nullptr;
}