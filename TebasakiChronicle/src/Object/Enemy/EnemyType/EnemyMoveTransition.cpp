#include "EnemyMoveTransition.h"

EnemyMoveTransitionAbstract::~EnemyMoveTransitionAbstract(){}

//コンストラクタ
EnemyMoveTransition::EnemyMoveTransition(EnemyMoveTransitionAbstract* emta, int transitionNum) :
	transition(emta),
	isTrue(transitionNum >= 0) {}
//デストラクタ
EnemyMoveTransition::~EnemyMoveTransition()
{
	delete transition;
}

//-----------------------------------------------
//遷移条件をクリアしたらtrueを返す
bool EnemyMoveTransition::IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern)
{
	return transition->IsTransition(cm, status, endMovePattern) == isTrue;
}

//-----------------------------------------------------------------------------
//0：遷移しない
bool ETransition_NotTransition::IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern)
{
	return false;
}

//-----------------------------------------------------------------------------
//1：一連の動作が終了したとき
bool ETransition_EndMovePattern::IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern)
{
	if (endMovePattern == true)
		return true;

	return false;
}

//-----------------------------------------------------------------------------
//2：視界内にプレイヤーが入っているとき
bool ETransition_PlayerIntoVisibility::IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern)
{
	if (cm.CheckHitSubCollisionObejct(1))
		return true;

	return false;
}