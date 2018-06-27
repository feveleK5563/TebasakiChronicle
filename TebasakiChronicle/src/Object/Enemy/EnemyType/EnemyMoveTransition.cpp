#include "EnemyMoveTransition.h"

EnemyMoveTransitionAbstract::~EnemyMoveTransitionAbstract(){}

EnemyMoveTransition::EnemyMoveTransition(int transitionNum) :
	isReturnTrue(transitionNum >= 0)
{
	SetTransition(transitionNum);
}
EnemyMoveTransition::~EnemyMoveTransition()
{
	delete transition;
}

//-----------------------------------------------------------------------------
//動作パターン遷移条件を設定する
void EnemyMoveTransition::SetTransition(int transitionNum)
{
	switch (abs(transitionNum))
	{
	case 0:	//遷移しない
		transition = new ETransition_NotTransition();
		break;

	case 1: //一連の動作が終了したとき
		transition = new ETransition_EndMovePattern();
		break;

	case 2: //視界内にプレイヤーが入っているとき
		transition = new ETransition_PlayerIntoVisibility();
		break;

	case 3:	//攻撃遷移用コリジョンにプレイヤーが入っているとき
		transition = new ETransition_PlayerIntoAttackArea();
	}
}
//-----------------------------------------------
//遷移条件をクリアしたらtrueを返す
bool EnemyMoveTransition::IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern)
{
	return transition->IsTransition(cm, status, endMovePattern) == isReturnTrue;
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

//-----------------------------------------------
//3：攻撃遷移用コリジョンにプレイヤーが入っているとき
bool ETransition_PlayerIntoAttackArea::IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern)
{
	if (cm.CheckHitSubCollisionObejct(2))
		return true;

	return false;
}