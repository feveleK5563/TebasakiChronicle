#pragma once
#include <iostream>
#include <fstream>
#include "../Object/Enemy/EnemyType/EnemyTypeManager.h"

class EnemyLoader
{
private:
	void LoadEnemyParamaterData(std::ifstream& ifs, EnemyTypeManager::EnemyData* ed);	//順番1
	void LoadEnemyCollisionData(std::ifstream& ifs, EnemyTypeManager::EnemyData* ed);	//順番2
	void LoadEnemyMoveData(std::ifstream& ifs, EnemyTypeManager::EnemyData* ed);		//順番3

public:
	EnemyLoader();
	~EnemyLoader();

	//敵情報の読み込みを行い、その情報まとめを返す
	EnemyTypeManager::EnemyData* LoadEnemyData(const std::string& enemyDataPath);
};
