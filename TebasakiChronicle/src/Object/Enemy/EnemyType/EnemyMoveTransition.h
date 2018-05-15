#pragma once
#include "../../../BaseClass/Collision/CollisionManager.h"

//動作パターン遷移の基底クラス
class EnemyMoveTransition
{
protected:
	bool isTrue;	//これがfalseだと戻り値のbool型が反転する

public:
	EnemyMoveTransition();
	virtual ~EnemyMoveTransition();

	virtual bool Transition(CollisionManager& cm, Status& status, const bool endMovePattern) = 0;
};

//条件が重複する場合、パターン番号の若いほうが優先される

//-----------------------------------------------
//0：遷移しない
class ETransition_NotTransition : public EnemyMoveTransition
{
public:
	bool Transition(CollisionManager& cm, Status& status, const bool endMovePattern);
};

//-----------------------------------------------
//1：一連の動作が終了したとき
class ETransition_EndMovePattern : public EnemyMoveTransition
{
public:
	ETransition_EndMovePattern(int transitionNum);
	bool Transition(CollisionManager& cm, Status& status, const bool endMovePattern);
};

//-----------------------------------------------
//2：視界内にプレイヤーが入っているとき
class ETransition_PlayerIntoVisibility : public EnemyMoveTransition
{
public:
	ETransition_PlayerIntoVisibility(int transitionNum);
	bool Transition(CollisionManager& cm, Status& status, bool endMovePattern);
};