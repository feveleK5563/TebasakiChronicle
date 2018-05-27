#pragma once
#include <vector>
#include "SystemClass.h"
#include "../../../BaseClass/Status/Status.h"
#include "../../../BaseClass/Move.h"
#include "../../../BaseClass/Collision/CollisionManager.h"
#include "../../TemporaryCollision/TemporaryCollisionManager.h"
#include "../../../TimeCount.h"

//-----------------------------------------------------------------------------
//動作の抽象クラス
class CharacterBehaviorAbstract
{
public:
	virtual ~CharacterBehaviorAbstract();
	virtual void Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move) = 0;
	virtual void Action(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt) = 0;
	virtual void Finalize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move) = 0;
};

//-----------------------------------------------------------------------------
//動作の設定と管理を行うクラス
class CharacterBehavior
{
private:
	CharacterBehaviorAbstract*	behavior;
	TimeCount					timeCnt;

public:
	CharacterBehavior(int moveNum);
	~CharacterBehavior();

	//動作を設定する
	void SetBehavior(int moveNum);

	void Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Finalize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};


//-----------------------------------------------
//0：何もしない
class Behavior_NoMotion : public CharacterBehaviorAbstract
{
public:
	void Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//1：向いている方向に移動する
class Behavior_MovementToDirection : public CharacterBehaviorAbstract
{
public:
	void Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//2：地面でジャンプ
class Behavior_JumpAtGround : public CharacterBehaviorAbstract
{
public:
	void Initialize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(CollisionManager& cmanager, TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//3：前方に攻撃する
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
//4：
