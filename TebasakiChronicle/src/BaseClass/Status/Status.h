#pragma once
#include "K_Math/MyMathFanctions.h"

//---------------------------------------------------------------------
//�X�e�[�^�X�N���X
//�T�v:�X�e�[�^�X��ێ����Ă���
//�����:�����
//---------------------------------------------------------------------
class Status
{
public:
	Status();
	~Status();

public:
	//����
	enum Direction
	{
		Right = 0,
		Left = 180,
	};

	//���
	enum State
	{
		Non,
		Active,
		Death,
		Invalid,
	};

public:
	//�ꊇ�ݒ菈��
	void	SetStatusData(
		const State& state,const K_Math::Vector3& pos,
		const K_Math::Vector3& angle,const K_Math::Vector3& scale,
		const Direction& dir, const int& attackPoint,const int& life
	);

	//!@brief	�ő�Life�̐ݒ�
	//!@param[in]	maxLife_	�ő�Life
	void	SetMaxLife(const int maxLife_);
	//!@brief	�ŏ�Life�̐ݒ�
	//!@param[in]	minLife_	�ŏ�Life
	void	SetMinLife(const int minLife_);
	//!@brie	�R���W�����}�X�N�̐ݒ�
	//!@param[in]	collisionMask	�R���W�����}�X�N
	void	SetCollisionMask(const int collisionMask);
	//!@breif	��Ԃ̐ݒ�
	//!@param[in]	state	���
	void	SetState(const State& state);

	//�擾����
	State&				GetState();
	K_Math::Vector3&	GetPos();
	K_Math::Vector3&	GetInitialPos();
	K_Math::Vector3&	GetAngle();
	K_Math::Vector3&	GetScale();
	Direction&			GetDirection();
	int&				GetAttackPoint();
	int&				GetLife();
	int&				GetMaxLife();
	int&				GetMinLife();
	int&				GetCollisiomMask();

private:
	State				state;		//���
	K_Math::Vector3		pos;		//���W
	K_Math::Vector3		initialPos;	//�������W
	K_Math::Vector3		angle;		//�X��
	K_Math::Vector3		scale;		//�g��k��
	Direction			direction;	//����
	int					attackPoint;//�U����
	int					life;		//�̗�
	int					maxLife;	//�ő�life
	int					minLife;	//�ŏ�life
	int					collisionMask;	//�R���W�����}�X�N
};