#include "SkillObject.h"


//--------------------------------------------------------------------
//�R���X�g���N�^
//--------------------------------------------------------------------
SkillObject::SkillObject(GameObject& obj, const float& distance,
	const std::string& imageName, const AnimationCharaChip& animCharaChip)
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
	object.SetPos(K_Math::Vector3(obj.GetPos().x() + GetDir() * distance, obj.GetPos().y(), obj.GetPos().z()));


	object.SetImage("SkillImg", CST::LoadAndGetTexture("SkillImg", "data/image/" + imageName + ".png"), true);
	object.GetImage().CreateCharaChip(animCharaChip.chip, animCharaChip.chipSheetNum, animCharaChip.animSpd, animCharaChip.isAnimRoop);
	
	shape = CC::CreateBoxShape(16, 24, 1);
	cManager.CreateBaseCollisionData(shape, object.GetPos(), object.GetAngle(), true);
	cManager.CreateSubCollisionData(shape, CollisionMask::Non, CollisionMask::Non, object.GetPos());
	cManager.SetSubCollisionUserData(0, &object.GetStatus());

}

//-------------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------------
SkillObject::~SkillObject()
{
	CC::RemoveCollisionShape(&shape);
}


//�X�L���̌��ʏ���
void	SkillObject::SkillEffect()
{

}


//!@brief ������Ԃ�
//!@return -1.0f�Ȃ獶,1.0f�Ȃ�E
float	SkillObject::GetDir()
{
	if (object.GetDirection() == Status::Direction::Left)
	{
		return -1.0f;
	}
	return 1.0f;
}

//!@brief �X�V����
void	SkillObject::UpDate()
{
	object.GetImage().Animation();
	cManager.GetBaseCollisionObjectPosition() = object.GetPos();
}

//!@brief �`�揈��
void	SkillObject::Render()
{
	object.GetImage().ImageDraw3D(object.GetPos(), object.GetAngle(), object.GetScale(), object.GetDirection());
}