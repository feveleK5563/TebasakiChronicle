#include "Move.h"

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

}
Move::Move(const K_Math::Vector3& vec, float add, float jumpPow, float fallSpeed, float gravity) :
	moveVec(vec),
	addVec(add),
	jumpPower(jumpPow),
	fallSpeed(fallSpeed),
	defaultGravity(-0.5f),
	gravity(gravity)
{

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
}

//�W�����v����
void	Move::JumpOperation()
{
	fallSpeed = jumpPower;

	//�W�����v�̐ݒ�Ɠ����ɃL�����N�^�[������������
	moveVec.y += fallSpeed;
}