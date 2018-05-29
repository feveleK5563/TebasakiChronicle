#include "SkillData.h"


//----------------------------------------------------------------
//�R���X�g���N�^
//----------------------------------------------------------------
SkillData::SkillData()
{
	skillID = -1;
	Clear();
	guiObj = nullptr;
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
std::shared_ptr<SkillType>  SkillData::GetSkillType() const
{
	return skillType;
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
void	SkillData::SetSkillType(std::shared_ptr<SkillType> skillType_)
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
	pressBntNum = -1;

	if (guiObj != nullptr)
	{
		delete guiObj;
		guiObj = nullptr;
		std::cout << "GUI�I�u�W�F�N�g���폜" << std::endl;
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
		skillType = std::shared_ptr<SkillType>(new SkillSword(0,10, 50.0f, 120,1));
		break;
	case 1:
		skillType = std::shared_ptr<SkillType>(new SkillSword(1, 5, 30.0f, 60, 1));
		break;
	case 2:
		skillType = std::shared_ptr<SkillType>(new SkillSword(2, 5, 30.0f, 60, 1));
		break;
	case 3:
		skillType = std::shared_ptr<SkillType>(new SkillSword(3, 5, 30.0f, 60, 1));
		break;
	case 4:
		skillType = std::shared_ptr<SkillType>(new SkillSword(4, 7, 30.0f, 60, 1));
		break;
	default:
		skillType = nullptr;
	}
}

//!@brief �X�L����GUI�I�u�W�F�N�g�̐���
void	SkillData::CreateGUIObject()
{
	K_Math::Vector3	guiPos;
	switch (pressBntNum) {
	case 0: guiPos = K_Math::Vector3(200, -100, -10);	break;
	case 1:	guiPos = K_Math::Vector3(170, -130, -10);	break;
	case 2:	guiPos = K_Math::Vector3(230, -130, -10);	break;
	case 3:	guiPos = K_Math::Vector3(200, -160, -10);	break;
	case 4: guiPos = K_Math::Vector3(200, -130, -10);	break;
	}
	std::cout << "GUI�I�u�W�F�N�g�𐶐�" << std::endl;
	guiObj = new GUIObject("target", guiPos, K_Math::Box2D(0, 0, 32, 32));
}

//!@brief GUI�I�u�W�F�N�g�̈ʒu�̈ړ�
void	SkillData::MoveGUIObjPos()
{
	K_Math::Vector3	guiPos;
	switch (pressBntNum) {
	case 0: guiPos = K_Math::Vector3(200, -100, -10);	break;
	case 1:	guiPos = K_Math::Vector3(170, -130, -10);	break;
	case 2:	guiPos = K_Math::Vector3(230, -130, -10);	break;
	case 3:	guiPos = K_Math::Vector3(200, -160, -10);	break;
	case 4: guiPos = K_Math::Vector3(200, -130, -10);	break;
	}
	std::cout << "GUI�I�u�W�F�N�g�𐶐�" << std::endl;
	guiObj = new GUIObject("target", guiPos, K_Math::Box2D(0, 0, 32, 32));
}

//!@brief �X�L��UI��`��
void	SkillData::RenderUI()
{
	if (guiObj == nullptr) { return; }
	guiObj->UpDate();
	guiObj->Render();
}


//!@brief �����ꂽ�{�^���ԍ����擾
void	SkillData::SetPressBtnNum(int num)
{
	pressBntNum = num;
}