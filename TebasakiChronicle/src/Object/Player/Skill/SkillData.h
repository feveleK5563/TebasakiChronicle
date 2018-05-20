#pragma once

#include "K_Graphics/ImageLoader.h"
#include "../src/BaseClass/ImageManager/AnimationCharaChip.h"
#include "SkillType.h"
#include "SkillSword\SkillSword.h"

//------------------------------------------------------------
//�X�L���̃f�[�^
//�T�v:�X�L���̃f�[�^�������Ă���
//�����:�����
//------------------------------------------------------------
class SkillData
{
public:
	SkillData();
	~SkillData();

	//!@brief �ێ����Ă���X�L��ID��Ԃ�
	//!@return skillID��Ԃ�
	int		GetSkillID();
	//!@brief �X�L���̎�ނ�Ԃ�
	//!@return SkillType��Ԃ�
	SkillType& GetSkillType() const;
	//!@brief �X�L���̉摜����Ԃ�
	//!@return SkillImageName��Ԃ�
	std::string& GetSkillImageName();
	//!@brief �X�L���̃L�����`�b�v
	AnimationCharaChip& GetAnimCharaChip();

	//!@brief �X�L���f�[�^���Z�b�g����
	//!@param[in] skillID_ �X�L��ID
	//!@param[in] animCharaChip_ �A�j���[�V�����L�����`�b�v
	void	SetSkillData(	const int& skillID_,
							AnimationCharaChip* animCharaChip_);

public:
	//!@brief �X�L���̎�ނ̃Z�b�g
	//!@param[in] skillType_ �擾�����X�L���̎��
	void	SetSkillType(SkillType* skillType_);
	//!@brief �X�L��ID�̃Z�b�g
	//!@brief[in] skillID_ �擾�����X�L��ID
	void	SetSkillID(const int& skillID_);
	//!@brief �A�j���[�V�����L�����`�b�v
	//!@param[in] animCharaChip_ �擾�����L�����`�b�v
	void	SetAnimCharaChip(AnimationCharaChip* animCharaChip_);

	//!@brief �X�L���̉摜�����擾
	//!@param[in] skillImageName_ �擾�����X�L���摜��
	void	SetSkillImageName(const std::string& skillImageName_);


public:
	//!@brief ���g�̃f�[�^�����ׂăN���A����
	void	Clear();

	//!@brief �g�p�񐔂�ݒ�
	void	SetUseNum(const int& useNum_);
	//!@brief ���݂̎g�p�񐔂��擾
	int		GetNowUseNum() const;
	//!@brief �g�p�񐔂����邩�`�F�b�N
	//!@return skillType�̎w��񐔈ȓ��Ȃ�true
	bool	CheckUseNum();
	//!@brief �g�p�񐔂��J�E���g���鏈��
	void	CountUseNum();

	//!@brief �X�L��ID����X�L���̎�ނ����߂�
	void	CreateSkillType();

private:
	int							skillID;		//�X�L��ID
	SkillType*					skillType;		//�X�L���̎��
	AnimationCharaChip*			animCharaChip;	//�A�j���[�V�����L�����`�b�v
	std::string					skillImageName;	//�X�L���̉摜��
	int							useNum;			//�g�p��
};