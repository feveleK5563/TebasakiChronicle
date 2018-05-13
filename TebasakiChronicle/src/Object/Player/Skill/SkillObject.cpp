#include "SkillObject.h"


//----------------------------------------------------------------
//コンストラクタ
//----------------------------------------------------------------
SkillObject::SkillObject(const SkillType& skillType_, const AnimationCharaChip& animCharaChip)
{
	object.GetStatus().SetStatusData(
		Status::State::Active,
		K_Math::Vector3(0,0,0),
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(1, 1, 1),
		Status::Direction::Right,
		1,
		0
	);


	continueTime = 180;

	object.SetImage("SkillImg", CST::LoadAndGetTexture("SkillImg", "data/image/resource2.png"), true);
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 0, 32, 48), 5, 6, true);

	shape = CC::CreateBoxShape(16, 24, 1);

	cManager.CreateBaseCollisionData(shape, object.GetPos(), object.GetAngle(), true);
	cManager.CreateSubCollisionData(shape, CollisionMask::Non, CollisionMask::Non, object.GetPos());

	cManager.SetSubCollisionUserData(0, &object.GetStatus());
}

//-------------------------------------------------------------
//デストラクタ
//-------------------------------------------------------------
SkillObject::~SkillObject()
{
	CC::RemoveCollisionShape(&shape);
}


//スキルの効果処理
void	SkillObject::SkillEffect()
{

}

//!@brief SkillObject自身が消えるかの判断
//!@return 消える時間が来たらtrue
bool	SkillObject::CheckContinueTime()
{
	if (continueTime <= 0)
	{
		return true;
	}
	return false;
}

//!@brief 更新処理
void	SkillObject::UpDate()
{
	object.GetImage().Animation();
	continueTime--;
}

//!@brief 描画処理
void	SkillObject::Render()
{
	object.GetImage().ImageDraw3D(object.GetPos(), object.GetAngle(), object.GetScale(), object.GetDirection());
}