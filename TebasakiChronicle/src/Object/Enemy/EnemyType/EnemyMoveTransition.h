#pragma once
#include "../../../BaseClass/Collision/CollisionManager.h"

//����p�^�[���J�ڂ̊��N���X
class EnemyMoveTransition
{
protected:
	bool isTrue;	//���ꂪfalse���Ɩ߂�l��bool�^�����]����

public:
	EnemyMoveTransition();
	virtual ~EnemyMoveTransition();

	virtual bool Transition(CollisionManager& cm, Status& status, const bool endMovePattern) = 0;
};

//�������d������ꍇ�A�p�^�[���ԍ��̎Ⴂ�ق����D�悳���

//-----------------------------------------------
//0�F�J�ڂ��Ȃ�
class ETransition_NotTransition : public EnemyMoveTransition
{
public:
	bool Transition(CollisionManager& cm, Status& status, const bool endMovePattern);
};

//-----------------------------------------------
//1�F��A�̓��삪�I�������Ƃ�
class ETransition_EndMovePattern : public EnemyMoveTransition
{
public:
	ETransition_EndMovePattern(int transitionNum);
	bool Transition(CollisionManager& cm, Status& status, const bool endMovePattern);
};

//-----------------------------------------------
//2�F���E���Ƀv���C���[�������Ă���Ƃ�
class ETransition_PlayerIntoVisibility : public EnemyMoveTransition
{
public:
	ETransition_PlayerIntoVisibility(int transitionNum);
	bool Transition(CollisionManager& cm, Status& status, bool endMovePattern);
};