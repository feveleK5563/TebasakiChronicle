#include "Player.h"


//--------------------------------------------------------------
//�T�v:�v���C���[�̎���
//�����:�����
//--------------------------------------------------------------

//-----------------------------------------------
//�R���X�g���N�^
//-----------------------------------------------
Player::Player()
{

}

//-----------------------------------------------
//�f�X�g���N�^
//-----------------------------------------------
Player::~Player()
{
	CC::RemoveCollisionShape(&shape);
	CC::RemoveCollisionShape(&shape2);
}

//������
void	Player::Initliaze()
{
	//�I�u�W�F�N�g�̏�����
	object.GetStatus().SetStatusData(
		Status::State::Active,
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(1, 1, 1),
		Status::Direction::Right,
		1,
		0
	);

	motion = Idle;
	motionCnt = 0;
	maxFrame = 60;
	minJumpForce = 1.5f;

	//�摜�̐���
	object.SetImage("Player", CST::LoadAndGetTexture("Player", "data/image/resource2.png"), true);
	//Motion�̏�Ԃ̏��ԂłȂ���΃A�j���[�V�������Ή����Ȃ�
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 0, 32, 48), 6, 6, true);		//Idle
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 48, 32, 48), 10, 8, true);	//Walk
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 48, 32, 48), 10, 6, true);	//Run
	object.GetImage().CreateCharaChip(K_Math::Box2D(192, 0, 32, 48), 2, 1, false);	//Jump
	object.GetImage().CreateCharaChip(K_Math::Box2D(256, 0, 32, 48), 2, 3, false);	//Fall
	object.GetImage().CreateCharaChip(K_Math::Box2D(320, 0, 32, 48), 2, 6, false);	//TakeOff
	object.GetImage().CreateCharaChip(K_Math::Box2D(320, 0, 32, 48), 2, 6, false);	//Landing
	object.GetImage().CreateCharaChip(K_Math::Box2D(320, 48, 32, 48), 4, 4, false);	//SkillUse
	object.GetImage().CreateCharaChip(K_Math::Box2D(320, 48, 32, 48), 4, 4, false);	//SkillMoveUse //�L�����`�b�v�̕ύX�L
	object.GetImage().CreateCharaChip(K_Math::Box2D(320, 48, 32, 48), 4, 4, false);	//SkillAirUse //�L�����`�b�v�̕ύX�L
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 96, 32, 48), 4, 4, false);	//CameraGunUse //�L�����`�b�v�̕ύX�L
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 96, 32, 48), 4, 4, false);	//CameraGunMoveUse //�L�����`�b�v�̕ύX�L
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 96, 32, 48), 4, 4, false);	//CameraGunAirUse //�L�����`�b�v�̕ύX�L

	//Move�̏d�͂̐ݒ�
	object.GetMove().SetAddVec(4.f);
	object.GetMove().SetJumpPow(9.f);

	//�J�����K���̏�����
	cameraGun.Initailize();

	//���肶���̐ݒ�-------------------------------
	//�{�b�N�X�̌`�̐���
	shape = CC::CreateBoxShape(16, 24, 1);
	shape2 = CC::CreateBoxShape(15, 1, 1);

	//��������[�`]�ŃR���W�����⍄�̂��쐬
	cManager.CreateBaseCollisionData(shape, object.GetPos(), object.GetAngle(), true);	//�x�[�X
	cManager.CreateSubCollisionData(shape, CollisionMask::EnemyCollision | CollisionMask::TakeDamagePlayer, CollisionMask::PlayerCollision, object.GetPos()); //��_��
	cManager.CreateSubCollisionData(shape2, CollisionMask::Ground, CollisionMask::Non, K_Math::Vector3(0, -24, 0)); //����
	cManager.CreateSubCollisionData(shape2, CollisionMask::Ground, CollisionMask::Non, K_Math::Vector3(0, 24, 0)); //����

	//�R���W�����ɏ�����������
	cManager.SetSubCollisionUserData(0, &object.GetStatus());
}

//�X�V
void	Player::UpDate()
{
	object.GetMove().GetMoveVec() = K_Math::Vector3(0, 0, 0);
	motionCnt++;

	ChangeDir();			//���͂ɉ����Č�����ς���
	//--------------------------------------------------------
	//�v�l&���[�V�����̈ړ�
	Think();
	Move();

	//�J�����K��-----------------------
	ShotCameraGun();				//���߂炪�������
	ReverseCameraGun();				//�J���������߂�
	cameraGun.UpDate(object.GetPos());

	//�X�L���̎g�p---------------------
	RegistSkill();
	skillManager.UpDate();

	//�����蔻�蓮��-------------------
	cManager.MoveBaseCollision(object.GetMoveVec(), object.GetDirection(), false);

	//�ʒu��������---------------------
	object.SetPos(cManager.GetBaseCollisionObjectPosition());

	//�A�j���[�V����-------------------
	object.GetImage().Animation();
}

//-----------------------------------------------------------------
//�`��
//-----------------------------------------------------------------
void	Player::Render()
{
	cameraGun.Render();
	object.GetImage().ImageDraw3D(object.GetPos(), object.GetAngle(), object.GetScale(), object.GetDirection());
	
	//�X�L���̕`��----------------------------
	skillManager.Render();
}

//�_���[�W��^����
int		Player::GiveDamege()
{
	return object.GetAttackPoint();
}

//���͂ɉ����Č�����ς���
void	Player::ChangeDir()
{
	//���X�e�B�b�N�̓|��Ă���[��
	float stickDepth = INPUT::GetStickPower(VpadIndex::Pad0, K_Input::VpadStick::L);
	//�E������0�x�Ƃ�����]�x
	float stickAngle = INPUT::GetStickRotation(VpadIndex::Pad0, K_Input::VpadStick::L);

	if (stickDepth != 0)
	{
		if ((K_Math::DegToRad(-90) < stickAngle) && (stickAngle < K_Math::DegToRad(90)))
		{
			object.SetDirection(Status::Direction::Right);
		}
		else
		{
			object.SetDirection(Status::Direction::Left);
		}
	}
}


//�J�����K����O�ɔ�΂�
void	Player::ShotCameraGun()
{
	//�B�e�{�^���������ƃJ������O���Ɏˏo����
	if (INPUT::IsPressButton(VpadIndex::Pad0,K_Input::VpadButton::L1))
	{
		if (object.GetMoveVec().x != 0)
		{
			cameraGun.SetMoveSpeed(7.0f);
		}
		cameraGun.SetDirection(object.GetDirection());	//�����𓯊�������
		cameraGun.SetCameraGun(true);
	}
}

//�J�����K�������ɖ߂�
void	Player::ReverseCameraGun()
{
	//�B�e�{�^���𗣂�
	if (INPUT::IsReaveButton(VpadIndex::Pad0,K_Input::VpadButton::L1))
	{
		//---------------------------------------------------
		if (&cameraGun.GetSkillAndCharaChip() != nullptr)
		{
			skillManager.ChangeRegistFlag(true);	//�o�^���[�h��
			//�J�����K������X�L���f�[�^���󂯎��
			skillManager.ReceiveSkillAndCharaChip(cameraGun.GetSkillAndCharaChip());
		}
		//�J�����}�[�J�[���v���C���[�̈ʒu�ɖ߂�
		cameraGun.SetCameraGun(false);
	}
}


//�W�����v����
void	Player::JumpMove()
{
	if (INPUT::IsPressButton(VpadIndex::Pad0,K_Input::VpadButton::R1))
	{
		object.GetMove().JumpOperation();
	}
	if (INPUT::IsReaveButton(VpadIndex::Pad0, K_Input::VpadButton::R1) && (object.GetMove().GetFallSpeed() > 1.5f))
	{
		object.GetMove().SetFallSpeed(1.5f);
	}
}




//----------------------------------------------------------
//�v�l����(���[�V��������)
void	Player::Think()
{
	Motion nowMotion = motion;
	
	//���[�V�����̕ύX�݂̂��s��
	switch (nowMotion) {
	case Idle:	//�ҋ@
		if (controller.IsLStickInput()) { nowMotion = Walk; }
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::R1)) { nowMotion = TakeOff; }
		ChangeSkillMotion(nowMotion,SkillUse);
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = CameraGunUse; }
		break;
	case Walk:	//����
		//1�t���[��
		if (motionCnt >= maxFrame / 3)
		{
			nowMotion = Run;
		}
		if (!cManager.CheckHitSubCollisionObejct(Foot)) { nowMotion = Fall; }
		if (!controller.IsLStickInput()) { nowMotion = Idle; }
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::R1)) { nowMotion = TakeOff; }
		ChangeSkillMotion(nowMotion, SkillMoveUse);
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = CameraGunMoveUse; }
		break;
	case Run:	//����
		if (!cManager.CheckHitSubCollisionObejct(Foot)) { nowMotion = Fall; }
		if (!controller.IsLStickInput()) { nowMotion = Idle; }
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::R1)) { nowMotion = TakeOff; }
		ChangeSkillMotion(nowMotion, SkillMoveUse);
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = CameraGunMoveUse; }
		break;
	case Jump:	//�㏸��
		if (object.GetMove().GetFallSpeed() <= 0.0f) { nowMotion = Fall; }
		if (cManager.CheckHitSubCollisionObejct(Head)) { nowMotion = Fall; }
		ChangeSkillMotion(nowMotion, SkillAirUse);
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = CameraGunAirUse; }
		break;
	case Fall:	//������
		if (cManager.CheckHitSubCollisionObejct(Foot)) { nowMotion = Landing; }
		ChangeSkillMotion(nowMotion, SkillAirUse);
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = CameraGunAirUse; }
		break;
	case TakeOff:	//��ԏu��
		if (motionCnt >= maxFrame / maxFrame)
		{
			nowMotion = Jump;
		}
		break;
	case Landing:	//���n�̏u��
		if (motionCnt >= maxFrame / maxFrame)
		{
			nowMotion = Idle;
		}
		break;
	case SkillUse:		//�X�L���g�p��
	case SkillMoveUse:	//�ړ����ɃX�L���g�p
	case SkillAirUse:	//�ړ����ɃX�L���g�p
		if (motionCnt > maxFrame / 6)
		{
			nowMotion = Idle;
		}
		break;
	case CameraGunUse:		//�J�����K���\��
	case CameraGunMoveUse:	//�J�����K���ړ����\��
	case CameraGunAirUse:	//�J�����K���󒆍\��
		if (motionCnt > maxFrame / 6)
		{
			nowMotion = Idle;
		}
		break;
	}
	//���[�V�����̍X�V
	UpDateMotion(nowMotion);
}


//---------------------------------------------------
//���[�V�����ɑΉ���������
void	Player::Move()
{
	//�d�͉���
	switch (motion) {
	default:

		//�㏸���������͑����ɒn�ʂ��Ȃ�
		if (object.GetMoveVec().y > 0.0f ||
			!cManager.CheckHitSubCollisionObejct(Foot))
		{
			object.GetMove().GravityOperation(cManager.CheckHitSubCollisionObejct(Foot));
		}
		else //�n�ʂƐڂ��Ă���
		{
			object.GetMoveVec().y = 0.0f;
		}

		break;
		//�d�͂𖳌��ɂ��郂�[�V����(���͂Ȃ�)
	case Non:
		break;
	}
	//�ړ� & �J�����K����SkillUse���͎g�p���Ȃ�
	switch (motion) {
	default:
		controller.UpDate(object.GetMove());
		break;
		//�ړ�����𖳎����郂�[�V����
	case SkillUse:
		//**********�X�L���g�p���͈ړ��������邩�͖���**********
		break;
	}

	//-------------------------------------------------
	//���[�V�����ŗL�̏���
	switch (motion) {
	case Idle:		//�ҋ@
		break;
	case Walk:		//����
		break;
	case Run:		//����
		break;
	case Jump:		//�㏸��
		if (motionCnt == 0)
		{
			object.GetMove().JumpOperation();
		}
		if (INPUT::IsReaveButton(VpadIndex::Pad0, K_Input::VpadButton::R1) && (object.GetMove().GetFallSpeed() > minJumpForce))
		{
			object.GetMove().SetFallSpeed(minJumpForce);
		}
		break;
	case Fall:		//������
		break;
	case TakeOff:	//��ԏu��
		break;
	case Landing:	//���n
		break;
	case SkillUse:		//�X�L���g�p��
	case SkillMoveUse:	//�ړ����̃X�L���g�p
	case SkillAirUse:	//�󒆂̃X�L���g�p
		if (motionCnt == 0)
		{
			UseSkill();
		}
		break;
	case CameraGunUse:		//�J�����K���\��
	case CameraGunMoveUse:	//�J�����K���ړ����\��
	case CameraGunAirUse:	//�J�����K���󒆍\��
		break;
	}
}


//------------------------------------------------
//���[�V�����̍X�V
bool	Player::UpDateMotion(const Motion& nowMotion)
{
	if (motion == nowMotion) { return false; }
	//�X�V����
	motion = nowMotion;
	motionCnt = 0;
	object.GetImage().ChangeAnimationPattern(motion, true);
	return true;
}



//------------------------------------
//�v���C���[�����o�^���g�p���𔻒f

//!@brief �X�L���̓o�^����
void	Player::RegistSkill()
{
	//0�� = Y
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::Y))
	{
		skillManager.RegistSkillData(0);
	}
	//1�� = X
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::X))
	{
		skillManager.RegistSkillData(1);
	}
	//2�� = B
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::B))
	{
		skillManager.RegistSkillData(2);
	}
	//3�� = A
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::A))
	{
		skillManager.RegistSkillData(3);
	}
}

//!@brief �X�L���̎g�p����
void		Player::UseSkill()
{
	//0�� = Y
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::Y))
	{
		skillManager.UseSkillData(0, object);
	}
	//1�� = X
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::X))
	{
		skillManager.UseSkillData(1, object);
	}
	//2�� = B
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::B))
	{
		skillManager.UseSkillData(2, object);
	}
	//3�� = A
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::A))
	{
		skillManager.UseSkillData(3, object);
	}
}


//!@brief �X�L���̏�ԕψ�
void	Player::SkillState(Motion& nowMotion,const Motion& nextMotion,const int& btnNum)
{
	if (!skillManager.CheckRegistFlag())
	{
		if (skillManager.CheckExistSkill(btnNum))
		{
			nowMotion = nextMotion;
		}
	}
}

//!@brief �X�L���̏�Ԃ�
void	Player::ChangeSkillMotion(Motion& nowMotion,const Motion& nextMotion)
{
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::A))
	{
		SkillState(nowMotion, nextMotion, 3);
	}
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::B))
	{
		SkillState(nowMotion, nextMotion, 2);
	}
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::X))
	{
		SkillState(nowMotion, nextMotion, 1);
	}
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::Y))
	{
		SkillState(nowMotion, nextMotion, 0);
	}
}