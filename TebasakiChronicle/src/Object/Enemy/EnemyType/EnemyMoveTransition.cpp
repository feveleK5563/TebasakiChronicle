#include "EnemyMoveTransition.h"

EnemyMoveTransitionAbstract::~EnemyMoveTransitionAbstract(){}

//�R���X�g���N�^
EnemyMoveTransition::EnemyMoveTransition(EnemyMoveTransitionAbstract* emta, int transitionNum) :
	transition(emta),
	isTrue(transitionNum >= 0) {}
//�f�X�g���N�^
EnemyMoveTransition::~EnemyMoveTransition()
{
	delete transition;
}

//-----------------------------------------------
//�J�ڏ������N���A������true��Ԃ�
bool EnemyMoveTransition::IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern)
{
	return transition->IsTransition(cm, status, endMovePattern) == isTrue;
}

//-----------------------------------------------------------------------------
//0�F�J�ڂ��Ȃ�
bool ETransition_NotTransition::IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern)
{
	return false;
}

//-----------------------------------------------------------------------------
//1�F��A�̓��삪�I�������Ƃ�
bool ETransition_EndMovePattern::IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern)
{
	if (endMovePattern == true)
		return true;

	return false;
}

//-----------------------------------------------------------------------------
//2�F���E���Ƀv���C���[�������Ă���Ƃ�
bool ETransition_PlayerIntoVisibility::IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern)
{
	if (cm.CheckHitSubCollisionObejct(1))
		return true;

	return false;
}