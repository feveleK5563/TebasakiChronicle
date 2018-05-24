#pragma once

#include "../src/Object/GameObject.h"
#include "K_Physics\BulletPhysics.h"
#include "../../../BaseClass/Collision/CollisionManager.h"
#include "../../Enemy/Enemy.h"

//----------------------------------------------------------------
//�J�����K��
//�T�v:�B�e�p�̃J�����ŁA�G���B�e���āA�X�L�����擾����
//�����:�����
//----------------------------------------------------------------
class CameraGun
{
public:
	CameraGun();
	~CameraGun();

	void	Chase(const K_Math::Vector3& targetPos);	//�G�̍��W���������ǔ�����
	void	RecieveData();
	bool	CheckUserData();

	void	Initailize();								//����������
	void	UpDate(const K_Math::Vector3& pPos);		//�X�V����
	void	Render();									//�`��

	void	SetPlayerPos(const K_Math::Vector3& pos);	//�v���C���[�̍��W�Ɠ�������
	void	SetCameraGun(bool isInjection);				//�J�����̑��x�̐ݒ�
	void	SetMoveSpeed(float moveSpeed);				//�ړ����x�̐ݒ�
	void	SetDirection(const Status::Direction& dir);	//�����̐ݒ�
	float 	GetDir();
	
	void	DataReset();

	//!@brief �J�����K�����󂯎�����X�L���f�[�^��n��
	//!@return skillAndCharaChip �X�L���̃f�[�^
	Enemy::SkillAndCharaChip& GetSkillAndCharaChip();

private:
	bool	CheckNowState(const Status::State& state);	//���݂̏�Ԃ𒲂ׂ�
	bool	CheckAddSpeed();

public:

	GameObject					object;			//�Q�[���I�u�W�F�N�g
private:
	K_Physics::CollisionShape*	shape;			//�`�̍쐬
	CollisionManager			cManager;		//�R���W�����̊Ǘ�

	int							targetNum;		//�^�[�Q�b�g�̔ԍ����i�[����
	Enemy::SkillAndCharaChip*	targetData;		//�^�[�Q�b�g�̃X�L���f�[�^���i�[����
};