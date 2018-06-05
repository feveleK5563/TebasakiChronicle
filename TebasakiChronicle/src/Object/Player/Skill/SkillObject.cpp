#include "SkillObject.h"

//--------------------------------------------------------------------
//コンストラクタ
//--------------------------------------------------------------------

//!@brief SkillTypeから振る舞いを生成
//!@brief SkillType 振る舞いを受け取る
//!@brief obj ゲームオブジェクトの参照
SkillObject::SkillObject(std::shared_ptr<SkillType> skillType_,GameObject& obj,const std::string& imageName, const AnimationCharaChip& animCharaChip)
	:skillType(skillType_)
{
	object.GetStatus().SetStatusData(
		Status::State::Active,
		obj.GetPos(),
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(1, 1, 1),
		obj.GetDirection(),
		skillType->GetAttackPoint(),
		0
	);
	
	object.SetPos(K_Math::Vector3(object.GetPos().x + GetDir() * skillType->GetAppearDist(), object.GetPos().y, object.GetPos().z));


	shape = CC::CreateBoxShape(16, 24, 1);
	continueCnt = 0;	//計測時間カウント
	oneFlag = true;		//1回のみ更新するかのフラグ
	upDateFlag = true;	//更新するかのフラグ

	//テンポラリコリジョン生成
	tempColManager.CreateTemporaryCollision(shape, CollisionMask::Non, CollisionMask::PlayerCollision ,
		object.GetPos(), 
		object.GetMoveVec(), object.GetDirection(), object.GetAttackPoint(),
		skillType->GetContinueTime(), object.GetMove().GetGravity(), false, false);

	//アニメーションセット
	tempColManager.SetAnimationCharaChip(CST::GetTexture(imageName),
		animCharaChip.chip,animCharaChip.chipSheetNum, animCharaChip.animSpd, animCharaChip.isAnimRoop);

	//スキルの動作の初期化
	skillType->BehaivorInit(tempColManager, object.GetStatus(), object.GetMove());
}

//-------------------------------------------------------------
//デストラクタ
//-------------------------------------------------------------
SkillObject::~SkillObject()
{
	//スキルの動作の終了
	skillType->BehaivorFinal(tempColManager, object.GetStatus(), object.GetMove());
}




//!@brief 更新処理
void	SkillObject::UpDate()
{
	//コリジョン更新
	tempColManager.Update();

	//スキルの動作
	skillType->Behaivor(tempColManager, object.GetStatus(), object.GetMove());
	skillType->UpDate(object);

	std::cout << "skillObj" << object.GetMove().GetMoveVec().y << std::endl;

	continueCnt++;

}

//!@brief 描画処理
void	SkillObject::Render()
{
	//コリジョン描画
	tempColManager.Render();
}


//!@brief 振る舞いをセットする
//!@param[in] skillType_ スキルのふるまい
void	SkillObject::SetSkillType(std::shared_ptr<SkillType> skillType_)
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



//!@brief	プレイヤーを移動させるための更新
//!@param[in] object プレイヤーのObject
void	SkillObject::PlayerUpDate(GameObject& object)
{
	//コリジョン更新
	tempColManager.Update();

	//スキルの動作
	skillType->Behaivor(tempColManager, object.GetStatus(), object.GetMove());

	if (OneProcess())
	{
		skillType->UpDate(object);
		if (oneFlag)
		{
			upDateFlag = false;
		}
	}
	continueCnt++;
}

//!@brief	1回処理を行うか指定
//!@param[in] oneFlag	1回の処理するかフラグ
//!@return	1回なら true それ以外なら false
bool	SkillObject::OneProcess()
{
	return upDateFlag;
}

//!@brief	1回だけ更新させるフラグのセット
//!@param[in] oneFlag	1回だけ更新するなら true
void	SkillObject::SetOneUpdateFlag(bool oneFlag_)
{
	oneFlag = oneFlag_;
}