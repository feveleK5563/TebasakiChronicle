#pragma once

//動作パターン遷移の基底クラス
class EnemyMoveTransition
{
public:
	EnemyMoveTransition(){}
	virtual ~EnemyMoveTransition(){}
	virtual bool Transition() = 0;
};

//-----------------------------------------------
//常時使用 (二つ以上設定した場合動作の保証はできないぜ)
class ETransition_Default : public EnemyMoveTransition
{
public:
	bool Transition();
};