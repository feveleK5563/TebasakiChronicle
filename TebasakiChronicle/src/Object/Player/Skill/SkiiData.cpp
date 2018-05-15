#include "SkillData.h"


//----------------------------------------------------------------
//コンストラクタ
//----------------------------------------------------------------
SkillData::SkillData()
{
	skillID = -1;
	Clear();
}

//----------------------------------------------------------------
//デストラクタ
//----------------------------------------------------------------
SkillData::~SkillData()
{

}


//!@brief 保持しているスキルIDを返す
//!@return skillIDを返す
int		SkillData::GetSkillID()
{
	return skillID;
}


//!@brief スキルの種類を返す
//!@return SkillTypeを返す
SkillType& SkillData::GetSkillType() const
{
	return *skillType;
}

//!@brief スキルの画像名を返す
//!@return SkillImageNameを返す
std::string& SkillData::GetSkillImageName()
{
	return skillImageName;
}


//!@brief スキルの出現位置を返す
//!@return SkillAppearPosを返す
K_Math::Vector3& SkillData::GetSkillAppearPos()
{
	return appearPos;
}

//!@brief スキルのキャラチップ
AnimationCharaChip& SkillData::GetAnimCharaChip()
{
	return *animCharaChip;
}


//!@brief スキルデータをセットする
//!@param[in] skillID_ スキルID
//!@param[in] skillType_ スキルの種類
//!@param[in] spriteObj_ スプライトオブジェクト
//!@param[in] animCharaChip_ アニメーションキャラチップ
void	SkillData::SetSkillData(const int& skillID_,
	SkillType* skillType_,
	K_Graphics::SpriteObject* spriteObj_,
	AnimationCharaChip* animCharaChip_)
{
	SetSkillID(skillID_);
	SetSkillType(skillType_);
	SetSpriteObj(spriteObj_);
	SetAnimCharaChip(animCharaChip_);
}




//!@brief スキルの種類のセット
//!@param[in] skillType_ 取得したスキルの種類
void	SkillData::SetSkillType(SkillType* skillType_)
{
	skillType = skillType_;
}

//!@brief スキルIDのセット
//!@brief[in] skillID_ 取得したスキルID
void	SkillData::SetSkillID(const int& skillID_)
{
	skillID = skillID_;
}

//!@brief スプライトオブジェクトのセット
//!@param[in] spriteObj_ 取得したスプライト
void	SkillData::SetSpriteObj(K_Graphics::SpriteObject* spriteObj_)
{
	spriteObj = spriteObj_;
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

//!@brief 出現位置を取得
//!@param[in] appearPos_ 取得した出現位置
void	SkillData::SetSkillAppearPos(const K_Math::Vector3& appearPos_)
{
	appearPos = appearPos_;
}

//!@brief 中身のデータをすべてクリアする
void	SkillData::Clear()
{
	skillID = -1;				//スキルID
	skillType = nullptr;		//スキルの種類
	spriteObj = nullptr;		//スプライト
	animCharaChip = nullptr;	//アニメーションキャラチップ

	skillImageName = "";					//スキルの画像名
	appearPos = K_Math::Vector3(0,0,0);		//出現位置
	
	useNum = 0;			//使用回数を0
	continueTime = 0;
	distance = 0;
}


//!@brief 使用回数をスキルIDで決める
void	SkillData::DecideSkillParam()
{
	switch (skillID) {
	case 0:
		useNum = 10;			//使用回数10回
		continueTime = 120;		//継続時間120フレーム
		distance = 30;			//プレイヤーからの距離30
		break;
	case 1:
		useNum = 7;
		continueTime = 60;
		distance = 50;
		break;
	default:
		useNum = 0;
		continueTime = 0;
		distance = 0;
		break;
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
//!@brief 使用回数が0以上かのチェック
bool	SkillData::CheckUseNum()
{
	if (useNum <= 0)
	{
		return false;
	}
	return true;
}
//!@brief 使用回数を減らす処理
void	SkillData::CountDownUseNum()
{
	useNum--;
}


//!@brief 継続時間の取得
//!@return 継続時間データ
int		SkillData::GetContinueTime() const
{
	return continueTime;
}

//!@brief 距離の取得
//!@return 距離データ
float	SkillData::GetDistance() const 
{
	return distance;
}