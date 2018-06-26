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
		Death,				//���S
	};

	
	//�R���W�����̎��
	enum CollisionKind
	{
		Base = 0,	//��
		Foot,		//����
		Head,		//����
	};

	//�A�j���[�V�������[�V����
	enum class AnimState
	{
		Non = -1,
		Idle = 0,		//�ҋ@
		Walk,			//�o����
		RightRun,		//�E��
		LeftRun,		//����
		Jump,			//�W�����v
		Fall,			//����
		Landing,		//���n
		GunRightRun,	//�E���J�����K��
		GunLeftRun,		//�����J�����K��
		GunJump,		//�W�����v�J�����K��
		GunFall,		//�����J�����K��
		GunIdle,		//�ҋ@���̃J�����K��
		Damage,			//�_���[�W
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

	//!@brief	�I�u�W�F�N�g�̎擾
	GameObject&	GetGameObject();

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

	//!@brief �m�b�N�o�b�N����
	//!@param[in] ����̍��W
	void	KnockBack(const K_Math::Vector3& pos_);

	//!@brief	�_�ŏ���
	bool	Flashing();

	//!@brief	�A�j���[�V������Ԃ̕ύX
	//!@param[in]	animState	�A�j���[�V�������
	void	ChangeAnimState(const AnimState& animState);
	
	//!@brief	�A�j���[�V������Ԃ̍X�V
	//!@param[in]	animState	�A�j���[�V�������
	void	UpDateAnimState(const AnimState& animState);

	//!@brief	�A�j���[�V�����؂�ւ�
	//!@brief	2�̃A�j���[�V������؂�ւ��鏈��
	//!@param[in]	animState1	�A�j���[�V�������1
	//!@param[in]	animState2	�A�j���[�V�������2
	//!@param[in]	frameCnt	�؂�ւ���t���[����
	void	SwitchAnimState(const AnimState& animState1,const AnimState& animState2,const float frameCnt);

private:
	//--------------------------------
	//�G�t�F�N�g

private:
	GameObject		object;				//�Q�[���I�u�W�F�N�g
	Status*			enemyData;			//�G�̃X�e�[�^�X
private:
	Motion			motion;				//���[�V����
	int				preMotionCnt;		//�O�̃��[�V�����J�E���g
	int				motionCnt;			//���[�V�����̃J�E���g
	CharaController	controller;			//�R���g���[���[
	CameraGun		cameraGun;			//�J�����K��
	SkillManager	skillManager;		//�X�L��
	int				maxFrame;			//�ő�̃t���[����
	float			minJumpForce;		//�Œ���̃W�����v
	int				invicibleCnt;		//���G���ԃJ�E���g
	int				maxInvicibleTime;	//�ő喳�G����
	AnimState		preAnimState;		//1�O�̃A�j���[�V�������
	AnimState		animState;			//�A�j���[�V�����̏��
public:
	K_Physics::CollisionShape*	shape;		//�x�[�X�R���W�����̌`��
	K_Physics::CollisionShape*	shape2;		//�����Ɠ���p�R���W�����̌`��
	CollisionManager			cManager;	//�R���W�����̊Ǘ���

	K_Graphics::Texture*		texture;

};

