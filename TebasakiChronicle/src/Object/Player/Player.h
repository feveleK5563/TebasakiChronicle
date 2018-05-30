#pragma once
#include "../src/Object//Player/CameraGun/CameraGun.h"
#include "../src/Object/Player/CharaController/CharaController.h"
#include "../src/Object/Player/Skill/SkillManager.h"


//--------------------------------------------------------------------
//�v���C���[
//�T�v:�v���C���[��p
//�����:�����
//--------------------------------------------------------------------
class Player
{
public:
	//���[�V����
	enum Motion
	{
		Non = -1,	//�Ȃ�
		Idle = 0,	//�ҋ@
		Walk,		//����
		Run,		//����
		Jump,		//�㏸��
		Fall,		//������
		TakeOff,	//��ԑO
		Landing,	//���n
		SkillUse,		//��~���ɃX�L���g�p
		SkillMoveUse,	//�ړ����ɃX�L���g�p
		SkillAirUse,	//�󒆂ŃX�L���g�p
		CameraGunUse,		//�J�����K����~���ɍ\��
		CameraGunMoveUse,	//�J�����K���ړ����ɍ\��
		CameraGunAirUse,	//�J�����K���󒆂ō\��
		DamageRecive,		//�_���[�W�󂯂�
	};

	//�R���W�����̎��
	enum CollisionKind
	{
		Base = 0,	//��
		Foot,		//����
		Head,		//����
	};

public:
	Player();
	~Player();

	void	Initliaze();	//������
	void	UpDate();		//�X�V
	void	Render();		//�`��

	//�_���[�W��^����
	int		GiveDamage();
	//�_���[�W�̎󂯂鏈��
	void	ReciveDamage();
private:
	void	ChangeDir();		//���͂ɉ����Č�����ς���
	void	ShotCameraGun();	//�J�����K�����΂�
	void	ReverseCameraGun();	//�J�����K����߂�
	void	JumpMove();			//�W�����v

	void	Think();	//�v�l����(���[�V��������)
	void	Move();		//���[�V�����ɑΉ���������
	bool	UpDateMotion(const Motion& nowMotion);	//���[�V�����̍X�V

private:
	
	//!@brief �X�L���̓o�^����
	void	RegistSkill();
	//!@brief �X�L���̎g�p����
	void	UseSkill();

	//!@brief �X�L���̏�ԕψ�
	void	SkillState(Motion& nowMotion,const Motion& nextMotion,const int& btnNum);
	//!@brief �X�L���̏�Ԃ�
	void	ChangeSkillMotion(Motion& nowMotion,const Motion& nextMotion);

	//!@brief �_���[�W���[�V�����փ`�F���W
	void	ChangeDamageMotion(Motion& motion);

public:
	GameObject		object;			//�Q�[���I�u�W�F�N�g
	Status* enemyData;
private:
	Motion			motion;			//���[�V����
	int				motionCnt;		//���[�V�����̃J�E���g
	CharaController	controller;		//�R���g���[���[
	CameraGun		cameraGun;		//�J�����K��
	SkillManager	skillManager;	//�X�L��
	int				maxFrame;		//�ő�̃t���[����
	float			minJumpForce;	//�Œ���̃W�����v
	int				invicibleCnt;	//���G���ԃJ�E���g
	int				maxInvicibleTime;//�ő喳�G����
public:
	K_Physics::CollisionShape*	shape;		//�x�[�X�R���W�����̌`��
	K_Physics::CollisionShape*	shape2;		//�����Ɠ���p�R���W�����̌`��
	CollisionManager			cManager;	//�R���W�����̊Ǘ���
};