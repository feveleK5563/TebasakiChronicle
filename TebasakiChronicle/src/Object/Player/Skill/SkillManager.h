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


	//!@brief SkillID��0(���݂��Ȃ�)�łȂ������`�F�b�N
	//!@param[in] skillID_ �擾�����X�L��ID
	//!@return ID��0�Ȃ�true
	bool	IsNonSkillID(const int& skillID_);

	//!@brief SkillAndCharaChip�^�̃f�[�^���󂯎��
	//!@param[in] skill �X�L���f�[�^
	//!@return �󂯎���f�[�^�Ȃ�(����Ɏ󂯎�ꂽ�Ȃ�)true
	bool	ReceiveSkillAndCharaChip(const Enemy::SkillAndCharaChip& skill);

	
	//!@brief Skill��o�^����
	//!@param[in] btnNum �{�^���ԍ�
	void	RegistSkill(const int& btnNum);
	//!@brief Skill���g�p����
	//!@param[in] btnNum �{�^���ԍ�
	//!@param[in] obj �I�u�W�F�N�g�̎Q��
	void	UseSkill(const int& btnNum,GameObject& obj);

	//!@brief �g�p���邩�o�^���邩���f���A���ꂼ��̏������s��
	void	Process(const int& btnNumconst,GameObject& obj);



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
	//!@brief ��������SkillType����SkillObj���쐬
	//!@brief btn �{�^���ԍ�
	//!@brief ����������true
	bool	CreateSkillObject(const int& btn,GameObject& obj);

private:
	static const int			skillNum = 5;	//�X�L����
	std::array<SkillData, skillNum>	skillDatas;	//�X�L���f�[�^
	std::vector<SkillObject*>		skillObj;	//�X�L���I�u�W�F�N�g
	bool						registFlag;		//�o�^�t���O
	bool						createSkillFlag;//�g�p���t���O
};