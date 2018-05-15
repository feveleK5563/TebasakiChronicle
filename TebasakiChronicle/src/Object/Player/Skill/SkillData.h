#pragma once

#include "K_Graphics/ImageLoader.h"
#include "../src/BaseClass/ImageManager/AnimationCharaChip.h"
#include "SkillType.h"

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
	//!@brief �X�L���̏o���ʒu��Ԃ�
	//!@return SkillAppearPos��Ԃ�
	K_Math::Vector3& GetSkillAppearPos();
	//!@brief �X�L���̃L�����`�b�v
	AnimationCharaChip& GetAnimCharaChip();

	//!@brief �X�L���f�[�^���Z�b�g����
	//!@param[in] skillID_ �X�L��ID
	//!@param[in] skillType_ �X�L���̎��
	//!@param[in] spriteObj_ �X�v���C�g�I�u�W�F�N�g
	//!@param[in] animCharaChip_ �A�j���[�V�����L�����`�b�v
	void	SetSkillData(	const int& skillID_,
							SkillType* skillType_,
							K_Graphics::SpriteObject* spriteObj_,
							AnimationCharaChip* animCharaChip_);

public:
	//!@brief �X�L���̎�ނ̃Z�b�g
	//!@param[in] skillType_ �擾�����X�L���̎��
	void	SetSkillType(SkillType* skillType_);
	//!@brief �X�L��ID�̃Z�b�g
	//!@brief[in] skillID_ �擾�����X�L��ID
	void	SetSkillID(const int& skillID_);
	//!@brief �X�v���C�g�I�u�W�F�N�g�̃Z�b�g
	//!@param[in] spriteObj_ �擾�����X�v���C�g
	void	SetSpriteObj(K_Graphics::SpriteObject* spriteObj_);
	//!@brief �A�j���[�V�����L�����`�b�v
	//!@param[in] animCharaChip_ �擾�����L�����`�b�v
	void	SetAnimCharaChip(AnimationCharaChip* animCharaChip_);

	//!@brief �X�L���̉摜�����擾
	//!@param[in] skillImageName_ �擾�����X�L���摜��
	void	SetSkillImageName(const std::string& skillImageName_);

	//!@brief �o���ʒu���擾
	//!@param[in] appearPos_ �擾�����o���ʒu
	void	SetSkillAppearPos(const K_Math::Vector3& appearPos_);

public:
	//!@brief ���g�̃f�[�^�����ׂăN���A����
	void	Clear();

	//!@brief �X�L��ID�X�L���̃p�����[�^�����߂�
	void	DecideSkillParam();
	//!@brief �g�p�񐔂�ݒ�
	void	SetUseNum(const int& useNum_);
	//!@brief ���݂̎g�p�񐔂��擾
	int		GetNowUseNum() const;
	//!@brief �g�p�񐔂����邩�`�F�b�N
	//!@return 0�ȏ�Ȃ�true
	bool	CheckUseNum();
	//!@brief �g�p�񐔂����炷����
	void	CountDownUseNum();

	//!@brief �p�����Ԃ̎擾
	//!@return �p�����ԃf�[�^
	int		GetContinueTime() const;
	//!@brief �����̎擾
	//!@return �����f�[�^
	float	GetDistance() const;

private:
	int							skillID;		//�X�L��ID
	SkillType*					skillType;		//�X�L���̎��
	K_Graphics::SpriteObject*	spriteObj;		//�X�v���C�g
	AnimationCharaChip*			animCharaChip;	//�A�j���[�V�����L�����`�b�v

	std::string					skillImageName;	//�X�L���̉摜��
	K_Math::Vector3				appearPos;		//�o���ʒu
	int							useNum;			//�g�p��
	int							continueTime;	//�p������
	float						distance;		//����
};