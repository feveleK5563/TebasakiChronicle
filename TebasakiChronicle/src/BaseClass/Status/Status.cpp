#include "Status.h"

//-----------------------------------------------------------------
//�X�e�[�^�X�̎���
//�����:�����
//-----------------------------------------------------------------

//---------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------
Status::Status()
{
	
}

//---------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------
Status::~Status()
{

}


//---------------------------------------------------
//�ꊇ�ݒ菈��
//---------------------------------------------------
void	Status::SetStatusData(const State& state, const K_Math::Vector3& pos,
	const K_Math::Vector3& angle, const K_Math::Vector3& scale,
	const Direction& dir, const int& attackPoint,const int& life)
{
	this->state = state;
	this->pos = pos;
	this->angle = angle;
	this->scale = scale;
	this->direction = dir;
	this->attackPoint = attackPoint;
	this->life = life;
}

//!@brief	�ő�Life�̐ݒ�
//!@brief	maxLife_	�ő�Life
void	Status::SetMaxLife(const int maxLife_)
{
	maxLife = maxLife_;
}
//!@brief	�ŏ�Life�̐ݒ�
//!@brief	minLife_	�ŏ�Life
void	Status::SetMinLife(const int minLife_)
{
	minLife = minLife_;
}


//---------------------------------------------------
//�擾����
//---------------------------------------------------
//��Ԃ̎擾
Status::State&	Status::GetState()
{
	return state;
}

//�ʒu�̎擾
K_Math::Vector3&	Status::GetPos()
{
	return pos;
}

//�X���̎擾
K_Math::Vector3&	Status::GetAngle()
{
	return angle;
}

//�g��k���̎擾
K_Math::Vector3&	Status::GetScale()
{
	return scale;
}

//�����̎擾
Status::Direction&	Status::GetDirection()
{
	return direction;
}

//�U���͂̎擾
int&				Status::GetAttackPoint()
{
	return attackPoint;
}

//�̗͂̎擾
int&				Status::GetLife()
{
	return life;
}

//!@brief	�ő�̗͂̎擾
//!@return	maxLife	�ő�Life
int&				Status::GetMaxLife()
{
	return maxLife;
}

//!@brief	�ŏ��̗͂̎擾
//!@return	minLife	�ŏ�Life
int&				Status:: GetMinLife()
{
	return minLife;
}

