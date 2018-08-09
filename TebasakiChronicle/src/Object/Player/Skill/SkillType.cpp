#include "SkillType.h"

//コンストラクタ
//!@brief コンストラクタ
//!@param[in] 最大使用回数
//!@param[in] 出現距離
//!@param[in] 継続時間
SkillType::SkillType(const int& moveID,const int& maxUseNum, const float& appearDist, const int& continueTime,const int& attackPoint)
	: maxUseNum(maxUseNum), appearDist(appearDist), continueTime(continueTime)
	, charaBehaivor(new CharacterBehavior(moveID)), attackPoint(attackPoint)
{
	
}


//-----------------------------------------------------------
//デストラクタ
//-----------------------------------------------------------
SkillType::~SkillType()
{
	Memory::SafeDelete(charaBehaivor);
}



//-----------------------------------------------------------
//更新処理
//-----------------------------------------------------------
void	SkillType::UpDate(GameObject& object)
{
	
}

//初期化
void	SkillType::BehaivorInit(TemporaryCollisionManager& tempCol, GameObject& gameObject, TimeCount& timeCnt)
{
	charaBehaivor->Initialize(tempCol, gameObject, timeCnt);
}
//終了
void	SkillType::BehaivorFinal(TemporaryCollisionManager& tempCol, GameObject& gameObject)
{
	charaBehaivor->Finalize(tempCol, gameObject);
}
void	SkillType::Behaivor(TemporaryCollisionManager& tempCol, GameObject& gameObject, CollisionManager* collmanager, TimeCount& timeCnt)
{
	charaBehaivor->Action(tempCol, gameObject, collmanager, timeCnt);
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

