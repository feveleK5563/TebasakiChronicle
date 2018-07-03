#pragma once
#include "K_Math\MyMathFanctions.h"

//-----------------------------------------------------
//Move�N���X
//�T�v:����ʂ����W�ɗ^����
//�����:�����
//-----------------------------------------------------
class Move
{
public:
	Move();
	Move(const K_Math::Vector3& vec, float add, float jumpPow, float fallSpeed, float gravity);
	~Move();

	//�ݒ菈��
	void	SetAddVec(float addVec);
	void	SetJumpPow(float jumpPow);
	void	SetFallSpeed(float fallSpeed);
	void	SetGravity(float gravity);
	void	SetDefaultGravity();
	void	SetHorizontal(float horizontal);
	void	SetVertical(float vertical);

	void	SetMoveDate(
		const float& addVec, const float& jumpPow,
		const float& fallSpeed, const float& gravity);

	//�擾����
	K_Math::Vector3& GetMoveVec();
	float	GetAddVec();
	float	GetJumpPow();
	float	GetFallSpeed();
	float	GetGravity();
	float	GetHorizontalSpeed();

	//!@brief	�������x�̐���
	void	ControlFallSpeed();

	//����
	void	GravityOperation(bool annulGravity);	//�d�͓���
	void	JumpOperation();						//�W�����v����
	void	Horizontal();		//�����ړ�
	void	Vertical();			//�����ړ�

	//!@brief	�����ړ��̒���
	//!@brief	���X��0�ɂ��Ă����A�����̈ړ����Ȃ����Ă����܂�
	void	RegulationHorizon();

private:
	K_Math::Vector3		moveVec;		//�ړ���
	float				addVec;			//���Z�ړ���(�L�����N�^�[�̈ړ����ɉ��Z����l)
	float				jumpPower;		//�W�����v��
	float				fallSpeed;		//�������x
	float				defaultGravity;	//�f�t�H���g�̏d�͉����x
	float				gravity;		//�d�͉����x
	float				verticalPower;	//�����̗�
	float				horizontalPower;//�����̗�
	float				verticalSpeed;	//�����̃X�s�[�h
	float				horizontalSpeed;//�����̃X�s�[�h

	float				maxFallSpeed;		//�ő嗎�����x
	float				maxverticalSpeed;	//�ő吂���X�s�[�h
	float				maxhorizontalSpeed;	//�ő吅���X�s�[�h
};