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

	void	SetMoveDate(
		const float& addVec, const float& jumpPow,
		const float& fallSpeed, const float& gravity);

	//�擾����
	K_Math::Vector3& GetMoveVec();
	float	GetAddVec();
	float	GetJumpPow();
	float	GetFallSpeed();
	float	GetGravity();

	//����
	void	GravityOperation(bool annulGravity);	//�d�͓���
	void	JumpOperation();						//�W�����v����

private:
	K_Math::Vector3		moveVec;		//�ړ���
	float				addVec;			//���Z�ړ���(�L�����N�^�[�̈ړ����ɉ��Z����l)
	float				jumpPower;		//�W�����v��
	float				fallSpeed;		//�������x
	float				defaultGravity;	//�f�t�H���g�̏d�͉����x
	float				gravity;		//�d�͉����x
};