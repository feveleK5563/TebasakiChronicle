#pragma once
#include <vector>
#include "SystemClass.h"
#include "../../../BaseClass/Status/Status.h"
#include "../../../BaseClass/Move.h"
#include "../../../BaseClass/Collision/CollisionManager.h"
#include "../../TemporaryCollision/TemporaryCollisionManager.h"
#include "../../../TimeCount.h"

//-----------------------------------------------------------------------------
//����̒��ۃN���X
class CharacterBehaviorAbstract
{
public:
	virtual ~CharacterBehaviorAbstract();
	virtual void Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move) = 0;
	virtual void Action(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt) = 0;
	virtual void Finalize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move) = 0;
};

//-----------------------------------------------------------------------------
//����̐ݒ�ƊǗ����s���N���X
class CharacterBehavior
{
private:
	CharacterBehaviorAbstract*	behavior;
	TimeCount					timeCnt;

public:
	CharacterBehavior(int moveNum);
	~CharacterBehavior();

	//�����ݒ肷��
	void SetBehavior(int moveNum);

	void Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Finalize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};


//-----------------------------------------------
//0�F�������Ȃ�
class Behavior_NoMotion : public CharacterBehaviorAbstract
{
public:
	void Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//1�F�����Ă�������Ɉړ�����
class Behavior_MovementToDirection : public CharacterBehaviorAbstract
{
public:
	void Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//2�F�n�ʂŃW�����v
class Behavior_JumpAtGround : public CharacterBehaviorAbstract
{
public:
	void Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//3�F�O���ɍU������
class Behavior_FrontAttack : public CharacterBehaviorAbstract
{
private:
	void CreateAttackCollision();

public:
	void Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//4�F
