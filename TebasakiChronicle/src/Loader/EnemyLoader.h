#pragma once
#include <iostream>
#include <fstream>
#include "../Object/Enemy/EnemyType/EnemyTypeManager.h"

class EnemyLoader
{
private:
	void LoadEnemyParamaterData(std::ifstream& ifs, EnemyTypeManager::EnemyData* ed);	//‡”Ô1
	void LoadEnemyCollisionData(std::ifstream& ifs, EnemyTypeManager::EnemyData* ed);	//‡”Ô2
	void LoadEnemyMoveData(std::ifstream& ifs, EnemyTypeManager::EnemyData* ed);		//‡”Ô3

public:
	EnemyLoader();
	~EnemyLoader();

	//“Gî•ñ‚Ì“Ç‚İ‚İ‚ğs‚¢A‚»‚Ìî•ñ‚Ü‚Æ‚ß‚ğ•Ô‚·
	EnemyTypeManager::EnemyData* LoadEnemyData(const std::string& enemyDataPath);
};
