#pragma once
#include "K_Math\MyMathFanctions.h"

//----------------------------------------------------------
//スキルの種類のインターフェイス
//概要:スキルの種類を表すインターフェイス
//製作者:日比野
//----------------------------------------------------------
class SkillType
{
protected:
	//!@brief コンストラクタ
	//!@param[in] maxUseNum_ 最大使用回数
	//!@param[in] continueTime_ 継続時間
	//!@param[in] appearPos_ 出現位置
	explicit SkillType(const int& maxUseNum_,const int& continueTime_,const K_Math::Vector3& appearPos_);
public:
	virtual ~SkillType() {};

	virtual void	UpDate() = 0;
	virtual void	Render() = 0;

protected:
	int				maxUseNum;		//最大使用回数
	int				continueTime;	//継続時間
	K_Math::Vector3	appearPos;		//出現位置
};