#pragma once

#include "K_Graphics/ImageLoader.h"
#include "../src/BaseClass/ImageManager/AnimationCharaChip.h"
#include "SkillType.h"

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
	//!@brief スキルの出現位置を返す
	//!@return SkillAppearPosを返す
	K_Math::Vector3& GetSkillAppearPos();
	//!@brief スキルのキャラチップ
	AnimationCharaChip& GetAnimCharaChip();

	//!@brief スキルデータをセットする
	//!@param[in] skillID_ スキルID
	//!@param[in] skillType_ スキルの種類
	//!@param[in] spriteObj_ スプライトオブジェクト
	//!@param[in] animCharaChip_ アニメーションキャラチップ
	void	SetSkillData(	const int& skillID_,
							SkillType* skillType_,
							K_Graphics::SpriteObject* spriteObj_,
							AnimationCharaChip* animCharaChip_);

public:
	//!@brief スキルの種類のセット
	//!@param[in] skillType_ 取得したスキルの種類
	void	SetSkillType(SkillType* skillType_);
	//!@brief スキルIDのセット
	//!@brief[in] skillID_ 取得したスキルID
	void	SetSkillID(const int& skillID_);
	//!@brief スプライトオブジェクトのセット
	//!@param[in] spriteObj_ 取得したスプライト
	void	SetSpriteObj(K_Graphics::SpriteObject* spriteObj_);
	//!@brief アニメーションキャラチップ
	//!@param[in] animCharaChip_ 取得したキャラチップ
	void	SetAnimCharaChip(AnimationCharaChip* animCharaChip_);

	//!@brief スキルの画像名を取得
	//!@param[in] skillImageName_ 取得したスキル画像名
	void	SetSkillImageName(const std::string& skillImageName_);

	//!@brief 出現位置を取得
	//!@param[in] appearPos_ 取得した出現位置
	void	SetSkillAppearPos(const K_Math::Vector3& appearPos_);

public:
	//!@brief 中身のデータをすべてクリアする
	void	Clear();

	//!@brief スキルIDスキルのパラメータを決める
	void	DecideSkillParam();
	//!@brief 使用回数を設定
	void	SetUseNum(const int& useNum_);
	//!@brief 現在の使用回数を取得
	int		GetNowUseNum() const;
	//!@brief 使用回数があるかチェック
	//!@return 0以上ならtrue
	bool	CheckUseNum();
	//!@brief 使用回数を減らす処理
	void	CountDownUseNum();

	//!@brief 継続時間の取得
	//!@return 継続時間データ
	int		GetContinueTime() const;
	//!@brief 距離の取得
	//!@return 距離データ
	float	GetDistance() const;

private:
	int							skillID;		//スキルID
	SkillType*					skillType;		//スキルの種類
	K_Graphics::SpriteObject*	spriteObj;		//スプライト
	AnimationCharaChip*			animCharaChip;	//アニメーションキャラチップ

	std::string					skillImageName;	//スキルの画像名
	K_Math::Vector3				appearPos;		//出現位置
	int							useNum;			//使用回数
	int							continueTime;	//継続時間
	float						distance;		//距離
};