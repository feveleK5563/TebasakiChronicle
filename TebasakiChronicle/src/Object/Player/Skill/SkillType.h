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
	//!@brief	�X�L���̃^�C�v(�n��)
	enum class Type
	{
		MoveSkill,			//����n
		AttackSkill,		//�U���n
		PassiveSkill,		//�p�b�V�u�n
	};

public:
	//!@brief �R���X�g���N�^
	//!@param[in] ����ID
	//!@param[in] �ő�g�p��
	//!@param[in] �o������
	//!@param[in] �p������
	//!@param[in] �U����
	SkillType(const int& moveID,const int& maxUseNum,const float& appearDist,const int& continueTime,const int& attackPoint);
	virtual ~SkillType();

	virtual void	UpDate(GameObject& object) = 0;
	
public:
	int		GetContinueTime() const;
	float	GetAppearDist() const;
	int		GetMaxUseNum() const;
	int		GetAttackPoint() const;


	//������
	void	BehaivorInit(TemporaryCollisionManager& tempCol, Status& status, Move& move);
	//�I��
	void	BehaivorFinal(TemporaryCollisionManager& tempCol, Status& status, Move& move);
	//����
	void	Behaivor(TemporaryCollisionManager& tempCol,Status& status,Move& move);
	
	//!@brief	�X�L���̃^�C�v(�n��)��Ԃ�
	//!@return	�X�L���̃^�C�v
	Type&	GetType();

	//!@brief	�^����R���W�����}�X�N��Ԃ�
	//!@return	�^����R���W�����}�X�N
	Status::CollisionMaskState&	GetGiveCollisionMask();
	//!@brief	�󂯎��R���W�����}�X�N��Ԃ�
	//!@return	�󂯎��R���W�����}�X�N
	Status::CollisionMaskState&	GetReciveCollisionMask();


protected:
	CharacterBehavior	charaBehaivor;	//����
	int					continueTime;	//�p������
	float				appearDist;		//�o������(�v���C���[����̋���)
	int					maxUseNum;		//�ő�g�p��
	int					attackPoint;	//�U����
	Type				type;			//�^�C�v
	Status::CollisionMaskState		giveCollisionMask;		//�^����R���W�����}�X�N
	Status::CollisionMaskState		reciveCollisionMask;	//�󂯎��R���W�����}�X�N
};

