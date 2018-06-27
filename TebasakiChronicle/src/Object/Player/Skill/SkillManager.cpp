#include "SkillManager.h"
#include "../src/Helper.h"
#include "SkillAttack/SkillAttack.h"


//----------------------------------------------------------------
//コンストラクタ
//----------------------------------------------------------------
SkillManager::SkillManager()
	: registFlag(false), createSkillFlag(false)
{
	for (int i = 0; i < 5; ++i)
	{
		skillDatas[i].Clear();
	}
}

//----------------------------------------------------------------
//デストラクタ
//----------------------------------------------------------------
SkillManager::~SkillManager()
{
	for (auto it : skillObj)
	{
		delete it;
	}
}


//!@brief SkillIDが同じかをチェック
//!@param[in] skillID_ 取得したスキルID
//!@return IDが同じならtrue
bool	SkillManager::CheckSkillID(const int& skillID_)
{
	//先に空かどうかをチェックし、空なら調べられない
	if (skillDatas.empty()) { return false; }

	for (auto it = skillDatas.begin(); it != skillDatas.end(); ++it)
	{
		if (it->GetSkillID() != skillID_)
		{
			return true;
		}
	}
	return false;
}


//!@brief SkillIDが0(存在しない)でないかをチェック
//!@param[in] skillID_ 取得したスキルID
//!@return IDが0ならtrue
bool	SkillManager::IsNonSkillID(const int& skillID_)
{
	if (skillID_ != 0)
	{
		return false;
	}
	return true;
}


//!@brief Skillを登録する
void	SkillManager::RegistSkill(const int& num)
{
	//対応したボタンにスキルDatasを渡す
	//スキルIDが同じかチェック
	if (skillDatas[skillNum - 1].GetSkillID() == skillDatas[num].GetSkillID())
	{
		skillDatas[num].Clear();
		//同じなら、ボタン5のスキルデータスキル番号のスキルに渡す
		skillDatas[num].SetSkillID(skillDatas[skillNum - 1].GetSkillID());
		skillDatas[num].SetSkillType(skillDatas[skillNum - 1].GetSkillType());
		skillDatas[num].SetSkillImageName(skillDatas[skillNum - 1].GetSkillImageName());
		skillDatas[num].SetAnimCharaChip(&skillDatas[skillNum - 1].GetAnimCharaChip());
		skillDatas[num].SetPressBtnNum(num);
		skillDatas[num].MoveGUIObjPos();
		skillDatas[skillNum - 1].Clear();
			
	}
	else
	{
		skillDatas[num].Clear();
		//前のデータを削除して、新しいスキルデータを渡す
		skillDatas[num].SetSkillID(skillDatas[skillNum - 1].GetSkillID());
		skillDatas[num].SetSkillType(skillDatas[skillNum - 1].GetSkillType());
		skillDatas[num].SetSkillImageName(skillDatas[skillNum - 1].GetSkillImageName());
		skillDatas[num].SetAnimCharaChip(&skillDatas[skillNum - 1].GetAnimCharaChip());
		skillDatas[num].SetPressBtnNum(num);
		skillDatas[num].MoveGUIObjPos();
		skillDatas[skillNum - 1].Clear();
	}
}

//!@brief SkillAndCharaChip型のデータを受け取る
//!@param[in] skill スキルデータ
//!@return 受け取れるデータなら(正常に受け取れたなら)true
bool	SkillManager::ReceiveSkillAndCharaChip(const Enemy::SkillAndCharaChip& skill)
{
	//SkillIDが0でないかをチェック
	if (IsNonSkillID(*skill.behaviorId))
	{
		return false;
	}

	skillDatas[skillNum - 1].Clear();	//クリア
	//スキルは一時的にボタン5に入る
	skillDatas[skillNum - 1].SetSkillID(*skill.behaviorId);
	skillDatas[skillNum - 1].SetSkillImageName(*skill.textureName);
	skillDatas[skillNum - 1].SetAnimCharaChip(skill.nowCharaChip);
	skillDatas[skillNum - 1].SetPressBtnNum(skillNum - 1);
	skillDatas[skillNum - 1].CreateGUIObject();
	skillDatas[skillNum - 1].CreateSkillType();
	return true;
}


//!@brief 更新処理
void	SkillManager::UpDate(GameObject& object)
{
	for (auto it = skillObj.begin(); it != skillObj.end();)
	{
		if ((*it) != nullptr)
		{
			if ((*it)->CheckSurvivalTime())
			{
				(*it)->UpDate(object);
				++it;
			}
			else
			{
				delete (*it);
				(*it) = nullptr;
				it = skillObj.erase(it);
			}
		}
	}
}


//!@brief 描画処理
void	SkillManager::Render()
{
	for (auto it = skillObj.begin(); it != skillObj.end(); ++it)
	{
		if ((*it) != nullptr)
		{
			(*it)->Render();
		}
	}
	//スキルUIの描画
	for (int i = 0; i < 5; ++i)
	{
		skillDatas[i].RenderUI();
	}
}



//!@brief 登録フラグの切り替え
//!@param[in] 登録フラグ registFlag
void	SkillManager::ChangeRegistFlag(bool registFlag_)
{
	registFlag = registFlag_;
}

//!@brief 現在の登録フラグの取得
//!@return 登録状態ならtrue
bool	SkillManager::CheckRegistFlag() const
{
	return registFlag;
}


//!@brief 現在の使用中フラグの取得
//!@return 使用中ならtrue
bool	SkillManager::CheckCreateSkillFlag() const
{
	return createSkillFlag;
}

//!@brief 指定したボタンのスキルが存在するかのチェック
//!@param[in] btn ボタン番号
//!@return 存在するならtrue
bool	SkillManager::CheckExistSkill(const int& btn)
{
	if (!skillDatas[btn].CheckUseNum())
	{
		return false;
	}
	return true;
}

//!@brief 生成したSkillTypeからSkillObjを作成
//!@brief 成功したらtrue
bool	SkillManager::CreateSkillObject(const int& btn,GameObject& obj)
{
	skillObj.emplace_back(new SkillObject(skillDatas[btn].GetSkillType(),obj,
		skillDatas[btn].GetSkillImageName(),skillDatas[btn].GetAnimCharaChip()));
	return true;
}


//!@brief 指定したスキルをクリアする
void	SkillManager::ClearSkill(const int& btn)
{
	skillDatas[btn].Clear();
}


//!@brief スキルを登録する
//!@param[in] btnNum ボタン番号
void	SkillManager::RegistSkillData(const int& btnNum)
{
	if (CheckRegistFlag())
	{
		if (skillDatas[skillNum - 1].GetSkillID() == 0) { return; }
		std::cout << "登録します" << std::endl;
		RegistSkill(btnNum);						//スキルを登録
		skillDatas[btnNum].CreateSkillType();		//スキルの種類を生成
		ChangeRegistFlag(false);					//登録モード終了
	}
}

//!@brief スキルを使用する
//!@param[in] btnNum ボタン番号
//!@param[in] obj ゲームオブジェクト
void	SkillManager::UseSkillData(const int& btnNum, GameObject& obj)
{
	if (skillDatas[btnNum].CheckUseNum())
	{
		if (!CheckRegistFlag())
		{
			CreateSkillObject(btnNum, obj);		//SkillObjを生成
			skillDatas[btnNum].CountUseNum();	//数をカウント

			std::cout << skillDatas[btnNum].GetNowUseNum() << std::endl;
			//スキルがなくなるため消す
			if (!skillDatas[btnNum].CheckUseNum()) { skillDatas[btnNum].Clear(); }
		}
	}
	else
	{
		if (skillDatas[btnNum].GetSkillID() != -1)
		{
			skillDatas[btnNum].Clear();
		}
	}
}


