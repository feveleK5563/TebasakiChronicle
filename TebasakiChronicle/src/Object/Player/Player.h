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
		SkillRegist,//�X�L���o�^��
		SkillUse,	//�X�L���g�p��
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


private:
	void	ChangeDir();		//���͂ɉ����Č�����ς���
	void	ShotCameraGun();	//�J�����K�����΂�
	void	ReverseCameraGun();	//�J�����K����߂�
	void	JumpMove();			//�W�����v

	void	Think();	//�v�l����(���[�V��������)
	void	Move();		//���[�V�����ɑΉ���������
	bool	UpDateMotion(const Motion& nowMotion);	//���[�V�����̍X�V

	//!@brief �X�L���̂��߂̃{�^��
	void	SkillBtnDown();

	//!@brief �X�L���̓o�^����
	void	RegistSkill();
	//!@brief �X�L���̎g�p����
	void	UseSkill();

private:
	Motion			motion;		//���[�V����
	int				motionCnt;	//���[�V�����̃J�E���g
	GameObject		object;		//�Q�[���I�u�W�F�N�g
	CharaController	controller;	//�R���g���[���[
	CameraGun		cameraGun;	//�J�����K��
	int				maxFrame;	//�ő�̃t���[����
	SkillManager	skillManager;//�X�L��

public:
	K_Physics::CollisionShape*	shape;		//�x�[�X�R���W�����̌`��
	K_Physics::CollisionShape*	shape2;		//�����Ɠ���p�R���W�����̌`��
	CollisionManager			cManager;	//�R���W�����̊Ǘ���
};