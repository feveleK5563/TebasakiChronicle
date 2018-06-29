#pragma once

#include "K_Graphics/ImageLoader.h"
#include "../src/BaseClass/ImageManager/AnimationCharaChip.h"
#include "SkillType.h"
#include "SkillMove/SkillMove.h"
#include "SkillAttack/SkillAttack.h"
#include <memory>
#include "../src/BaseClass/GUIObject/GUIObject.h"


class SkillType;
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
	std::shared_ptr<SkillType>  GetSkillType() const;
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
	void	SetSkillType(std::shared_ptr<SkillType> skillType_);
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

	//!@brief 押されたボタン番号を取得
	void	SetPressBtnNum(int num);

public:
	//-------------------------------------------------
	//!@brief	UI
	//!@brief スキルのGUIオブジェクトの生成
	void	CreateGUIObject();
	//!@brief GUIオブジェクトの位置の移動
	void	MoveGUIObjPos();
	//!@brief スキルUIを描画
	void	RenderUI();

private:
	//!@brief スキルIDからデータを決める
	void	DecideSkillData();

private:
	//!@brief	スキル登録の際のUIの作成
	//!@param[in]	rerativePos	相対位置
	void	CreateRegistSkillUI(const K_Math::Vector3& rerativePos);

private:
	int							skillID;		//スキルID
	std::shared_ptr<SkillType>	skillType;		//スキルの種類
	AnimationCharaChip*			animCharaChip;	//アニメーションキャラチップ
	std::string					skillImageName;	//スキルの画像名
	int							useNum;			//使用回数

	GUIObject*					skillIcon;		//スキルのUI
	GUIObject*					skillNumUI;		//スキル数のUI
	std::vector<GUIObject*>		registSkillUI;	//登録する際のスキルUI
	int							pressBntNum;	//押されたボタン番号
	std::string					skillIconImage;	//スキルIcon画像名
};
