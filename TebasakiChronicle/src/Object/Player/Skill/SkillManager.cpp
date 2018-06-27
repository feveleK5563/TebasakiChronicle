#include "SkillManager.h"
#include "../src/Helper.h"
#include "SkillAttack/SkillAttack.h"


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
	for (auto it : skillObj)
	{
		delete it;
	}
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


//!@brief Skill��o�^����
void	SkillManager::RegistSkill(const int& num)
{
	//�Ή������{�^���ɃX�L��Datas��n��
	//�X�L��ID���������`�F�b�N
	if (skillDatas[skillNum - 1].GetSkillID() == skillDatas[num].GetSkillID())
	{
		skillDatas[num].Clear();
		//�����Ȃ�A�{�^��5�̃X�L���f�[�^�X�L���ԍ��̃X�L���ɓn��
		skillDatas[num].SetSkillID(skillDatas[skillNum - 1].GetSkillID());
		skillDatas[num].SetSkillType(skillDatas[skillNum - 1].GetSkillType());
		skillDatas[num].SetSkillImageName(skillDatas[skillNum - 1].GetSkillImageName());
		skillDatas[num].SetAnimCharaChip(&skillDatas[skillNum - 1].GetAnimCharaChip());
		skillDatas[num].SetPressBtnNum(num);
		skillDatas[num].MoveGUIObjPos();
		skillDatas[skillNum - 1].Clear();
			
	}
	else
	{
		skillDatas[num].Clear();
		//�O�̃f�[�^���폜���āA�V�����X�L���f�[�^��n��
		skillDatas[num].SetSkillID(skillDatas[skillNum - 1].GetSkillID());
		skillDatas[num].SetSkillType(skillDatas[skillNum - 1].GetSkillType());
		skillDatas[num].SetSkillImageName(skillDatas[skillNum - 1].GetSkillImageName());
		skillDatas[num].SetAnimCharaChip(&skillDatas[skillNum - 1].GetAnimCharaChip());
		skillDatas[num].SetPressBtnNum(num);
		skillDatas[num].MoveGUIObjPos();
		skillDatas[skillNum - 1].Clear();
	}
}

//!@brief SkillAndCharaChip�^�̃f�[�^���󂯎��
//!@param[in] skill �X�L���f�[�^
//!@return �󂯎���f�[�^�Ȃ�(����Ɏ󂯎�ꂽ�Ȃ�)true
bool	SkillManager::ReceiveSkillAndCharaChip(const Enemy::SkillAndCharaChip& skill)
{
	//SkillID��0�łȂ������`�F�b�N
	if (IsNonSkillID(*skill.behaviorId))
	{
		return false;
	}

	skillDatas[skillNum - 1].Clear();	//�N���A
	//�X�L���͈ꎞ�I�Ƀ{�^��5�ɓ���
	skillDatas[skillNum - 1].SetSkillID(*skill.behaviorId);
	skillDatas[skillNum - 1].SetSkillImageName(*skill.textureName);
	skillDatas[skillNum - 1].SetAnimCharaChip(skill.nowCharaChip);
	skillDatas[skillNum - 1].SetPressBtnNum(skillNum - 1);
	skillDatas[skillNum - 1].CreateGUIObject();
	skillDatas[skillNum - 1].CreateSkillType();
	return true;
}


//!@brief �X�V����
void	SkillManager::UpDate(GameObject& object)
{
	for (auto it = skillObj.begin(); it != skillObj.end();)
	{
		if ((*it) != nullptr)
		{
			if ((*it)->CheckSurvivalTime())
			{
				(*it)->UpDate(object);
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
	//�X�L��UI�̕`��
	for (int i = 0; i < 5; ++i)
	{
		skillDatas[i].RenderUI();
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

//!@brief �w�肵���{�^���̃X�L�������݂��邩�̃`�F�b�N
//!@param[in] btn �{�^���ԍ�
//!@return ���݂���Ȃ�true
bool	SkillManager::CheckExistSkill(const int& btn)
{
	if (!skillDatas[btn].CheckUseNum())
	{
		return false;
	}
	return true;
}

//!@brief ��������SkillType����SkillObj���쐬
//!@brief ����������true
bool	SkillManager::CreateSkillObject(const int& btn,GameObject& obj)
{
	skillObj.emplace_back(new SkillObject(skillDatas[btn].GetSkillType(),obj,
		skillDatas[btn].GetSkillImageName(),skillDatas[btn].GetAnimCharaChip()));
	return true;
}


//!@brief �w�肵���X�L�����N���A����
void	SkillManager::ClearSkill(const int& btn)
{
	skillDatas[btn].Clear();
}


//!@brief �X�L����o�^����
//!@param[in] btnNum �{�^���ԍ�
void	SkillManager::RegistSkillData(const int& btnNum)
{
	if (CheckRegistFlag())
	{
		if (skillDatas[skillNum - 1].GetSkillID() == 0) { return; }
		std::cout << "�o�^���܂�" << std::endl;
		RegistSkill(btnNum);						//�X�L����o�^
		skillDatas[btnNum].CreateSkillType();		//�X�L���̎�ނ𐶐�
		ChangeRegistFlag(false);					//�o�^���[�h�I��
	}
}

//!@brief �X�L�����g�p����
//!@param[in] btnNum �{�^���ԍ�
//!@param[in] obj �Q�[���I�u�W�F�N�g
void	SkillManager::UseSkillData(const int& btnNum, GameObject& obj)
{
	if (skillDatas[btnNum].CheckUseNum())
	{
		if (!CheckRegistFlag())
		{
			CreateSkillObject(btnNum, obj);		//SkillObj�𐶐�
			skillDatas[btnNum].CountUseNum();	//�����J�E���g

			std::cout << skillDatas[btnNum].GetNowUseNum() << std::endl;
			//�X�L�����Ȃ��Ȃ邽�ߏ���
			if (!skillDatas[btnNum].CheckUseNum()) { skillDatas[btnNum].Clear(); }
		}
	}
	else
	{
		if (skillDatas[btnNum].GetSkillID() != -1)
		{
			skillDatas[btnNum].Clear();
		}
	}
}


