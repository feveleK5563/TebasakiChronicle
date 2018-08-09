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
		break;

	case 4:	//足元が地形と接触しているとき
		transition = new ETransition_HitFoot();
		break;

	case 5: //視界内のプレイヤーが向いている方向にいるとき
		transition = new ETransition_IntoVisibilityAndMatchDirection();
		break;

	case 6:	//ダメージを受けたとき
		transition = new ETransition_TakeDamage();
		break;

	case 7:	//ランダムに二択
		transition = new ETransition_SelectRandom();
		break;
	}
}
//-----------------------------------------------
//遷移条件をクリアしたらtrueを返す
bool EnemyMoveTransition::IsTransition(CollisionManager& cm, Status& status, bool endMovePattern)
{
	return transition->IsTransition(cm, status, endMovePattern) == isReturnTrue;
}

//-----------------------------------------------------------------------------
//0：遷移しない
bool ETransition_NotTransition::IsTransition(CollisionManager& cm, Status& status, bool endMovePattern)
{
	return false;
}

//-----------------------------------------------------------------------------
//1：一連の動作が終了したとき
bool ETransition_EndMovePattern::IsTransition(CollisionManager& cm, Status& status, bool endMovePattern)
{
	if (endMovePattern == true)
		return true;

	return false;
}

//-----------------------------------------------------------------------------
//2：視界内にプレイヤーが入っているとき
bool ETransition_PlayerIntoVisibility::IsTransition(CollisionManager& cm, Status& status, bool endMovePattern)
{
	if (cm.CheckHitSubCollisionObejct(EnemyCollisionName::Visibility))
		return true;

	return false;
}

//-----------------------------------------------
//3：攻撃遷移用コリジョンにプレイヤーが入っているとき
bool ETransition_PlayerIntoAttackArea::IsTransition(CollisionManager& cm, Status& status, bool endMovePattern)
{
	if (cm.CheckHitSubCollisionObejct(EnemyCollisionName::AttackArea))
		return true;

	return false;
}

//-----------------------------------------------
//4：足元が地形と接触しているとき
bool ETransition_HitFoot::IsTransition(CollisionManager& cm, Status& status, bool endMovePattern)
{
	if (cm.CheckHitSubCollisionObejct(EnemyCollisionName::CheckFoot))
		return true;

	return false;
}

//-----------------------------------------------
//5：視界内のプレイヤーが向いている方向にいるとき
bool ETransition_IntoVisibilityAndMatchDirection::IsTransition(CollisionManager& cm, Status& status, bool endMovePattern)
{
	auto pdata = cm.GetConflictionObjectsTag(1);
	if (pdata.size() <= 0)
		return false;

	if ((((Status*)pdata[0])->GetPos().x < status.GetPos().x && status.GetDirection() == Status::Direction::Left) ||
		(((Status*)pdata[0])->GetPos().x > status.GetPos().x && status.GetDirection() == Status::Direction::Right))
	{
		return true;
	}
	return false;
}

//-----------------------------------------------
//6：ダメージを受けたとき
bool ETransition_TakeDamage::IsTransition(CollisionManager& cm, Status& status, bool endMovePattern)
{
	return status.GetState() == Status::State::Invalid;
}

//-----------------------------------------------
//7：ランダムに二択
bool ETransition_SelectRandom::IsTransition(CollisionManager& cm, Status& status, bool endMovePattern)
{
	//return rand() % 2;
	return 0;
}