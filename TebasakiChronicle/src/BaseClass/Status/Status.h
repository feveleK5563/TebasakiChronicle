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
	};

	//�R���W�����}�X�N
	enum CollisionMaskState
	{
		None = 0,
		Ground = 1 << 0,
		PlayerCollision = 1 << 1,
		EnemyCollision = 1 << 2,
		TakeDamagePlayer = 1 << 3,
		TakeDamageEnemy = 1 << 4,
		CameraGunCollision = 1 << 5,
		EnemyCamCollision = 1 << 6,
	};

public:
	//�ꊇ�ݒ菈��
	void	SetStatusData(
		const State& state,const K_Math::Vector3& pos,
		const K_Math::Vector3& angle,const K_Math::Vector3& scale,
		const Direction& dir, const int& attackPoint,const int& life
	);

	//!@brief	�ő�Life�̐ݒ�
	//!@brief	maxLife_	�ő�Life
	void	SetMaxLife(const int maxLife_);
	//!@brief	�ŏ�Life�̐ݒ�
	//!@brief	minLife_	�ŏ�Life
	void	SetMinLife(const int minLife_);

	//�擾����
	State&				GetState();
	K_Math::Vector3&	GetPos();
	K_Math::Vector3&	GetAngle();
	K_Math::Vector3&	GetScale();
	Direction&			GetDirection();
	int&				GetAttackPoint();
	int&				GetLife();
	int&				GetMaxLife();
	int&				GetMinLife();

private:
	State				state;		//���
	K_Math::Vector3		pos;		//���W
	K_Math::Vector3		angle;		//�X��
	K_Math::Vector3		scale;		//�g��k��
	Direction			direction;	//����
	int					attackPoint;//�U����
	int					life;		//�̗�
	int					maxLife;	//�ő�life
	int					minLife;	//�ŏ�life
};