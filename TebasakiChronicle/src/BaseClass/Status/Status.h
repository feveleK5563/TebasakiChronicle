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

public:
	//�ꊇ�ݒ菈��
	void	SetStatusData(
		const State& state,const K_Math::Vector3& pos,
		const K_Math::Vector3& angle,const K_Math::Vector3& scale,
		const Direction& dir, const int& attackPoint,const int& life
	);


	//�擾����
	State&				GetState();
	K_Math::Vector3&	GetPos();
	K_Math::Vector3&	GetAngle();
	K_Math::Vector3&	GetScale();
	Direction&			GetDirection();
	int&				GetAttackPoint();
	int&				GetLife();

private:
	State				state;		//���
	K_Math::Vector3		pos;		//���W
	K_Math::Vector3		angle;		//�X��
	K_Math::Vector3		scale;		//�g��k��
	Direction			direction;	//����
	int					attackPoint;//�U����
	int					life;		//�̗�
};