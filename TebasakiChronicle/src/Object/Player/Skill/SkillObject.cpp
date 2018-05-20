#include "SkillObject.h"


//--------------------------------------------------------------------
//コンストラクタ
//--------------------------------------------------------------------

//!@brief SkillTypeから振る舞いを生成
//!@brief SkillType 振る舞いを受け取る
//!@brief obj ゲームオブジェクトの参照
SkillObject::SkillObject(SkillType* skillType_,GameObject& obj,const std::string& imageName, const AnimationCharaChip& animCharaChip)
	:skillType(skillType_)
{
	object.GetStatus().SetStatusData(
		Status::State::Active,
		obj.GetPos(),
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(1, 1, 1),
		obj.GetDirection(),
		1,
		0
	);
	
	object.SetPos(K_Math::Vector3(object.GetPos().x() + GetDir() * skillType->GetAppearDist(), object.GetPos().y(), object.GetPos().z()));

	object.SetImage(imageName, nullptr, true);
	object.GetImage().CreateCharaChip(animCharaChip.chip, animCharaChip.chipSheetNum, animCharaChip.animSpd, animCharaChip.isAnimRoop);

	shape = CC::CreateBoxShape(16, 24, 1);
	cManager.CreateBaseCollisionData(shape, object.GetPos(), object.GetAngle(), true);
	cManager.CreateSubCollisionData(shape, CollisionMask::Non, CollisionMask::Non, K_Math::Vector3(0,0,0));
	cManager.SetSubCollisionUserData(0, &object.GetStatus());

	continueCnt = 0;	//計測時間カウント

}

//-------------------------------------------------------------
//デストラクタ
//-------------------------------------------------------------
SkillObject::~SkillObject()
{
	CC::RemoveCollisionShape(&shape);
}




//!@brief 更新処理
void	SkillObject::UpDate()
{
	object.GetImage().Animation();
	//位置同期
	cManager.SetBaseCollisionObjectPosition(object.GetPos());
	//スキルの動作
	skillType->UpDate();
	
	continueCnt++;
}

//!@brief 描画処理
void	SkillObject::Render()
{
	object.GetImage().ImageDraw3D(object.GetPos(), object.GetAngle(), object.GetScale(), object.GetDirection());
}


//!@brief 振る舞いをセットする
//!@param[in] skillType_ スキルのふるまい
void	SkillObject::SetSkillType(SkillType* skillType_)
{
	skillType = skillType_;
}


//!@brief 生存時間内かをチェック
//!@return 生存時間内ならtrue
bool	SkillObject::CheckSurvivalTime()
{
	if (continueCnt > skillType->GetContinueTime())
	{
		return false;
	}
	return true;
}

//!@brief 向きを返す
//!@return -1.0fなら左,1.0fなら右
float	SkillObject::GetDir()
{
	if (object.GetDirection() == Status::Direction::Left)
	{
		return -1.0f;
	}
	return 1.0f;
}