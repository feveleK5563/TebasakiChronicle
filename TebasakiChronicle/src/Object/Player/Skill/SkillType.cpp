#include "SkillType.h"

//コンストラクタ
//!@brief コンストラクタ
//!@param[in] 最大使用回数
//!@param[in] 出現距離
//!@param[in] 継続時間
SkillType::SkillType(const int& moveID,const int& maxUseNum, const float& appearDist, const int& continueTime,const int& attackPoint)
	: maxUseNum(maxUseNum), appearDist(appearDist), continueTime(continueTime)
	, charaBehaivor(moveID), attackPoint(attackPoint)
{
	
}


//-----------------------------------------------------------
//デストラクタ
//-----------------------------------------------------------
SkillType::~SkillType()
{

}



//-----------------------------------------------------------
//更新処理
//-----------------------------------------------------------
void	SkillType::UpDate(GameObject& object)
{
	
}

//初期化
void	SkillType::BehaivorInit(TemporaryCollisionManager& tempCol, Status& status, Move& move)
{
	charaBehaivor.Initialize(tempCol, status, move);
}
//終了
void	SkillType::BehaivorFinal(TemporaryCollisionManager& tempCol, Status& status, Move& move)
{
	charaBehaivor.Finalize(tempCol, status, move);
}
void	SkillType::Behaivor(TemporaryCollisionManager& tempCol, Status& status, Move& move)
{
	charaBehaivor.Action(tempCol, status, move);
}



//取得処理
int		SkillType::GetContinueTime() const
{
	return continueTime;
}
float	SkillType::GetAppearDist() const
{
	return appearDist;
}
int		SkillType::GetMaxUseNum() const
{
	return maxUseNum;
}
int		SkillType::GetAttackPoint() const
{
	return attackPoint;
}


//!@brief	スキルのタイプ(系統)を返す
//!@return	スキルのタイプ
SkillType::Type&	SkillType::GetType()
{
	return type;
}

//!@brief	与えるコリジョンマスクを返す
//!@return	与えるコリジョンマスク
Status::CollisionMaskState&	SkillType::GetGiveCollisionMask()
{
	return giveCollisionMask;
}

//!@brief	受け取るコリジョンマスクを返す
//!@return	受け取るコリジョンマスク
Status::CollisionMaskState&	SkillType::GetReciveCollisionMask()
{
	return reciveCollisionMask;
}