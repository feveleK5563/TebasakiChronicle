#include "EnemyMoveTransition.h"

EnemyMoveTransition::EnemyMoveTransition(){}
EnemyMoveTransition::~EnemyMoveTransition(){}

//-----------------------------------------------------------------------------
//0：常にfalseを返す
bool ETransition_NotTrans::Transition(CollisionManager& cm, Status& status)
{
	return false;
}

//-----------------------------------------------------------------------------
//1：視界内にプレイヤーが入っているとき
bool ETransition_PIntoView::Transition(CollisionManager& cm, Status& status)
{
	if (cm.CheckHitSubCollisionObejct(1))
		return true;

	return false;
}

//-----------------------------------------------------------------------------
//2：視界内に入っているプレイヤーが自身の反対方向に移動したとき
bool ETransition_PMoveOtherSide::Transition(CollisionManager& cm, Status& status)
{
	//視界用コリジョンからプレイヤーの座標を受け取る
	for (auto it : cm.GetConflictionObjectsTag(1))
	{
		Status* pst = (Status*)it->userData;
		if (status.GetState() == Status::Right)
		{
			if ((status.GetPos().x() - pst->GetPos().x()) > 0.f)
				return true;
		}
		else
		{
			if ((status.GetPos().x() - pst->GetPos().x()) < 0.f)
				return true;
		}
	}
	return false;
}