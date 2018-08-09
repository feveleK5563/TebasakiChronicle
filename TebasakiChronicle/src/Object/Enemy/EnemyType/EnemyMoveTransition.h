#pragma once
#include "../../../BaseClass/Collision/CollisionManager.h"

//-----------------------------------------------------------------------------
//動作パターン遷移の抽象クラス
class EnemyMoveTransitionAbstract
{
public:
	virtual ~EnemyMoveTransitionAbstract();
	virtual bool IsTransition(CollisionManager& cm, Status& status, bool endMovePattern) = 0;
};

//-----------------------------------------------------------------------------
//動作パターン遷移を管理クラス
class EnemyMoveTransition
{
private:
	EnemyMoveTransitionAbstract*	transition;
	const bool						isReturnTrue;	//これがfalseだと戻り値のbool型が反転する

public:
	EnemyMoveTransition(int transitionNum);
	~EnemyMoveTransition();

	//遷移条件を設定する
	void SetTransition(int transitionNum);

	//遷移条件をクリアしたらtrueを返す
	bool IsTransition(CollisionManager& cm, Status& status, bool endMovePattern);
};

//条件が重複する場合、パターン番号の若いほうが優先される

//-----------------------------------------------
//0：遷移しない
class ETransition_NotTransition : public EnemyMoveTransitionAbstract
{
public:
	bool IsTransition(CollisionManager& cm, Status& status, bool endMovePattern);
};

//-----------------------------------------------
//1：一連の動作が終了したとき
class ETransition_EndMovePattern : public EnemyMoveTransitionAbstract
{
public:
	bool IsTransition(CollisionManager& cm, Status& status, bool endMovePattern);
};

//-----------------------------------------------
//2：視界内にプレイヤーが入っているとき
class ETransition_PlayerIntoVisibility : public EnemyMoveTransitionAbstract
{
public:
	bool IsTransition(CollisionManager& cm, Status& status, bool endMovePattern);
};

//-----------------------------------------------
//3：攻撃遷移用コリジョンにプレイヤーが入っているとき
class ETransition_PlayerIntoAttackArea : public EnemyMoveTransitionAbstract
{
public:
	bool IsTransition(CollisionManager& cm, Status& status, bool endMovePattern);
};

//-----------------------------------------------
//4：足元が地形と接触しているとき
class ETransition_HitFoot : public EnemyMoveTransitionAbstract
{
public:
	bool IsTransition(CollisionManager& cm, Status& status, bool endMovePattern);
};

//-----------------------------------------------
//5：視界内のプレイヤーが向いている方向にいるとき
class ETransition_IntoVisibilityAndMatchDirection : public EnemyMoveTransitionAbstract
{
public:
	bool IsTransition(CollisionManager& cm, Status& status, bool endMovePattern);
};

//-----------------------------------------------
//6：ダメージを受けたとき
class ETransition_TakeDamage : public EnemyMoveTransitionAbstract
{
public:
	bool IsTransition(CollisionManager& cm, Status& status, bool endMovePattern);
};

//-----------------------------------------------
//7：ランダムに二択
class ETransition_SelectRandom : public EnemyMoveTransitionAbstract
{
public:
	bool IsTransition(CollisionManager& cm, Status& status, bool endMovePattern);
};