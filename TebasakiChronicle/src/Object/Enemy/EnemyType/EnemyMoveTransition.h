#pragma once
#include "../../../BaseClass/Collision/CollisionManager.h"

//動作パターン遷移の基底クラス
class EnemyMoveTransition
{
public:
	EnemyMoveTransition();
	virtual ~EnemyMoveTransition();

	virtual bool Transition(CollisionManager& cm, Status& status) = 0;
};

//条件が重複する場合、パターン番号の若いほうが優先される

//-----------------------------------------------
//常時使用
class ETransition_Default : public EnemyMoveTransition
{
public:
	bool Transition(CollisionManager& cm, Status& status);
};

//-----------------------------------------------
//視界内にプレイヤーが入っているとき
class ETransition_PIntoView : public EnemyMoveTransition
{
public:
	bool Transition(CollisionManager& cm, Status& status);
};

//-----------------------------------------------
//視界内に入っているプレイヤーが自身の反対方向に移動したとき
class ETransition_PMoveOtherSide : public EnemyMoveTransition
{
public:
	bool Transition(CollisionManager& cm, Status& status);
};