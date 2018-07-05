#pragma once
#include <vector>
#include "SystemClass.h"
#include "../../../Effect/Effect.h"
#include "../../../BaseClass/Status/Status.h"
#include "../../../BaseClass/Move.h"
#include "../../TemporaryCollision/TemporaryCollisionManager.h"
#include "../../../TimeCount.h"
#include "../../../Helper.h"

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

public:
	CharacterBehavior(int moveNum);
	~CharacterBehavior();

	//動作を設定する
	void SetBehavior(int moveNum);

	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move, TimeCount& timeCnt);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};


/* 動作追加のためのテンプレ

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
//無条件に一回だけジャンプする
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
//重力の有無を切り替える
class Behavior_SwitchingGravity : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//重力を無効にして浮く
class Behavior_DisableGravityAndFloat : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//重力を一時的に二倍にする
class Behavior_ToDoubleGravity : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//重力を一時的に半分にする
class Behavior_ToHarfGravity : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//空中で上下に揺れる
class Behavior_AirIdle : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//空中で上下に揺れながら向いている方向に移動する
class Behavior_AirMovementToDirection : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//Y座標の真ん中から前方に弾を発射する
class Behavior_ShotBulletFromMiddle : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//重力アリの爆弾を投げる
class Behavior_ThrowBomb : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//一定時間無敵状態になる
class Behavior_Invulnerable : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};