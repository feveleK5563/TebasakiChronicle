#pragma once
#include "Enemy.h"

class EnemyManager
{
private:
	std::vector<Enemy*> enemy;

public:
	EnemyManager();
	~EnemyManager();

	//“G‚ğˆê‘Ìì¬‚·‚é
	void CreateEnemy(EnemyType* cpyet, const K_Math::Vector3& setPos, const Status::Direction& direction);
	//ì¬‚µ‚½‘S‚Ä‚Ì“G‚ğXV‚·‚é
	void UpdateAllEnemy();
	//‘S‚Ä‚Ì“G‚ğ•`‰æ‚·‚é
	void DrawAllEnemy();

	//‘S‚Ä‚Ì“G‚ğíœ(‰ğ•ú)‚·‚é
	void DeleteAllEnemy();
};