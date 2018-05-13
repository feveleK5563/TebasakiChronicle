#include "SkillManager.h"
#include "../src/Helper.h"
#include "SkillSword\SkillSword.h"


//----------------------------------------------------------------
//コンストラクタ
//----------------------------------------------------------------
SkillManager::SkillManager()
	: skillChangeFlag(false)
{

}

//----------------------------------------------------------------
//デストラクタ
//----------------------------------------------------------------
SkillManager::~SkillManager()
{
	for (auto it : skillObj)
	{
		if (it != nullptr)
		{
			delete it;
			it = nullptr;
		}
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


//!@brief Skillを生成するボタンに対応してスキルを出現させる
//!@param[in] num 番号
void	SkillManager::CreateSkill(const int& num)
{
	//番号の種類のオブジェクトを生成
	//ここで、skllTypeに応じたものを生成

	//持っているスキルデータを生成する
	skill.emplace_back(CreateSkillType(skillDatas[num].GetSkillID()));
	
	skillObj.emplace_back(new SkillObject(skillDatas[num].GetSkillType(), skillDatas[num].GetAnimCharaChip()));

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
	skillDatas[skillNum - 1].SetSkillAppearPos(*skill.pos);

	std::cout << "スキルデータを受け取りました" << std::endl;
	std::cout << "受け取る前のSkillID:" << *skill.skillId << std::endl;
	std::cout << "受け取ったあとのSkillID:" << skillDatas[skillNum - 1].GetSkillID() << std::endl;
	return true;
}


//!@brief SkillIDによってスキル生成するものを変える
//!@param[in] SkillType スキルの種類
//!@return スキルの種類(派生クラス)
SkillType*	SkillManager::CreateSkillType(const int& skillID_)
{
	switch (skillID_) {
	case 0:
		return new SkillSword(10,3,K_Math::Vector3(0,0,0));
	case 2:
		//return new Walk();
	default:
		return nullptr;
	}
}


//!@brief Skillを交換するのか使用するかのチェック
//!@return スキルを交換するならtrue、使用するならfalse
bool	SkillManager::CheckSkillChangeFlag()
{
	if (!skillChangeFlag)
	{
		return false;
	}
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
			skillDatas[num].SetSkillAppearPos(skillDatas[skillNum - 1].GetSkillAppearPos());

		}
		else
		{
			//前のデータを削除して、新しいスキルデータを渡す
			skillDatas[num].SetSkillID(skillDatas[skillNum - 1].GetSkillID());
			skillDatas[num].SetSkillType(&skillDatas[skillNum - 1].GetSkillType());
			skillDatas[num].SetSkillImageName(skillDatas[skillNum - 1].GetSkillImageName());
			skillDatas[num].SetSkillAppearPos(skillDatas[skillNum - 1].GetSkillAppearPos());
		}
	}
}

//!@brief 使用するか登録するか判断し、それぞれの処理を行う
void	SkillManager::Process(const int& btnNum)
{
	if (CheckSkillChangeFlag())
	{
		RegistSkill(btnNum);
		std::cout << "スキルを" << btnNum << "に登録" << std::endl;
		ChangeSkillFlag(false);
	}
	else
	{
		CreateSkill(btnNum);
		std::cout << "スキルを" << btnNum << "使いました" << std::endl;
	}
}


//!@brief スキルを交換するかのフラグ切り替え
//!@param[in] skillChangeFlag_ スキルチェンジフラグ
void	SkillManager::ChangeSkillFlag(bool skillChangeFlag_)
{
	skillChangeFlag = skillChangeFlag_;
}


//!@brief 更新処理
void	SkillManager::UpDate()
{
	for (auto it = skill.begin(); it != skill.end(); ++it)
	{
		if ((*it) != nullptr)
		{
			(*it)->UpDate();
		}
	}
	for (auto it = skillObj.begin(); it != skillObj.end();)
	{
		if ((*it) != nullptr)
		{
			(*it)->UpDate();
			//時間が来たらvectorから排除
			if ((*it)->CheckContinueTime())
			{
				delete (*it);
				(*it) = nullptr;
				it = skillObj.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}


//!@brief 描画処理
void	SkillManager::Render()
{
	for (auto it = skill.begin(); it != skill.end(); ++it)
	{
		if ((*it) != nullptr)
		{
			(*it)->Render();
		}
	}
	for (auto it = skillObj.begin(); it != skillObj.end(); ++it)
	{
		if ((*it) != nullptr)
		{
			(*it)->Render();
		}
	}
}

//private:

//!@brief SkillIDに基づいた、SkillObjectを生成する
void	SkillManager::Create()
{

}