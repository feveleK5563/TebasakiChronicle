#include "SkillData.h"


//----------------------------------------------------------------
//コンストラクタ
//----------------------------------------------------------------
SkillData::SkillData()
{
	skillID = -1;
	Clear();
	guiObj = nullptr;
}

//----------------------------------------------------------------
//デストラクタ
//----------------------------------------------------------------
SkillData::~SkillData()
{
	if (guiObj != nullptr)
	{
		delete guiObj;
		guiObj = nullptr;
	}
}


//!@brief 保持しているスキルIDを返す
//!@return skillIDを返す
int		SkillData::GetSkillID()
{
	return skillID;
}


//!@brief スキルの種類を返す
//!@return SkillTypeを返す
std::shared_ptr<SkillType>  SkillData::GetSkillType() const
{
	return skillType;
}

//!@brief スキルの画像名を返す
//!@return SkillImageNameを返す
std::string& SkillData::GetSkillImageName()
{
	return skillImageName;
}



//!@brief スキルのキャラチップ
AnimationCharaChip& SkillData::GetAnimCharaChip()
{
	return *animCharaChip;
}


//!@brief スキルデータをセットする
//!@param[in] skillID_ スキルID
//!@param[in] skillType_ スキルの種類
//!@param[in] animCharaChip_ アニメーションキャラチップ
void	SkillData::SetSkillData(const int& skillID_,
	AnimationCharaChip* animCharaChip_)
{
	SetSkillID(skillID_);
	SetAnimCharaChip(animCharaChip_);
}




//!@brief スキルの種類のセット
//!@param[in] skillType_ 取得したスキルの種類
void	SkillData::SetSkillType(std::shared_ptr<SkillType> skillType_)
{
	skillType = skillType_;
}

//!@brief スキルIDのセット
//!@brief[in] skillID_ 取得したスキルID
void	SkillData::SetSkillID(const int& skillID_)
{
	skillID = skillID_;
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


//!@brief 中身のデータをすべてクリアする
void	SkillData::Clear()
{
	skillID = -1;				//スキルID
	skillType = nullptr;		//スキルの種類
	animCharaChip = nullptr;	//アニメーションキャラチップ
	skillImageName = "";		//スキルの画像名
	useNum = 0;					//使用回数を0
	pressBntNum = -1;

	if (guiObj != nullptr)
	{
		delete guiObj;
		guiObj = nullptr;
	}
}



//!@brief 使用回数を設定
void	SkillData::SetUseNum(const int& useNum_)
{
	useNum = useNum_;
}
//!@brief 現在の使用回数を取得
int		SkillData::GetNowUseNum() const
{
	return useNum;
}
//!@brief 使用回数が指定回数以上かのチェック
bool	SkillData::CheckUseNum()
{
	if (skillType == nullptr) { return false; }
	if (useNum >= skillType->GetMaxUseNum())
	{
		return false;
	}
	return true;
}
//!@brief 使用回数をカウントする処理
void	SkillData::CountUseNum()
{
	useNum++;
}



//!@brief スキルIDからスキルの種類を決める
void	SkillData::CreateSkillType()
{
	switch (skillID) {
	case 0:
		skillType = std::shared_ptr<SkillType>(new SkillMove(skillID, 8, 0.0f, 60, 0));
		break;
	case 1:
		skillType = std::shared_ptr<SkillType>(new SkillMove(skillID, 5, 0.0f, 60, 0));
		break;
	case 2:
		skillType = std::shared_ptr<SkillType>(new SkillMove(skillID, 5, 0.0f, 60, 0));
		break;
	case 3:
		skillType = std::shared_ptr<SkillType>(new SkillMove(skillID, 10, 0.0f, 60, 0));
		break;
	case 4:
		skillType = std::shared_ptr<SkillType>(new SkillAttack(skillID, 7, 30.0f, 60, 1));
		break;
	case 5:
		skillType = std::shared_ptr<SkillType>(new SkillMove(skillID, 7, 0.0f, 60, 0));
		break;
	case 6:
		skillType = std::shared_ptr<SkillType>(new SkillMove(skillID, 7, 0.0f, 60, 0));
		break;
	case 7:
		skillType = std::shared_ptr<SkillType>(new SkillMove(skillID, 5, 0.0f, 60, 0));
		break;
	case 8:
		skillType = std::shared_ptr<SkillType>(new SkillMove(skillID, 5, 0.0f, 60, 0));
		break;
	case 9:
		skillType = std::shared_ptr<SkillType>(new SkillMove(skillID, 5, 0.0f, 60, 0));
		break;
	case 10:
		skillType = std::shared_ptr<SkillType>(new SkillMove(skillID, 5, 0.0f, 60, 0));
		break;
	case 11:
		skillType = std::shared_ptr<SkillType>(new SkillAttack(skillID, 7, 30.0f, 60, 1));
		break;
	case 12:
		skillType = std::shared_ptr<SkillType>(new SkillAttack(skillID, 5, 30.0f, 60, 1));
		break;
	default:
		skillType = nullptr;
	}
}

//!@brief スキルのGUIオブジェクトの生成
void	SkillData::CreateGUIObject()
{
	K_Math::Vector3	guiPos;
	switch (pressBntNum) {
	case 0: guiPos = K_Math::Vector3(1000, 500, 0);	break;
	case 1:	guiPos = K_Math::Vector3(1000, 500, 0);	break;
	case 2:	guiPos = K_Math::Vector3(1000, 500, 0);	break;
	case 3:	guiPos = K_Math::Vector3(1000, 500, 0);	break;
	case 4: guiPos = K_Math::Vector3(1170, 610, 0);	break;
	}
	DecideSkillData();
	guiObj = new GUIObject(skillIconImage, guiPos, K_Math::Box2D(0, 0, 64, 64));
}

//!@brief GUIオブジェクトの位置の移動
void	SkillData::MoveGUIObjPos()
{
	K_Math::Vector3	 guiPos = K_Math::Vector3(1170, 610, 0);
	
	DecideSkillData();
	guiObj = new GUIObject(skillIconImage, guiPos, K_Math::Box2D(0, 0, 64, 64));
	
	switch (pressBntNum) {
	case 0: guiObj->AddVec(K_Math::Vector3(0, 64, 0));	break;
	case 1:	guiObj->AddVec(K_Math::Vector3(-64, 0, 0));	break;
	case 2: guiObj->AddVec(K_Math::Vector3(64, 0, 0));	break;
	case 3:	guiObj->AddVec(K_Math::Vector3(0, -64, 0));	break;
	case 4:	guiObj->AddVec(K_Math::Vector3(0, 0, 0));	break;
	}
}

//!@brief スキルUIを描画
void	SkillData::RenderUI()
{
	if (guiObj == nullptr) { return; }
	guiObj->UpDate();
	guiObj->Render();
}


//!@brief 押されたボタン番号を取得
void	SkillData::SetPressBtnNum(int num)
{
	pressBntNum = num;
}


//!@brief スキルIDからデータを決める
void	SkillData::DecideSkillData()
{
	switch (skillID) {
	case 0:
		skillIconImage = "skillIcon";
		break;
	case 1:
		skillIconImage = "skillIcon";
		break;
	case 2:
		skillIconImage = "skillIcon";
		break;
	case 3:
		skillIconImage = "skillIcon";
		break;
	case 4:
		skillIconImage = "skillIcon";
		break;
	}
}