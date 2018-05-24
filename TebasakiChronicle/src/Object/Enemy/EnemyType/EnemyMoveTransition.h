#pragma once
#include "../../../BaseClass/Collision/CollisionManager.h"

//-----------------------------------------------------------------------------
//動作パターン遷移の抽象クラス
class EnemyMoveTransitionAbstract
{
public:
	virtual ~EnemyMoveTransitionAbstract();
	virtual bool IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern) = 0;
};

//-----------------------------------------------------------------------------
//動作パターン遷移を行うクラス
class EnemyMoveTransition
{
private:
	EnemyMoveTransitionAbstract*	transition;
	const bool						isTrue;	//これがfalseだと戻り値のbool型が反転する

public:
	EnemyMoveTransition(EnemyMoveTransitionAbstract* emta, int transitionNum);
	~EnemyMoveTransition();

	//遷移条件をクリアしたらtrueを返す
	bool IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern);
};

//条件が重複する場合、パターン番号の若いほうが優先される

//-----------------------------------------------
//0：遷移しない
class ETransition_NotTransition : public EnemyMoveTransitionAbstract
{
public:
	bool IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern);
};

//-----------------------------------------------
//1：一連の動作が終了したとき
class ETransition_EndMovePattern : public EnemyMoveTransitionAbstract
{
public:
	bool IsTransition(CollisionManager& cm, Status& status, const bool endMovePattern);
};

//-----------------------------------------------
//2：視界内にプレイヤーが入っているとき
class ETransition_PlayerIntoVisibility : public EnemyMoveTransitionAbstract
{
public:
	bool IsTransition(CollisionManager& cm, Status& status, bool endMovePattern);
};