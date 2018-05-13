#include "SkillData.h"


//----------------------------------------------------------------
//コンストラクタ
//----------------------------------------------------------------
SkillData::SkillData()
{

}

//----------------------------------------------------------------
//デストラクタ
//----------------------------------------------------------------
SkillData::~SkillData()
{

}


//!@brief 保持しているスキルIDを返す
//!@return skillIDを返す
int		SkillData::GetSkillID()
{
	return skillID;
}


//!@brief スキルの種類を返す
//!@return SkillTypeを返す
SkillType& SkillData::GetSkillType() const
{
	return *skillType;
}

//!@brief スキルの画像名を返す
//!@return SkillImageNameを返す
std::string& SkillData::GetSkillImageName()
{
	return skillImageName;
}


//!@brief スキルの出現位置を返す
//!@return SkillAppearPosを返す
K_Math::Vector3& SkillData::GetSkillAppearPos()
{
	return appearPos;
}

//!@brief スキルのキャラチップ
AnimationCharaChip& SkillData::GetAnimCharaChip()
{
	return *animCharaChip;
}


//!@brief スキルデータをセットする
//!@param[in] skillID_ スキルID
//!@param[in] skillType_ スキルの種類
//!@param[in] spriteObj_ スプライトオブジェクト
//!@param[in] animCharaChip_ アニメーションキャラチップ
void	SkillData::SetSkillData(const int& skillID_,
	SkillType* skillType_,
	K_Graphics::SpriteObject* spriteObj_,
	AnimationCharaChip* animCharaChip_)
{
	SetSkillID(skillID_);
	SetSkillType(skillType_);
	SetSpriteObj(spriteObj_);
	SetAnimCharaChip(animCharaChip_);
}




//!@brief スキルの種類のセット
//!@param[in] skillType_ 取得したスキルの種類
void	SkillData::SetSkillType(SkillType* skillType_)
{
	skillType = skillType_;
}

//!@brief スキルIDのセット
//!@brief[in] skillID_ 取得したスキルID
void	SkillData::SetSkillID(const int& skillID_)
{
	skillID = skillID_;
}

//!@brief スプライトオブジェクトのセット
//!@param[in] spriteObj_ 取得したスプライト
void	SkillData::SetSpriteObj(K_Graphics::SpriteObject* spriteObj_)
{
	spriteObj = spriteObj_;
}


//!@brief アニメーションキャラチップ
//!@param[in] animCharaChip_ 取得したキャラチップ
void	SkillData::SetAnimCharaChip(AnimationCharaChip* animCharaChip_)
{
	animCharaChip = animCharaChip_;
}

//!@brief スキルの画像名を取得
//!@param[in] skillImageName_ 取得したスキル画像名
void	SkillData::SetSkillImageName(const std::string& skillImageName_)
{
	skillImageName = skillImageName_;
}

//!@brief 出現位置を取得
//!@param[in] appearPos_ 取得した出現位置
void	SkillData::SetSkillAppearPos(const K_Math::Vector3& appearPos_)
{
	appearPos = appearPos_;
}