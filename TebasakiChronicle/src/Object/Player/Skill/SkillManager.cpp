#include "SkillManager.h"
#include "../src/Helper.h"
#include "SkillSword\SkillSword.h"


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


//!@brief SkillAndCharaChip型のデータを受け取る
//!@param[in] skill スキルデータ
//!@return 受け取れるデータなら(正常に受け取れたなら)true
bool	SkillManager::ReceiveSkillAndCharaChip(const Enemy::SkillAndCharaChip& skill)
{
	//SkillIDが0でないかをチェック
	if (IsNonSkillID(*skill.skillId))
	{
		//return false;
	}

	//スキルは一時的にボタン5に入る
	skillDatas[skillNum - 1].SetSkillID(*skill.skillId);
	skillDatas[skillNum - 1].SetSkillImageName(*skill.textureName);
	skillDatas[skillNum - 1].SetAnimCharaChip(skill.nowCharaChip);


	std::cout << "スキルデータを受け取りました" << std::endl;
	return true;
}







//!@brief Skillを登録する
void	SkillManager::RegistSkill(const int& num)
{
	//対応したボタンにスキルDatasを渡す
	//そのボタンが押されたSkillDatasにデータがない(-1)
	if (skillDatas[num].GetSkillID() == -1)
	{
		//スキルIDが同じかチェック
		if (skillDatas[skillNum - 1].GetSkillID() == skillDatas[num].GetSkillID())
		{
			//同じなら、ボタン5のスキルデータスキル番号のスキルに渡す
			skillDatas[num].SetSkillID(skillDatas[skillNum - 1].GetSkillID());
			skillDatas[num].SetSkillType(&skillDatas[skillNum - 1].GetSkillType());
			skillDatas[num].SetSkillImageName(skillDatas[skillNum - 1].GetSkillImageName());
			skillDatas[num].SetAnimCharaChip(&skillDatas[skillNum - 1].GetAnimCharaChip());
			skillDatas[skillNum - 1].Clear();
		}
		else
		{
			skillDatas[num].Clear();
			//前のデータを削除して、新しいスキルデータを渡す
			skillDatas[num].SetSkillID(skillDatas[skillNum - 1].GetSkillID());
			skillDatas[num].SetSkillType(&skillDatas[skillNum - 1].GetSkillType());
			skillDatas[num].SetSkillImageName(skillDatas[skillNum - 1].GetSkillImageName());
			skillDatas[num].SetAnimCharaChip(&skillDatas[skillNum - 1].GetAnimCharaChip());
			skillDatas[skillNum - 1].Clear();
		}
	}
}

//!@brief Skillを使用する
//!@param[in] btnNum ボタン番号
//!@param[in] obj ゲームオブジェクトの参照
void	SkillManager::UseSkill(const int& btnNum,GameObject& obj)
{
	if (skillDatas[btnNum].CheckUseNum())
	{
		CreateSkillObject(btnNum,obj);
	}
}

//!@brief 使用するか登録するか判断し、それぞれの処理を行う
void	SkillManager::Process(const int& btnNum,GameObject& obj)
{
	createSkillFlag = false;	//常に使用しない

	//登録状態のとき
	if (CheckRegistFlag())
	{
		RegistSkill(btnNum);						//スキルを登録
		skillDatas[btnNum].CreateSkillType();		//スキルの種類を生成

		ChangeRegistFlag(false);					//登録モード終了
		std::cout << "スキルを" << btnNum << "に登録" << std::endl;
	}
	else   //ここのelseをはずすと登録と同時にスキル使用可能
	//スキルを存在するとき
	if (skillDatas[btnNum].CheckUseNum())
	{
		createSkillFlag = true;
		CreateSkillObject(btnNum,obj);	//SkillObjを生成

		skillDatas[btnNum].CountUseNum();	//数をカウント
		std::cout << "スキル:" << btnNum << "使いました" << std::endl;
	}
	else
	{
		if (skillDatas[btnNum].GetSkillID() != -1)
		{
			delete &skillDatas[btnNum].GetSkillType();
			skillDatas[btnNum].Clear();
		}

		createSkillFlag = false;
		std::cout << "スキルがありません" << std::endl;
	}
}




//!@brief 更新処理
void	SkillManager::UpDate()
{
	for (auto it = skillObj.begin(); it != skillObj.end();)
	{
		if ((*it) != nullptr)
		{
			if ((*it)->CheckSurvivalTime())
			{
				(*it)->UpDate();
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


//!@brief 生成したSkillTypeからSkillObjを作成
//!@brief 成功したらtrue
bool	SkillManager::CreateSkillObject(const int& btn,GameObject& obj)
{
	skillObj.emplace_back(new SkillObject(&skillDatas[btn].GetSkillType(),obj,
		skillDatas[btn].GetSkillImageName(),skillDatas[btn].GetAnimCharaChip()));
	return true;
}
