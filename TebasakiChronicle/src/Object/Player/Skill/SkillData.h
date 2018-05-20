#pragma once

#include "K_Graphics/ImageLoader.h"
#include "../src/BaseClass/ImageManager/AnimationCharaChip.h"
#include "SkillType.h"
#include "SkillSword\SkillSword.h"

//------------------------------------------------------------
//スキルのデータ
//概要:スキルのデータを持っている
//製作者:日比野
//------------------------------------------------------------
class SkillData
{
public:
	SkillData();
	~SkillData();

	//!@brief 保持しているスキルIDを返す
	//!@return skillIDを返す
	int		GetSkillID();
	//!@brief スキルの種類を返す
	//!@return SkillTypeを返す
	SkillType& GetSkillType() const;
	//!@brief スキルの画像名を返す
	//!@return SkillImageNameを返す
	std::string& GetSkillImageName();
	//!@brief スキルのキャラチップ
	AnimationCharaChip& GetAnimCharaChip();

	//!@brief スキルデータをセットする
	//!@param[in] skillID_ スキルID
	//!@param[in] animCharaChip_ アニメーションキャラチップ
	void	SetSkillData(	const int& skillID_,
							AnimationCharaChip* animCharaChip_);

public:
	//!@brief スキルの種類のセット
	//!@param[in] skillType_ 取得したスキルの種類
	void	SetSkillType(SkillType* skillType_);
	//!@brief スキルIDのセット
	//!@brief[in] skillID_ 取得したスキルID
	void	SetSkillID(const int& skillID_);
	//!@brief アニメーションキャラチップ
	//!@param[in] animCharaChip_ 取得したキャラチップ
	void	SetAnimCharaChip(AnimationCharaChip* animCharaChip_);

	//!@brief スキルの画像名を取得
	//!@param[in] skillImageName_ 取得したスキル画像名
	void	SetSkillImageName(const std::string& skillImageName_);


public:
	//!@brief 中身のデータをすべてクリアする
	void	Clear();

	//!@brief 使用回数を設定
	void	SetUseNum(const int& useNum_);
	//!@brief 現在の使用回数を取得
	int		GetNowUseNum() const;
	//!@brief 使用回数があるかチェック
	//!@return skillTypeの指定回数以内ならtrue
	bool	CheckUseNum();
	//!@brief 使用回数をカウントする処理
	void	CountUseNum();

	//!@brief スキルIDからスキルの種類を決める
	void	CreateSkillType();

private:
	int							skillID;		//スキルID
	SkillType*					skillType;		//スキルの種類
	AnimationCharaChip*			animCharaChip;	//アニメーションキャラチップ
	std::string					skillImageName;	//スキルの画像名
	int							useNum;			//使用回数
};