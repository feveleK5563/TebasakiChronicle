#pragma once
#include <vector>
#include "SystemClass.h"
#include "../../../BaseClass/Status/Status.h"
#include "../../../BaseClass/Move.h"
#include "../../TemporaryCollision/TemporaryCollisionManager.h"
#include "../../../TimeCount.h"

//-----------------------------------------------------------------------------
//動作の抽象クラス
class CharacterBehaviorAbstract
{
public:
	virtual ~CharacterBehaviorAbstract();
	virtual void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move) = 0;
	virtual void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt) = 0;
	virtual void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move) = 0;
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

	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};


/* テンプレ

//-----------------------------------------------
//
class Behavior_ : public CharacterBehaviorAbstract
{
public:
void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

*/

//-----------------------------------------------
//何もしない
class Behavior_NoMotion : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//向きを変更する
class Behavior_ChangeDirection : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//向いている方向に移動する
class Behavior_MovementToDirection : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//一回だけジャンプする
class Behavior_OnceJump : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//前方に攻撃する
class Behavior_FrontAttack : public CharacterBehaviorAbstract
{
private:
	void CreateAttackCollision();

public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//4：
