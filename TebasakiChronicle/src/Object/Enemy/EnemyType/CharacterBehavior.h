#pragma once
#include <vector>
#include "SystemClass.h"
#include "../../../Effect/Effect.h"
#include "../../GameObject.h"
#include "../../TemporaryCollision/TemporaryCollisionManager.h"
#include "../../../TimeCount.h"
#include "../../../Helper.h"

//-----------------------------------------------------------------------------
//����̒��ۃN���X
class CharacterBehaviorAbstract
{
public:
	virtual ~CharacterBehaviorAbstract();
	virtual void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) = 0;
	virtual void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) = 0;
	virtual void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) = 0;
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

	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject, TimeCount& timeCnt);
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, TimeCount& timeCnt);
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject);
};


/* ����ǉ��̂��߂̃e���v��

//-----------------------------------------------
//
class Behavior_ : public CharacterBehaviorAbstract
{
public:
void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

*/

//-----------------------------------------------
//�������Ȃ�
class Behavior_NoMotion : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//������ύX����
class Behavior_ChangeDirection : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//�����Ă�������Ɉړ�����
class Behavior_MovementToDirection : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//�������Ɉ�񂾂��W�����v����
class Behavior_OnceJump : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//�O���ɍU������
class Behavior_FrontAttack : public CharacterBehaviorAbstract
{
private:
	void CreateAttackCollision();

public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//�d�̗͂L����؂�ւ���
class Behavior_SwitchingGravity : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//�d�͂𖳌��ɂ��ĕ���
class Behavior_DisableGravityAndFloat : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//�ꎞ�I�ɏd�͂𖳌��ɂ��A��葬�x�ŗ�������
class Behavior_Fall : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//�d�͂��ꎞ�I�ɔ����ɂ���
class Behavior_ToHarfGravity : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//�󒆂ŏ㉺�ɗh���
class Behavior_AirIdle : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//�󒆂ŏ㉺�ɗh��Ȃ�������Ă�������Ɉړ�����
class Behavior_AirMovementToDirection : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//Y���W�̐^�񒆂���O���ɒe�𔭎˂���
class Behavior_ShotBulletFromMiddle : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//�d�̓A���̔��e�𓊂���
class Behavior_ThrowBomb : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager,  GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//���E���̃v���C���[��X���ɍ��킹��
class Behavior_MovePlayerPosX : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//���E���̃v���C���[��Y���ɍ��킹��
class Behavior_MovePlayerPosY : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//�����z�u���̍��W�Ɉړ�����
class Behavior_MoveInitPos : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//�ꎞ�I�ɏd�͂𖳌��ɂ��}�������A����I�����ɃG�t�F�N�g�𔭐�������
class Behavior_HighSpeedFall : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//�R���W�����}�X�N��S�Ė����ɂ���
class Behavior_NonActiveCollisionMask : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//�R���W�����}�X�N��S�ėL���ɂ���
class Behavior_ActiveCollisionMask : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//�r�[��������
class Behavior_Beam : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};

//-----------------------------------------------
//�����Ă�������ɍ����ňړ�����
class Behavior_HighSpeedMove : public CharacterBehaviorAbstract
{
public:
	void Initialize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
	void Action(TemporaryCollisionManager& tempmanager, GameObject& gameObject, CollisionManager* collmanager, const TimeCount& timeCnt) override;
	void Finalize(TemporaryCollisionManager& tempmanager, GameObject& gameObject) override;
};