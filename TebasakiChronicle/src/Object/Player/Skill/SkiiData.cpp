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


//!@brief �X�L���̏o���ʒu��Ԃ�
//!@return SkillAppearPos��Ԃ�
K_Math::Vector3& SkillData::GetSkillAppearPos()
{
	return appearPos;
}

//!@brief �X�L���̃L�����`�b�v
AnimationCharaChip& SkillData::GetAnimCharaChip()
{
	return *animCharaChip;
}


//!@brief �X�L���f�[�^���Z�b�g����
//!@param[in] skillID_ �X�L��ID
//!@param[in] skillType_ �X�L���̎��
//!@param[in] spriteObj_ �X�v���C�g�I�u�W�F�N�g
//!@param[in] animCharaChip_ �A�j���[�V�����L�����`�b�v
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

//!@brief �X�v���C�g�I�u�W�F�N�g�̃Z�b�g
//!@param[in] spriteObj_ �擾�����X�v���C�g
void	SkillData::SetSpriteObj(K_Graphics::SpriteObject* spriteObj_)
{
	spriteObj = spriteObj_;
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

//!@brief �o���ʒu���擾
//!@param[in] appearPos_ �擾�����o���ʒu
void	SkillData::SetSkillAppearPos(const K_Math::Vector3& appearPos_)
{
	appearPos = appearPos_;
}

//!@brief ���g�̃f�[�^�����ׂăN���A����
void	SkillData::Clear()
{
	skillID = -1;				//�X�L��ID
	skillType = nullptr;		//�X�L���̎��
	spriteObj = nullptr;		//�X�v���C�g
	animCharaChip = nullptr;	//�A�j���[�V�����L�����`�b�v

	skillImageName = "";					//�X�L���̉摜��
	appearPos = K_Math::Vector3(0,0,0);		//�o���ʒu
	
	useNum = 0;			//�g�p�񐔂�0
	continueTime = 0;
	distance = 0;
}


//!@brief �g�p�񐔂��X�L��ID�Ō��߂�
void	SkillData::DecideSkillParam()
{
	switch (skillID) {
	case 0:
		useNum = 10;			//�g�p��10��
		continueTime = 120;		//�p������120�t���[��
		distance = 30;			//�v���C���[����̋���30
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
//!@brief �g�p�񐔂�0�ȏォ�̃`�F�b�N
bool	SkillData::CheckUseNum()
{
	if (useNum <= 0)
	{
		return false;
	}
	return true;
}
//!@brief �g�p�񐔂����炷����
void	SkillData::CountDownUseNum()
{
	useNum--;
}


//!@brief �p�����Ԃ̎擾
//!@return �p�����ԃf�[�^
int		SkillData::GetContinueTime() const
{
	return continueTime;
}

//!@brief �����̎擾
//!@return �����f�[�^
float	SkillData::GetDistance() const 
{
	return distance;
}