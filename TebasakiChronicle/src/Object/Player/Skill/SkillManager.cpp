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


	std::cout << "�X�L���f�[�^���󂯎��܂���" << std::endl;
	return true;
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
			skillDatas[skillNum - 1].Clear();
		}
	}
}

//!@brief Skill���g�p����
//!@param[in] btnNum �{�^���ԍ�
//!@param[in] obj �Q�[���I�u�W�F�N�g�̎Q��
void	SkillManager::UseSkill(const int& btnNum,GameObject& obj)
{
	if (skillDatas[btnNum].CheckUseNum())
	{
		CreateSkillObject(btnNum,obj);
	}
}

//!@brief �g�p���邩�o�^���邩���f���A���ꂼ��̏������s��
void	SkillManager::Process(const int& btnNum,GameObject& obj)
{
	createSkillFlag = false;	//��Ɏg�p���Ȃ�

	//�o�^��Ԃ̂Ƃ�
	if (CheckRegistFlag())
	{
		RegistSkill(btnNum);						//�X�L����o�^
		skillDatas[btnNum].CreateSkillType();		//�X�L���̎�ނ𐶐�

		ChangeRegistFlag(false);					//�o�^���[�h�I��
		std::cout << "�X�L����" << btnNum << "�ɓo�^" << std::endl;
	}
	else   //������else���͂����Ɠo�^�Ɠ����ɃX�L���g�p�\
	//�X�L���𑶍݂���Ƃ�
	if (skillDatas[btnNum].CheckUseNum())
	{
		createSkillFlag = true;
		CreateSkillObject(btnNum,obj);	//SkillObj�𐶐�

		skillDatas[btnNum].CountUseNum();	//�����J�E���g
		std::cout << "�X�L��:" << btnNum << "�g���܂���" << std::endl;
	}
	else
	{
		if (skillDatas[btnNum].GetSkillID() != -1)
		{
			delete &skillDatas[btnNum].GetSkillType();
			skillDatas[btnNum].Clear();
		}

		createSkillFlag = false;
		std::cout << "�X�L��������܂���" << std::endl;
	}
}




//!@brief �X�V����
void	SkillManager::UpDate()
{
	for (auto it = skillObj.begin(); it != skillObj.end();)
	{
		if ((*it) != nullptr)
		{
			if ((*it)->CheckSurvivalTime())
			{
				(*it)->UpDate();
				++it;
			}
			else
			{
				delete (*it);
				(*it) = nullptr;
				it = skillObj.erase(it);
			}
		}
	}
}


//!@brief �`�揈��
void	SkillManager::Render()
{
	for (auto it = skillObj.begin(); it != skillObj.end(); ++it)
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


//!@brief ��������SkillType����SkillObj���쐬
//!@brief ����������true
bool	SkillManager::CreateSkillObject(const int& btn,GameObject& obj)
{
	skillObj.emplace_back(new SkillObject(&skillDatas[btn].GetSkillType(),obj,
		skillDatas[btn].GetSkillImageName(),skillDatas[btn].GetAnimCharaChip()));
	return true;
}
