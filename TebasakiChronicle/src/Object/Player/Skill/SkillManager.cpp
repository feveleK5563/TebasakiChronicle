#include "SkillManager.h"
#include "../src/Helper.h"
#include "SkillSword\SkillSword.h"


//----------------------------------------------------------------
//�R���X�g���N�^
//----------------------------------------------------------------
SkillManager::SkillManager()
	: registFlag(false), createSkillFlag(false)
{
	for (int i = 0; i < 5; ++i)
	{
		skillDatas[i].Clear();
	}
}

//----------------------------------------------------------------
//�f�X�g���N�^
//----------------------------------------------------------------
SkillManager::~SkillManager()
{
	
}


//!@brief SkillID�����������`�F�b�N
//!@param[in] skillID_ �擾�����X�L��ID
//!@return ID�������Ȃ�true
bool	SkillManager::CheckSkillID(const int& skillID_)
{
	//��ɋ󂩂ǂ������`�F�b�N���A��Ȃ璲�ׂ��Ȃ�
	if (skillDatas.empty()) { return false; }

	for (auto it = skillDatas.begin(); it != skillDatas.end(); ++it)
	{
		if (it->GetSkillID() != skillID_)
		{
			return true;
		}
	}
	return false;
}


//!@brief Skill�𐶐�����{�^���ɑΉ����ăX�L�����o��������
//!@param[in] num �ԍ�
void	SkillManager::CreateSkill(const int& num)
{
	skill.emplace_back(CreateSkillType(skillDatas[num].GetSkillID(),num));
}

//!@brief SkillID��0(���݂��Ȃ�)�łȂ������`�F�b�N
//!@param[in] skillID_ �擾�����X�L��ID
//!@return ID��0�Ȃ�true
bool	SkillManager::IsNonSkillID(const int& skillID_)
{
	if (skillID_ != 0)
	{
		return false;
	}
	return true;
}


//!@brief SkillAndCharaChip�^�̃f�[�^���󂯎��
//!@param[in] skill �X�L���f�[�^
//!@return �󂯎���f�[�^�Ȃ�(����Ɏ󂯎�ꂽ�Ȃ�)true
bool	SkillManager::ReceiveSkillAndCharaChip(const Enemy::SkillAndCharaChip& skill)
{
	//SkillID��0�łȂ������`�F�b�N
	if (IsNonSkillID(*skill.skillId))
	{
		//return false;
	}

	//�X�L���͈ꎞ�I�Ƀ{�^��5�ɓ���
	skillDatas[skillNum - 1].SetSkillID(*skill.skillId);
	skillDatas[skillNum - 1].SetSkillImageName(*skill.textureName);
	skillDatas[skillNum - 1].SetAnimCharaChip(skill.nowCharaChip);
	skillDatas[skillNum - 1].SetSkillAppearPos(*skill.pos);

	std::cout << "�X�L���f�[�^���󂯎��܂���" << std::endl;
	return true;
}


//!@brief SkillID�ɂ���ăX�L������������̂�ς���
//!@param[in] SkillType �X�L���̎��
//!@return �X�L���̎��(�h���N���X)
SkillType*	SkillManager::CreateSkillType(const int& skillID_,const int& btn)
{
	SkillType*	skillType = nullptr;

	//��������O�Ɏg�p�񐔂����邩�`�F�b�N
	if (skillDatas[btn].CheckUseNum())
	{
		switch (skillID_) {
		case 0:
			skillType = new SkillSword(skillDatas[btn].GetContinueTime(), skillDatas[btn].GetDistance(), object, 
				skillDatas[btn].GetSkillImageName(), skillDatas[btn].GetAnimCharaChip());
			break;
		case 2:
			//return new Walk();
		default:
			return nullptr;
		}
		//�����������
		//�X�L���f�[�^�̎g�p�񐔂����炷
		skillDatas[btn].CountDownUseNum();
	}
	else
	{
		skillDatas[btn].Clear();	//�N���A��������
	}
	return skillType;
}




//!@brief Skill��o�^����
void	SkillManager::RegistSkill(const int& num)
{
	//�Ή������{�^���ɃX�L��Datas��n��
	//���̃{�^���������ꂽSkillDatas�Ƀf�[�^���Ȃ�(-1)
	if (skillDatas[num].GetSkillID() == -1)
	{
		//�X�L��ID���������`�F�b�N
		if (skillDatas[skillNum - 1].GetSkillID() == skillDatas[num].GetSkillID())
		{
			//�����Ȃ�A�{�^��5�̃X�L���f�[�^�X�L���ԍ��̃X�L���ɓn��
			skillDatas[num].SetSkillID(skillDatas[skillNum - 1].GetSkillID());
			skillDatas[num].SetSkillType(&skillDatas[skillNum - 1].GetSkillType());
			skillDatas[num].SetSkillImageName(skillDatas[skillNum - 1].GetSkillImageName());
			skillDatas[num].SetAnimCharaChip(&skillDatas[skillNum - 1].GetAnimCharaChip());
			skillDatas[num].SetSkillAppearPos(skillDatas[skillNum - 1].GetSkillAppearPos());
			skillDatas[skillNum - 1].Clear();
		}
		else
		{
			skillDatas[num].Clear();
			//�O�̃f�[�^���폜���āA�V�����X�L���f�[�^��n��
			skillDatas[num].SetSkillID(skillDatas[skillNum - 1].GetSkillID());
			skillDatas[num].SetSkillType(&skillDatas[skillNum - 1].GetSkillType());
			skillDatas[num].SetSkillImageName(skillDatas[skillNum - 1].GetSkillImageName());
			skillDatas[num].SetAnimCharaChip(&skillDatas[skillNum - 1].GetAnimCharaChip());
			skillDatas[num].SetSkillAppearPos(skillDatas[skillNum - 1].GetSkillAppearPos());
			skillDatas[skillNum - 1].Clear();
		}
	}
}

//!@brief �g�p���邩�o�^���邩���f���A���ꂼ��̏������s��
void	SkillManager::Process(const int& btnNum)
{
	createSkillFlag = false;	//��Ɏg�p���Ȃ�

	//�o�^��Ԃ̂Ƃ�
	if (CheckRegistFlag())
	{
		RegistSkill(btnNum);
		skillDatas[btnNum].DecideSkillParam();	//�g�p�񐔂�����
		ChangeRegistFlag(false);				//�o�^���[�h�I��
		std::cout << "�X�L����" << btnNum << "�ɓo�^" << std::endl;
	}
	else   //������else���͂����Ɠo�^�Ɠ����ɃX�L���g�p�\
	//�X�L���𑶍݂���Ƃ�
	if (skillDatas[btnNum].CheckUseNum())
	{
		createSkillFlag = true;
		CreateSkill(btnNum);
		std::cout << "�X�L��:" << btnNum << "�g���܂���" << std::endl;
	}
	else
	{
		createSkillFlag = false;
		std::cout << "�X�L��������܂���" << std::endl;
	}
}



//!@brief �I�u�W�F�N�g�̃f�[�^���Q��
//!@param[in] obj �Q�[���I�u�W�F�N�g�̎Q��
void	SkillManager::SetObjectData(const GameObject& obj)
{
	object = obj;
}


//!@brief �X�V����
void	SkillManager::UpDate()
{
	for (auto it = skill.begin(); it != skill.end();)
	{
		if ((*it) != nullptr)
		{
			if ((*it)->KillTime())
			{
				delete (*it);
				(*it) = nullptr;
				it = skill.erase(it);
			}
			else
			{
				(*it)->UpDate();
				it++;
			}
		}
	}
}


//!@brief �`�揈��
void	SkillManager::Render()
{
	for (auto it = skill.begin(); it != skill.end(); ++it)
	{
		if ((*it) != nullptr)
		{
			(*it)->Render();
		}
	}
}



//!@brief �o�^�t���O�̐؂�ւ�
//!@param[in] �o�^�t���O registFlag
void	SkillManager::ChangeRegistFlag(bool registFlag_)
{
	registFlag = registFlag_;
}

//!@brief ���݂̓o�^�t���O�̎擾
//!@return �o�^��ԂȂ�true
bool	SkillManager::CheckRegistFlag() const
{
	return registFlag;
}


//!@brief ���݂̎g�p���t���O�̎擾
//!@return �g�p���Ȃ�true
bool	SkillManager::CheckCreateSkillFlag() const
{
	return createSkillFlag;
}