#pragma once
#include <array>
#include "../src/Object/Player/Skill/SkillData.h"
#include "SkillObject.h"
#include "../src/Object/Enemy/Enemy.h"

//----------------------------------------------------------------
//�X�L�����Ǘ�����
//�T�v:�X�L�����Ǘ�����A�v���C���[������Skill�̔��̂悤�Ȃ���
//�����:�����
//----------------------------------------------------------------
class SkillManager
{
public:
	SkillManager();
	~SkillManager();


	//!@brief SkillID�����������`�F�b�N
	//!@param[in] skillID_ �擾�����X�L��ID
	//!@return ID�������Ȃ�true
	bool	CheckSkillID(const int& skillID_);

	//!@brief Skill�𐶐�����{�^���ɑΉ����ăX�L�����o��������
	//!@param[in] num �ԍ�
	void	CreateSkill(const int& num);

	//!@brief SkillID��0(���݂��Ȃ�)�łȂ������`�F�b�N
	//!@param[in] skillID_ �擾�����X�L��ID
	//!@return ID��0�Ȃ�true
	bool	IsNonSkillID(const int& skillID_);

	//!@brief SkillAndCharaChip�^�̃f�[�^���󂯎��
	//!@param[in] skill �X�L���f�[�^
	//!@return �󂯎���f�[�^�Ȃ�(����Ɏ󂯎�ꂽ�Ȃ�)true
	bool	ReceiveSkillAndCharaChip(const Enemy::SkillAndCharaChip& skill);

	//!@brief SkillID�ɂ���ăX�L������������̂�ς���
	//!@param[in] skillID_ �X�L����ID
	//!@param[in] btn �{�^���ԍ�
	//!@return �X�L���̎��(�h���N���X)
	SkillType*	CreateSkillType(const int& skillID_,const int& btn);

	//!@brief Skill��o�^����
	void	RegistSkill(const int& num);

	//!@brief �g�p���邩�o�^���邩���f���A���ꂼ��̏������s��
	void	Process(const int& btnNum);


	//!@brief �I�u�W�F�N�g�̃f�[�^���Q��
	//!@param[in] obj �Q�[���I�u�W�F�N�g�̎Q��
	void	SetObjectData(const GameObject& obj);


	//!@brief �X�V����
	void	UpDate();
	//!@brief �`�揈��
	void	Render();
	
public:
	//!@brief �o�^�t���O�̐؂�ւ�
	//!@param[in] registFlag_ �o�^�t���O
	void	ChangeRegistFlag(bool registFlag_);
	//!@brief ���݂̓o�^�t���O�̎擾
	//!@return �o�^��ԂȂ�true
	bool	CheckRegistFlag() const;

	//!@brief ���݂̎g�p���t���O�̎擾
	//!@return �g�p���Ȃ�true
	bool	CheckCreateSkillFlag() const;

private:
	static const int			skillNum = 5;	//�X�L����
	std::array<SkillData, skillNum>	skillDatas;	//�X�L���f�[�^
	std::vector<SkillType*>		skill;			//�X�L��
	GameObject					object;			//�Q�[���I�u�W�F�N�g
	bool						registFlag;		//�o�^�t���O
	bool						createSkillFlag;//�g�p���t���O
};