#include "SkillData.h"
#include "../src/Helper.h"

//----------------------------------------------------------------
//�R���X�g���N�^
//----------------------------------------------------------------
SkillData::SkillData()
{
	skillID = 0;
	Clear();
	skillIcon = nullptr;
	skillNumUI = nullptr;
}

//----------------------------------------------------------------
//�f�X�g���N�^
//----------------------------------------------------------------
SkillData::~SkillData()
{
	Clear();
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
	skillID = 0;				//�X�L��ID
	skillType = nullptr;		//�X�L���̎��
	animCharaChip = nullptr;	//�A�j���[�V�����L�����`�b�v
	skillImageName = "";		//�X�L���̉摜��
	useNum = 0;					//�g�p�񐔂�0
	pressBntNum = -1;			//�{�^���ԍ��Ȃ�

	Memory::SafeDelete(skillIcon);
	for (auto ui : registSkillUI)
	{
		Memory::SafeDelete(ui);
	}
	registSkillUI.clear();
	Memory::SafeDelete(skillNumUI);
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
	
	if (useNum <= 0)
	{
		return false;
	}
	return true;
}
//!@brief �g�p�񐔂��J�E���g���鏈��
void	SkillData::CountUseNum()
{
	useNum -= 1;
}



//!@brief �X�L��ID����X�L���̎�ނ����߂�
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
		//skillType = std::shared_ptr<SkillType>(new SkillAttack(skillID, 7, 30.0f, 60, 1));
		skillType = std::shared_ptr<SkillType>(new SkillMove(3, 100, 0.0f, 60, 0));	//��
		break;
	case 12:
		skillType = std::shared_ptr<SkillType>(new SkillAttack(skillID, 5, 30.0f, 60, 1));
		break;
	default:
		skillType = nullptr;
	}
	if (skillType == nullptr) { return; }
	useNum = skillType->GetMaxUseNum();
}

//!@brief �X�L����GUI�I�u�W�F�N�g�̐���
void	SkillData::CreateGUIObject()
{
	K_Math::Vector3	guiPos = K_Math::Vector3(1170, 610, 0);
	
	//�X�L��ID����A�C�R���摜�����߂�
	DecideSkillData();
	//�X�L���A�C�R��UI�̐���
	skillIcon = new GUIObject(skillIconImage, guiPos, K_Math::Box2D(0, 0, 64, 64));
	CreateRegistSkillUI(guiPos);
	
	//�X�L������UI�̐���
	skillNumUI = new GUIObject("ScreenUI/number2", guiPos + K_Math::Vector3(10, 10, 0), K_Math::Box2D(0, 0, 16, 16));
	skillNumUI->SetOffsetSrcPos(K_Math::Vector2(11, 0));
}

//!@brief GUI�I�u�W�F�N�g�̈ʒu�̈ړ�
void	SkillData::MoveGUIObjPos()
{
	K_Math::Vector3	 guiPos = K_Math::Vector3(1170, 610, 0);
	K_Math::Vector3	addVec[] =
	{
		K_Math::Vector3(0,64,0),
		K_Math::Vector3(-64,0,0),
		K_Math::Vector3(64,0,0),
		K_Math::Vector3(0,-64,0)
	};

	//�X�L��ID����A�C�R�������߂�
	DecideSkillData();
	skillIcon = new GUIObject(skillIconImage, guiPos + addVec[pressBntNum], K_Math::Box2D(0, 0, 64, 64));
	
	//�X�L�����̕\��UI�̍쐬
	skillNumUI = new GUIObject("ScreenUI/number2", guiPos + K_Math::Vector3(10, 10, 0), K_Math::Box2D(0, 0, 16, 16));
	skillNumUI->AddVec(addVec[pressBntNum]);
	skillNumUI->SetOffsetSrcPos(K_Math::Vector2(11, 0));
}

//!@brief �X�L��UI��`��
void	SkillData::RenderUI()
{
	//�o�^�̍ۂ�UI�\��
	for (auto ui : registSkillUI)
	{
		if (ui == nullptr) { return; }
		ui->UpDate();
		ui->Render();
	}
	
	//�X�L���A�C�R����UI
	if (skillIcon == nullptr) { return; }
	skillIcon->UpDate();
	skillIcon->Render();

	//�X�L������UI�̕\��
	if (skillNumUI == nullptr) { return; }
	skillNumUI->UpDate();
	std::string	text = std::to_string(GetNowUseNum());
	skillNumUI->RenderNumberImage(text.c_str());
}


//!@brief �����ꂽ�{�^���ԍ����擾
void	SkillData::SetPressBtnNum(int num)
{
	pressBntNum = num;
}


//!@brief �X�L��ID����f�[�^�����߂�
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
	default:
		skillIconImage = "skillIcon";
	}
}



//!@brief	�X�L���o�^�̍ۂ�UI�̍쐬
//!@param[in]	rerativePos	���Έʒu
void	SkillData::CreateRegistSkillUI(const K_Math::Vector3& rerativePos)
{
	K_Math::Vector3 srcBox[4] =
	{
		K_Math::Vector3(30,0,0),
		K_Math::Vector3(0,-30,0) ,
		K_Math::Vector3(-30,0,0),
		K_Math::Vector3(0,30,0)
	};
	float angle[4] = { 270,0,90,180 };
	int cnt = 0;
	for (int i = 0; i < 4; ++i)
	{
		registSkillUI.emplace_back(new GUIObject("ScreenUI/skillSelect2", rerativePos + srcBox[i], K_Math::Box2D(0, 0, 64, 64), 10, 3.0f));
	}
	for (auto ui : registSkillUI)
	{
		ui->SetAngle(K_Math::Vector3(0, 0, angle[cnt]));
		cnt++;
	}
}

