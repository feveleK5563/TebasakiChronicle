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

public:
	CharacterBehavior(int moveNum);
	~CharacterBehavior();

	//�����ݒ肷��
	void SetBehavior(int moveNum);

	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move, TimeCount& timeCnt);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};


/* ����ǉ��̂��߂̃e���v��

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
//�������Ɉ�񂾂��W�����v����
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
//�d�̗͂L����؂�ւ���
class Behavior_SwitchingGravity : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//�d�͂𖳌��ɂ��ĕ���
class Behavior_DisableGravityAndFloat : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//�d�͂��ꎞ�I�ɓ�{�ɂ���
class Behavior_ToDoubleGravity : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//�d�͂��ꎞ�I�ɔ����ɂ���
class Behavior_ToHarfGravity : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//�󒆂ŏ㉺�ɗh���
class Behavior_AirIdle : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//�󒆂ŏ㉺�ɗh��Ȃ�������Ă�������Ɉړ�����
class Behavior_AirMovementToDirection : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//Y���W�̐^�񒆂���O���ɒe�𔭎˂���
class Behavior_ShotBulletFromMiddle : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//�d�̓A���̔��e�𓊂���
class Behavior_ThrowBomb : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};

//-----------------------------------------------
//��莞�Ԗ��G��ԂɂȂ�
class Behavior_Invulnerable : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
	void Action(TemporaryCollisionManager& tempmanager, Status& status, Move& move, const TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, Status& status, Move& move);
};