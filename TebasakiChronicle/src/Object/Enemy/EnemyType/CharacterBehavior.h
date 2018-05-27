#pragma once
#include <vector>
#include "SystemClass.h"
#include "../../../BaseClass/Status/Status.h"
#include "../../../BaseClass/Move.h"
#include "../../TemporaryCollision/TemporaryCollisionManager.h"
#include "../../../TimeCount.h"

//-----------------------------------------------------------------------------
//����̒��ۃN���X
class CharacterBehaviorAbstract
{
public:
	virtual ~CharacterBehaviorAbstract();
	virtual void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move) = 0;
	virtual void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt) = 0;
	virtual void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move) = 0;
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

	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};


/* �e���v��

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
//�������Ȃ�
class Behavior_NoMotion : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//������ύX����
class Behavior_ChangeDirection : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//�����Ă�������Ɉړ�����
class Behavior_MovementToDirection : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//��񂾂��W�����v����
class Behavior_OnceJump : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//�O���ɍU������
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
//4�F
