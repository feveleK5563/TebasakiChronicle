#pragma once
#include <vector>
#include "SystemClass.h"
#include "../../../BaseClass/Status/Status.h"
#include "../../../BaseClass/Move.h"
#include "../../../BaseClass/Collision/CollisionManager.h"
#include "../../TemporaryCollision/TemporaryCollisionManager.h"

//����̊��N���X
class EnemyMove
{
public:
	EnemyMove(){}
	virtual ~EnemyMove() {}
	virtual void FirstMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move) = 0;
	virtual void EMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move) = 0;
};

//-----------------------------------------------
//0�F�������Ȃ�
class EMove_NoMotion : public EnemyMove
{
public:
	void FirstMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void EMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//1�F�����Ă�������Ɉړ�����
class EMove_Movement : public EnemyMove
{
public:
	void FirstMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void EMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//2�F�W�����v����
class EMove_Jump : public EnemyMove
{
public:
	void FirstMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void EMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//3�F�O���ɍU������
class EMove_FrontAttack : public EnemyMove
{
private:
	void CreateAttackCollision();

public:
	void FirstMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void EMove(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};