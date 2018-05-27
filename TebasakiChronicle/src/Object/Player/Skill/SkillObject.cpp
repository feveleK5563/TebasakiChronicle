#include "SkillObject.h"

//--------------------------------------------------------------------
//�R���X�g���N�^
//--------------------------------------------------------------------

//!@brief SkillType����U�镑���𐶐�
//!@brief SkillType �U�镑�����󂯎��
//!@brief obj �Q�[���I�u�W�F�N�g�̎Q��
SkillObject::SkillObject(std::shared_ptr<SkillType> skillType_,GameObject& obj,const std::string& imageName, const AnimationCharaChip& animCharaChip)
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
	
	object.SetPos(K_Math::Vector3(object.GetPos().x + GetDir() * skillType->GetAppearDist(), object.GetPos().y, object.GetPos().z));

	shape = CC::CreateBoxShape(16, 24, 1);
	continueCnt = 0;	//�v�����ԃJ�E���g

	//�e���|�����R���W��������
	tempColManager.CreateTemporaryCollision(shape, CollisionMask::Non, CollisionMask::Non,
		object.GetPos(), object.GetMoveVec(), object.GetDirection(), 1, 
		skillType->GetContinueTime(), object.GetMove().GetGravity(), false, false);

	//�A�j���[�V�����Z�b�g
	tempColManager.SetAnimationCharaChip(imageName, CST::GetTexture(imageName),
		animCharaChip.chip,animCharaChip.chipSheetNum, animCharaChip.animSpd, animCharaChip.isAnimRoop);
}

//-------------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------------
SkillObject::~SkillObject()
{
	
}




//!@brief �X�V����
void	SkillObject::UpDate()
{
	//�R���W�����X�V
	tempColManager.Update();

	//�X�L���̓���
	skillType->UpDate();
	
	continueCnt++;
}

//!@brief �`�揈��
void	SkillObject::Render()
{
	//�R���W�����`��
	tempColManager.Render();
}


//!@brief �U�镑�����Z�b�g����
//!@param[in] skillType_ �X�L���̂ӂ�܂�
void	SkillObject::SetSkillType(std::shared_ptr<SkillType> skillType_)
{
	skillType = skillType_;
}


//!@brief �������ԓ������`�F�b�N
//!@return �������ԓ��Ȃ�true
bool	SkillObject::CheckSurvivalTime()
{
	if (continueCnt > skillType->GetContinueTime())
	{
		return false;
	}
	return true;
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