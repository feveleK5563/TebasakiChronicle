#include "EnemyMoveTransition.h"

EnemyMoveTransition::EnemyMoveTransition(){}
EnemyMoveTransition::~EnemyMoveTransition(){}

//-----------------------------------------------------------------------------
//0�F�J�ڂ��Ȃ�
bool ETransition_NotTransition::Transition(CollisionManager& cm, Status& status, const bool endMovePattern)
{
	return false;
}

//-----------------------------------------------------------------------------
//1�F��A�̓��삪�I�������Ƃ�
ETransition_EndMovePattern::ETransition_EndMovePattern(int transitionNum)
{
	if (transitionNum > 0)
		isTrue = true;
	else
		isTrue = false;
}
bool ETransition_EndMovePattern::Transition(CollisionManager& cm, Status& status, const bool endMovePattern)
{
	if (endMovePattern == true)
		return true == isTrue;

	return false == isTrue;
}

//-----------------------------------------------------------------------------
//2�F���E���Ƀv���C���[�������Ă���Ƃ�
ETransition_PlayerIntoVisibility::ETransition_PlayerIntoVisibility(int transitionNum)
{
	if (transitionNum > 0)
		isTrue = true;
	else
		isTrue = false;
}
bool ETransition_PlayerIntoVisibility::Transition(CollisionManager& cm, Status& status, const bool endMovePattern)
{
	if (cm.CheckHitSubCollisionObejct(1))
		return true == isTrue;

	return false == isTrue;
}