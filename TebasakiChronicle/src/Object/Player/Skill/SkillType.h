#pragma once
#include "K_Math\MyMathFanctions.h"
#include "SkillObject.h"
#include "../src/Object/Enemy/EnemyType/CharacterBehavior.h"

//----------------------------------------------------------
//スキルの種類のインターフェイス
//概要:スキルの種類を表すインターフェイス
//製作者:日比野
//----------------------------------------------------------
class SkillType
{
public:
	//!@brief	スキルのタイプ(系統)
	enum class Type
	{
		MoveSkill,			//動作系
		AttackSkill,		//攻撃系
		PassiveSkill,		//パッシブ系
	};

public:
	//!@brief コンストラクタ
	//!@param[in] 動作ID
	//!@param[in] 最大使用回数
	//!@param[in] 出現距離
	//!@param[in] 継続時間
	//!@param[in] 攻撃力
	SkillType(const int& moveID,const int& maxUseNum,const float& appearDist,const int& continueTime,const int& attackPoint);
	virtual ~SkillType();

	virtual void	UpDate(GameObject& object) = 0;
	
public:
	int		GetContinueTime() const;
	float	GetAppearDist() const;
	int		GetMaxUseNum() const;
	int		GetAttackPoint() const;


	//初期化
	void	BehaivorInit(TemporaryCollisionManager& tempCol, Status& status, Move& move);
	//終了
	void	BehaivorFinal(TemporaryCollisionManager& tempCol, Status& status, Move& move);
	//動作
	void	Behaivor(TemporaryCollisionManager& tempCol,Status& status,Move& move);
	
	//!@brief	スキルのタイプ(系統)を返す
	//!@return	スキルのタイプ
	Type&	GetType();

	//!@brief	与えるコリジョンマスクを返す
	//!@return	与えるコリジョンマスク
	Status::CollisionMaskState&	GetGiveCollisionMask();
	//!@brief	受け取るコリジョンマスクを返す
	//!@return	受け取るコリジョンマスク
	Status::CollisionMaskState&	GetReciveCollisionMask();


protected:
	CharacterBehavior	charaBehaivor;	//動作
	int					continueTime;	//継続時間
	float				appearDist;		//出現距離(プレイヤーからの距離)
	int					maxUseNum;		//最大使用回数
	int					attackPoint;	//攻撃力
	Type				type;			//タイプ
	Status::CollisionMaskState		giveCollisionMask;		//与えるコリジョンマスク
	Status::CollisionMaskState		reciveCollisionMask;	//受け取るコリジョンマスク
};

