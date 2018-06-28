#include "Move.h"

#include <iostream>
//------------------------------------------------------
//�T�v:Move�N���X�̏������e
//�����:�����
//------------------------------------------------------


//------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------
Move::Move() :
	moveVec(K_Math::Vector3(0, 0, 0)),
	addVec(0.0f),
	jumpPower(0.0f),
	fallSpeed(0.0f),
	defaultGravity(-0.5f),
	gravity(defaultGravity)
{
	verticalPower = 7.5f;
	horizontalPower = 7.0f;
	verticalSpeed = 0;
	horizontalSpeed = 0;

	maxFallSpeed = -15.0f;
	maxverticalSpeed = 15.0f;
	maxhorizontalSpeed = 15.0f;
}
Move::Move(const K_Math::Vector3& vec, float add, float jumpPow, float fallSpeed, float gravity) :
	moveVec(vec),
	addVec(add),
	jumpPower(jumpPow),
	fallSpeed(fallSpeed),
	defaultGravity(-0.5f),
	gravity(gravity)
{
	verticalPower = 7.5f;
	horizontalPower = 7.0f;
	verticalSpeed = 0;
	horizontalSpeed = 0;

	maxFallSpeed = -15.0f;
	maxverticalSpeed = 15.0f;
	maxhorizontalSpeed = 15.0f;
}

//------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------
Move::~Move()
{

}


//------------------------------------------------------
//�ݒ菈��
//------------------------------------------------------
//���Z�ړ���
void	Move::SetAddVec(float addVec)
{
	this->addVec = addVec;
}

//�W�����v�͂̐ݒ�
void	Move::SetJumpPow(float jumpPow)
{
	this->jumpPower = jumpPow;
}

//�������x�̐ݒ�
void	Move::SetFallSpeed(float fallSpeed)
{
	this->fallSpeed = fallSpeed;
}

//�d�͉����x�̐ݒ�
void	Move::SetGravity(float gravity)
{
	this->gravity = gravity;
}

//�d�͉����x���f�t�H���g�̒l�ɐݒ�
void	Move::SetDefaultGravity()
{
	this->gravity = this->defaultGravity;
}

//�f�[�^�̐ݒ�
void	Move::SetMoveDate(	const float& addVec, const float& jumpPow,
							const float& fallSpeed, const float& gravity)
{
	this->moveVec = K_Math::Vector3(0, 0, 0);
	this->addVec = addVec;
	this->jumpPower = jumpPow;
	this->fallSpeed = fallSpeed;
	this->gravity = gravity;
}

void	Move::SetHorizontal(float horizontal)
{
	horizontalPower = horizontal;
}
void	Move::SetVertical(float vertical)
{
	verticalPower = vertical;
}
//------------------------------------------------------
//�擾����
//------------------------------------------------------
//����ʂ��擾(�ύX�\)
K_Math::Vector3& Move::GetMoveVec()
{
	return moveVec;
}

//���Z�ړ��ʂ��擾
float	Move::GetAddVec()
{
	return addVec;
}

//�W�����v�͂̎擾
float	Move::GetJumpPow()
{
	return jumpPower;
}

//�������x�̎擾
float	Move::GetFallSpeed()
{
	return fallSpeed;
}

//�d�͉����x�̐ݒ�
float	Move::GetGravity()
{
	return gravity;
}
//!@brief	���������X�s�[�h�̎擾
float	Move::GetHorizontalSpeed()
{
	return horizontalSpeed;
}

//------------------------------------------------------
//���䏈��
//------------------------------------------------------
//!@brief	�������x�̐���
void	Move::ControlFallSpeed()
{
	if (fallSpeed <= maxFallSpeed)
	{
		fallSpeed = maxFallSpeed;
	}
}

//------------------------------------------------------
//����
//------------------------------------------------------
//�d�͓���
void	Move::GravityOperation(bool annulGravity)
{
	if (annulGravity == true)
	{
		moveVec.y = 0;
		fallSpeed = 0;
		return;
	}
	
	moveVec.y += fallSpeed;
	fallSpeed += gravity;

	ControlFallSpeed();
}

//�W�����v����
void	Move::JumpOperation()
{
	fallSpeed = jumpPower;

	//�W�����v�̐ݒ�Ɠ����ɃL�����N�^�[������������
	moveVec.y += fallSpeed;
}

//�����ړ�
void	Move::Horizontal()
{
	horizontalSpeed = horizontalPower;
	moveVec.x += horizontalSpeed;
}

//�����ړ�
void	Move::Vertical()
{
	fallSpeed = verticalPower;
	moveVec.y += fallSpeed;
}
