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


	//!@brief SkillIDが0(存在しない)でないかをチェック
	//!@param[in] skillID_ 取得したスキルID
	//!@return IDが0ならtrue
	bool	IsNonSkillID(const int& skillID_);

	//!@brief SkillAndCharaChip型のデータを受け取る
	//!@param[in] skill スキルデータ
	//!@return 受け取れるデータなら(正常に受け取れたなら)true
	bool	ReceiveSkillAndCharaChip(const Enemy::SkillAndCharaChip& skill);

	
	//!@brief Skillを登録する
	//!@param[in] btnNum ボタン番号
	void	RegistSkill(const int& btnNum);
	//!@brief Skillを使用する
	//!@param[in] btnNum ボタン番号
	//!@param[in] obj オブジェクトの参照
	void	UseSkill(const int& btnNum,GameObject& obj);

	//!@brief 使用するか登録するか判断し、それぞれの処理を行う
	void	Process(const int& btnNumconst,GameObject& obj);



	//!@brief 更新処理
	void	UpDate();
	//!@brief 描画処理
	void	Render();
	
public:
	//!@brief 登録フラグの切り替え
	//!@param[in] registFlag_ 登録フラグ
	void	ChangeRegistFlag(bool registFlag_);
	//!@brief 現在の登録フラグの取得
	//!@return 登録状態ならtrue
	bool	CheckRegistFlag() const;

	//!@brief 現在の使用中フラグの取得
	//!@return 使用中ならtrue
	bool	CheckCreateSkillFlag() const;


private:
	//!@brief 生成したSkillTypeからSkillObjを作成
	//!@brief btn ボタン番号
	//!@brief 成功したらtrue
	bool	CreateSkillObject(const int& btn,GameObject& obj);

private:
	static const int			skillNum = 5;	//スキル数
	std::array<SkillData, skillNum>	skillDatas;	//スキルデータ
	std::vector<SkillObject*>		skillObj;	//スキルオブジェクト
	bool						registFlag;		//登録フラグ
	bool						createSkillFlag;//使用中フラグ
};