#pragma once
#include <vector>
#include "SystemClass.h"
#include "../../../BaseClass/Status/Status.h"
#include "../../../BaseClass/Move.h"
#include "../../../BaseClass/Collision/CollisionManager.h"
#include "../../TemporaryCollision/TemporaryCollisionManager.h"

//動作の基底クラス
class EnemyMove
{
public:
	EnemyMove(){}
	virtual ~EnemyMove() {}
	virtual void FirstMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move) = 0;
	virtual void EMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move) = 0;
};

//-----------------------------------------------
//何もしない
class EMove_NoMotion : public EnemyMove
{
public:
	void FirstMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void EMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//向いている方向に移動する
class EMove_Movement : public EnemyMove
{
public:
	void FirstMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void EMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//ジャンプする
class EMove_Jump : public EnemyMove
{
public:
	void FirstMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void EMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//前方に攻撃する
class EMove_FrontAttack : public EnemyMove
{
private:
	void CreateAttackCollision();

public:
	void FirstMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void EMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};