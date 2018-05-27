#pragma once
#include "../../../BaseClass/Collision/CollisionManager.h"

//-----------------------------------------------------------------------------
//����p�^�[���J�ڂ̒��ۃN���X
class EnemyMoveTransitionAbstract
{
public:
	virtual ~EnemyMoveTransitionAbstract();
	virtual bool IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern) = 0;
};

//-----------------------------------------------------------------------------
//����p�^�[���J�ڂ��Ǘ��N���X
class EnemyMoveTransition
{
private:
	EnemyMoveTransitionAbstract*	transition;
	const bool						isReturnTrue;	//���ꂪfalse���Ɩ߂�l��bool�^�����]����

public:
	EnemyMoveTransition(int transitionNum);
	~EnemyMoveTransition();

	//�J�ڏ�����ݒ肷��
	void SetTransition(int transitionNum);

	//�J�ڏ������N���A������true��Ԃ�
	bool IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern);
};

//�������d������ꍇ�A�p�^�[���ԍ��̎Ⴂ�ق����D�悳���

//-----------------------------------------------
//0�F�J�ڂ��Ȃ�
class ETransition_NotTransition : public EnemyMoveTransitionAbstract
{
public:
	bool IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern);
};

//-----------------------------------------------
//1�F��A�̓��삪�I�������Ƃ�
class ETransition_EndMovePattern : public EnemyMoveTransitionAbstract
{
public:
	bool IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern);
};

//-----------------------------------------------
//2�F���E���Ƀv���C���[�������Ă���Ƃ�
class ETransition_PlayerIntoVisibility : public EnemyMoveTransitionAbstract
{
public:
	bool IsTransition(CollisionManager& cm, Status& status, bool endMovePattern);
};