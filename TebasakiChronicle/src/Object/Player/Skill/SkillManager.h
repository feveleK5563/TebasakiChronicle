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

private:
	//!@brief SkillIDが同じかをチェック
	//!@param[in] skillID_ 取得したスキルID
	//!@return IDが同じならtrue
	bool	CheckSkillID(const int& skillID_);


	//!@brief SkillIDが0(存在しない)でないかをチェック
	//!@param[in] skillID_ 取得したスキルID
	//!@return IDが0ならtrue
	bool	IsNonSkillID(const int& skillID_);

	//!@brief Skillを登録する
	//!@param[in] btnNum ボタン番号
	void	RegistSkill(const int& btnNum);

public:
	//!@brief SkillAndCharaChip型のデータを受け取る
	//!@param[in] skill スキルデータ
	//!@return 受け取れるデータなら(正常に受け取れたなら)true
	bool	ReceiveSkillAndCharaChip(const Enemy::SkillAndCharaChip& skill);

	//!@brief 更新処理
	void	UpDate(GameObject& object);
	//!@brief 描画処理
	void	Render();
	
	//!@brief 登録フラグの切り替え
	//!@param[in] registFlag_ 登録フラグ
	void	ChangeRegistFlag(bool registFlag_);
	//!@brief 現在の登録フラグの取得
	//!@return 登録状態ならtrue
	bool	CheckRegistFlag() const;

	//!@brief 現在の使用中フラグの取得
	//!@return 使用中ならtrue
	bool	CheckCreateSkillFlag() const;

	//!@brief 指定したボタンのスキルが存在するかのチェック
	//!@param[in] btn ボタン番号
	//!@return 存在するならtrue
	bool	CheckExistSkill(const int& btn);

public:
	//!@brief 生成したSkillTypeからSkillObjを作成
	//!@brief btn ボタン番号
	//!@brief 成功したらtrue
	bool	CreateSkillObject(const int& btn,GameObject& obj);

	//!@brief 指定したスキルをクリアする
	void	ClearSkill(const int& btn);

	//!@brief スキルを登録する
	//!@param[in] btnNum ボタン番号
	void	RegistSkillData(const int& btnNum);
	//!@brief スキルを使用する
	//!@param[in] btnNum ボタン番号
	//!@param[in] obj ゲームオブジェクト
	void	UseSkillData(const int& btnNum, GameObject& obj);

private:
	static const int			skillNum = 5;	//スキル数
	std::array<SkillData, skillNum>	skillDatas;	//スキルデータ
	std::vector<SkillObject*>		skillObj;	//スキルオブジェクト
	bool						registFlag;		//登録フラグ
	bool						createSkillFlag;//使用中フラグ

};