#pragma once
#include <iostream>
#include <fstream>
#include "../Object/Enemy/EnemyType/EnemyTypeManager.h"

class EnemyLoader
{
private:
	void LoadEnemyParamaterData(std::ifstream& ifs, EnemyTypeManager::EnemyData* ed);	//����1
	void LoadEnemyCollisionData(std::ifstream& ifs, EnemyTypeManager::EnemyData* ed);	//����2
	void LoadEnemyMoveData(std::ifstream& ifs, EnemyTypeManager::EnemyData* ed);		//����3

public:
	EnemyLoader();
	~EnemyLoader();

	//�G���̓ǂݍ��݂��s���A���̏��܂Ƃ߂�Ԃ�
	EnemyTypeManager::EnemyData* LoadEnemyData(const std::string& enemyDataPath);
};
