#pragma once
#include "EnemyType.h"
#include "../../../Helper.h"

class EnemyTypeManager
{
public:
	struct EnemyData	//�G���̂܂Ƃ�
	{
		EnemyType::ParameterData* paramater;
		EnemyType::CollisionData* collision;
		std::vector<EnemyMovePattern::MoveSetUpData*> movesetupdata;

		EnemyData(){}

		~EnemyData()
		{
			Memory::SafeDelete(paramater);
			Memory::SafeDelete(collision);

			for (auto it : movesetupdata)
				Memory::SafeDelete(it);
		}
	};

public:
	std::vector<EnemyType*> eType;

	//�R���X�g���N�^
	EnemyTypeManager();
	//�f�X�g���N�^
	~EnemyTypeManager();

	//�t�@�C����ǂݍ���œG�̃f�[�^�����
	//�����F�ǂݍ��ރt�@�C���ւ̃p�X(string)
	void CreateEnemyData(EnemyData* ed);

	//�w��ԍ��̓G�f�[�^�̃A�h���X�l��Ԃ�
	EnemyType* GetEnemyTypeData(int enemyNum);
};