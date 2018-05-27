#pragma once
#include "K_Math\MyMathFanctions.h"
#include "SkillObject.h"
#include "../src/Object/Enemy/EnemyType/CharacterBehavior.h"

//----------------------------------------------------------
//�X�L���̎�ނ̃C���^�[�t�F�C�X
//�T�v:�X�L���̎�ނ�\���C���^�[�t�F�C�X
//�����:�����
//----------------------------------------------------------
class SkillType
{
public:
	//!@brief �R���X�g���N�^
	//!@param[in] �ő�g�p��
	//!@param[in] �o������
	//!@param[in] �p������
	SkillType(const int& maxUseNum,const float& appearDist,const int& continueTime);
	virtual ~SkillType();

	virtual void	UpDate() = 0;
	
public:
	int		GetContinueTime() const;
	float	GetAppearDist() const;
	int		GetMaxUseNum() const;

protected:
	CharacterBehavior	charaBehaivor;	//����
	int				continueTime;	//�p������
	float			appearDist;		//�o������
	int				maxUseNum;		//�ő�g�p��
};

