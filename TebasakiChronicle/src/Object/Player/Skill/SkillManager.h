#pragma once
#include <array>
#include "../src/Object/Player/Skill/SkillData.h"
#include "SkillObject.h"
#include "../src/Object/Enemy/Enemy.h"

//----------------------------------------------------------------
//スキルを管理する
//概要:スキルを管理する、プレイヤーがもつSkillの箱のようなもの
//製作者:日比野
//----------------------------------------------------------------
class SkillManager
{
public:
	SkillManager();
	~SkillManager();


	//!@brief SkillIDが同じかをチェック
	//!@param[in] skillID_ 取得したスキルID
	//!@return IDが同じならtrue
	bool	CheckSkillID(const int& skillID_);

	//!@brief Skillを生成するボタンに対応してスキルを出現させる
	//!@param[in] num 番号
	void	CreateSkill(const int& num);

	//!@brief SkillIDが0(存在しない)でないかをチェック
	//!@param[in] skillID_ 取得したスキルID
	//!@return IDが0ならtrue
	bool	IsNonSkillID(const int& skillID_);

	//!@brief SkillAndCharaChip型のデータを受け取る
	//!@param[in] skill スキルデータ
	//!@return 受け取れるデータなら(正常に受け取れたなら)true
	bool	ReceiveSkillAndCharaChip(const Enemy::SkillAndCharaChip& skill);

	//!@brief SkillIDによってスキル生成するものを変える
	//!@param[in] skillID_ スキルのID
	//!@return スキルの種類(派生クラス)
	SkillType*	CreateSkillType(const int& skillID_);

	//!@brief Skillを交換するのか使用するかのチェック
	//!@return スキルを交換するならtrue、使用するならfalse
	bool	CheckSkillChangeFlag();

	//!@brief Skillを登録する
	void	RegistSkill(const int& num);

	//!@brief 使用するか登録するか判断し、それぞれの処理を行う
	void	Process(const int& btnNum);

	//!@brief スキルを交換するかのフラグ切り替え
	//!@param[in] skillChangeFlag_ スキルチェンジフラグ
	void	ChangeSkillFlag(bool skillChangeFlag_);

	//!@brief 更新処理
	void	UpDate();
	//!@brief 描画処理
	void	Render();

private:
	//!@brief SkillIDに基づいた、SkillObjectを生成する
	void	Create();

private:
	static const int			skillNum = 5;	//スキル数
	std::array<SkillData, skillNum>	skillDatas;	//スキルデータ
	std::vector<SkillObject*>	skillObj;		//スキルオブジェクト
	bool						skillChangeFlag;//スキルを交換するかのフラグ
	std::vector<SkillType*>		skill;
};