#pragma once
#include "K_Math\MyMathFanctions.h"
#include "SkillObject.h"


//----------------------------------------------------------
//スキルの種類のインターフェイス
//概要:スキルの種類を表すインターフェイス
//製作者:日比野
//----------------------------------------------------------
class SkillType
{
protected:
	//!@brief コンストラクタ
	//!@param[in] continueTime_ 継続時間
	//!@param[in] distance_ 距離
	//!@param[in] appearPos_ 出現位置
	//!@param[in] animCharaChip アニメーションキャラチップ
	explicit SkillType(const int& continueTime_,
		const float& distance_,
		GameObject& obj,
		const std::string& textureName,
		const AnimationCharaChip& animCharaChip);
public:
	virtual ~SkillType();

	virtual void	UpDate() = 0;
	virtual void	Render() = 0;

	virtual bool	KillTime() = 0;

protected:
	int				continueTime;	//継続時間
	float			distance;		//距離
	K_Math::Vector3	appearPos;		//出現位置
	SkillObject*	skillObject;	//スキルの当たり判定など
};

