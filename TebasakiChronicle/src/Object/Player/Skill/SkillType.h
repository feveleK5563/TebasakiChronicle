#pragma once
#include "K_Math\MyMathFanctions.h"
#include "SkillObject.h"


//----------------------------------------------------------
//�X�L���̎�ނ̃C���^�[�t�F�C�X
//�T�v:�X�L���̎�ނ�\���C���^�[�t�F�C�X
//�����:�����
//----------------------------------------------------------
class SkillType
{
protected:
	//!@brief �R���X�g���N�^
	//!@param[in] continueTime_ �p������
	//!@param[in] distance_ ����
	//!@param[in] appearPos_ �o���ʒu
	//!@param[in] animCharaChip �A�j���[�V�����L�����`�b�v
	explicit SkillType(const int& continueTime_,
		const float& distance_,
		GameObject& obj,
		const std::string& textureName,
		const AnimationCharaChip& animCharaChip);
public:
	virtual ~SkillType();

	virtual void	UpDate() = 0;
	virtual void	Render() = 0;

	virtual bool	KillTime() = 0;

protected:
	int				continueTime;	//�p������
	float			distance;		//����
	K_Math::Vector3	appearPos;		//�o���ʒu
	SkillObject*	skillObject;	//�X�L���̓����蔻��Ȃ�
};

