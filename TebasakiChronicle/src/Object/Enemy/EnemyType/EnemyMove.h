#pragma once
#include <vector>
#include "SystemClass.h"
#include "../../../BaseClass/Status/Status.h"
#include "../../../BaseClass/Move.h"
#include "../../../BaseClass/Collision/CollisionManager.h"

//動作の基底クラス
class EnemyMove
{
public:
	EnemyMove(){}
	virtual ~EnemyMove() {}
	virtual void EMove(CollisionManager& cmanager, Status& status, Move& move) = 0;
};

//-----------------------------------------------
//何もしない
class EMove_NoMotion : public EnemyMove
{
public:
	void EMove(CollisionManager& cmanager, Status& status, Move& move);
};

//-----------------------------------------------
//向いている方向に移動する
class EMove_Movement : public EnemyMove
{
public:
	void EMove(CollisionManager& cmanager, Status& status, Move& move);
};

//-----------------------------------------------
//ジャンプする
class EMove_Jump : public EnemyMove
{
public:
	void EMove(CollisionManager& cmanager, Status& status, Move& move);
};