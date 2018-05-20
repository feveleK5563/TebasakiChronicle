#include "SkillData.h"


//----------------------------------------------------------------
//�R���X�g���N�^
//----------------------------------------------------------------
SkillData::SkillData()
{
	skillID = -1;
	Clear();
}

//----------------------------------------------------------------
//�f�X�g���N�^
//----------------------------------------------------------------
SkillData::~SkillData()
{

}


//!@brief �ێ����Ă���X�L��ID��Ԃ�
//!@return skillID��Ԃ�
int		SkillData::GetSkillID()
{
	return skillID;
}


//!@brief �X�L���̎�ނ�Ԃ�
//!@return SkillType��Ԃ�
SkillType& SkillData::GetSkillType() const
{
	return *skillType;
}

//!@brief �X�L���̉摜����Ԃ�
//!@return SkillImageName��Ԃ�
std::string& SkillData::GetSkillImageName()
{
	return skillImageName;
}



//!@brief �X�L���̃L�����`�b�v
AnimationCharaChip& SkillData::GetAnimCharaChip()
{
	return *animCharaChip;
}


//!@brief �X�L���f�[�^���Z�b�g����
//!@param[in] skillID_ �X�L��ID
//!@param[in] skillType_ �X�L���̎��
//!@param[in] animCharaChip_ �A�j���[�V�����L�����`�b�v
void	SkillData::SetSkillData(const int& skillID_,
	AnimationCharaChip* animCharaChip_)
{
	SetSkillID(skillID_);
	SetAnimCharaChip(animCharaChip_);
}




//!@brief �X�L���̎�ނ̃Z�b�g
//!@param[in] skillType_ �擾�����X�L���̎��
void	SkillData::SetSkillType(SkillType* skillType_)
{
	skillType = skillType_;
}

//!@brief �X�L��ID�̃Z�b�g
//!@brief[in] skillID_ �擾�����X�L��ID
void	SkillData::SetSkillID(const int& skillID_)
{
	skillID = skillID_;
}


//!@brief �A�j���[�V�����L�����`�b�v
//!@param[in] animCharaChip_ �擾�����L�����`�b�v
void	SkillData::SetAnimCharaChip(AnimationCharaChip* animCharaChip_)
{
	animCharaChip = animCharaChip_;
}

//!@brief �X�L���̉摜�����擾
//!@param[in] skillImageName_ �擾�����X�L���摜��
void	SkillData::SetSkillImageName(const std::string& skillImageName_)
{
	skillImageName = skillImageName_;
}


//!@brief ���g�̃f�[�^�����ׂăN���A����
void	SkillData::Clear()
{
	skillID = -1;				//�X�L��ID
	skillType = nullptr;		//�X�L���̎��
	animCharaChip = nullptr;	//�A�j���[�V�����L�����`�b�v
	skillImageName = "";		//�X�L���̉摜��
	useNum = 0;					//�g�p�񐔂�0

}



//!@brief �g�p�񐔂�ݒ�
void	SkillData::SetUseNum(const int& useNum_)
{
	useNum = useNum_;
}
//!@brief ���݂̎g�p�񐔂��擾
int		SkillData::GetNowUseNum() const
{
	return useNum;
}
//!@brief �g�p�񐔂��w��񐔈ȏォ�̃`�F�b�N
bool	SkillData::CheckUseNum()
{
	if (skillType == nullptr) { return false; }
	if (useNum >= skillType->GetMaxUseNum())
	{
		return false;
	}
	return true;
}
//!@brief �g�p�񐔂��J�E���g���鏈��
void	SkillData::CountUseNum()
{
	useNum++;
}



//!@brief �X�L��ID����X�L���̎�ނ����߂�
void	SkillData::CreateSkillType()
{
	switch (skillID) {
	case 0:
		skillType = new SkillSword(10, 30.0f, 120);
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		skillType = nullptr;
	}
}