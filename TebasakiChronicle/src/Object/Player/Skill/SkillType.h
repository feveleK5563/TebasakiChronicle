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
	//!@brief コンストラクタ
	//!@param[in] 最大使用回数
	//!@param[in] 出現距離
	//!@param[in] 継続時間
	SkillType(const int& maxUseNum,const float& appearDist,const int& continueTime);
	virtual ~SkillType();

	virtual void	UpDate() = 0;
	
public:
	int		GetContinueTime() const;
	float	GetAppearDist() const;
	int		GetMaxUseNum() const;

protected:
	CharacterBehavior	charaBehaivor;	//動作
	int				continueTime;	//継続時間
	float			appearDist;		//出現距離
	int				maxUseNum;		//最大使用回数
};

