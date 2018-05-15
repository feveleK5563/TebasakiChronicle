#include "EnemyMoveTransition.h"

EnemyMoveTransition::EnemyMoveTransition(){}
EnemyMoveTransition::~EnemyMoveTransition(){}

//-----------------------------------------------------------------------------
//0：遷移しない
bool ETransition_NotTransition::Transition(CollisionManager& cm, Status& status, const bool endMovePattern)
{
	return false;
}

//-----------------------------------------------------------------------------
//1：一連の動作が終了したとき
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
//2：視界内にプレイヤーが入っているとき
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