#include "Player.h"
#include "../src/Effect/Effect.h"
#include "../src/Helper.h"


//--------------------------------------------------------------
//�T�v:�v���C���[�̎���
//�����:�����
//--------------------------------------------------------------

//-----------------------------------------------
//�R���X�g���N�^
//-----------------------------------------------
Player::Player()
{
	enemyData = nullptr;
	shutterSource.LoadSound("Shutter", "data/sounds/camera/shutter.ogg", ALLREAD);
	jumpSource.LoadSound("Jump", "data/sounds/player/jump.ogg", ALLREAD);
	damageSource.LoadSound("Damage", "data/sounds/player/damage.ogg", ALLREAD);
	RunSource.LoadSound("Run", "data/sounds/player/walk.ogg", ALLREAD);
	landingSource.LoadSound("landing", "data/sounds/player/landing.ogg", ALLREAD);
	cameraGunShotSource.LoadSound("cameraShot", "data/sounds/player/gunShot.ogg", ALLREAD);
	
	soundEngine.AddSource(shutterSource);
	soundEngine.AddSource(jumpSource);
	soundEngine.AddSource(damageSource);
	soundEngine.AddSource(RunSource);
	soundEngine.AddSource(landingSource);
	soundEngine.AddSource(cameraGunShotSource);

	asset = new Asset(new AssetSound("data/SoundLoadData/playerSound.txt"));
	asset->LoadEffect("data/EffectLoadData/playerEffect.txt");
}

//-----------------------------------------------
//�f�X�g���N�^
//-----------------------------------------------
Player::~Player()
{
	CC::RemoveCollisionShape(&shape);
	CC::RemoveCollisionShape(&shape2);

	Memory::SafeDelete(texture);

	soundEngine.DeleteSound("Shutter");
	soundEngine.DeleteSound("Jump");
	soundEngine.DeleteSound("Damage");
	soundEngine.DeleteSound("Run");
	soundEngine.DeleteSound("landing");
	soundEngine.DeleteSound("cameraShot");

	Memory::SafeDelete(asset);
}

//-------------------------------------------------------------------
//������
void	Player::Initliaze()
{
	//�I�u�W�F�N�g�̏�����
	object.GetStatus().SetStatusData(
		Status::State::Active,
		K_Math::Vector3(100, 50, 0),
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(1, 1, 1),
		Status::Direction::Right,
		1,
		10
		);

	motion = Idle;
	motionCnt = 0;
	maxFrame = 60;
	minJumpForce = 1.5f;
	invicibleCnt = 0;
	maxInvicibleTime = 120;		//���G����
	object.GetStatus().SetMinLife(0);
	object.GetStatus().SetMaxLife(10);
	preTargetDir = object.GetDirection();
	targetDir = object.GetDirection();


	texture = new K_Graphics::Texture();
	texture->Initialize();
	texture->LoadImage("./data/image/Player/player.png");
	//�摜�̐���
	object.SetImage(texture, true);
	//AnimState�̏�Ԃ̏��ԂłȂ���΃A�j���[�V�������Ή����Ȃ�
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 0, 64, 64), 6, 8, true);				//Idle
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 64, 64, 64), 3, 1, false);			//Walk(�o����)
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 64 * 2, 64, 64), 11, 4, true);		//Run
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 64 * 3, 64, 64), 5, 4, false);		//Jump
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 64 * 4, 64, 64), 5, 4, false);		//fall
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 64 * 3, 64, 64), 1, 1, false);		//TakeOff
	object.GetImage().CreateCharaChip(K_Math::Box2D(64 * 5, 64 * 5, 64, 64), 1, 3, false);	//landing
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 64 * 5, 64, 64), 10, 4, true);		//GunRun
	object.GetImage().CreateCharaChip(K_Math::Box2D(64, 64 * 6, 64, 64), 5, 4, false);		//GunJump
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 64 * 7, 64, 64), 5, 4, false);		//GunFall
	object.GetImage().CreateCharaChip(K_Math::Box2D(64 * 3, 64, 64, 64), 1, 5, false);		//GunIdle
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 64 * 8, 64, 64), 5, 4, false);		//Damage
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 64 * 9, 64, 64), 10, 4, true);		//GunRunBack

	//Move�̏d�͂̐ݒ�
	object.GetMove().SetAddVec(4.f);
	object.GetMove().SetJumpPow(9.f);

	//�J�����K���̏�����
	cameraGun.Initailize();

	//���肶���̐ݒ�-------------------------------
	//�{�b�N�X�̌`�̐���
	shape = CC::CreateBoxShape(12, 30, 1);
	shape2 = CC::CreateBoxShape(11, 1, 1);
	
	//��������[�`]�ŃR���W�����⍄�̂��쐬
	cManager.CreateBaseCollisionData(shape, object.GetPos(), object.GetAngle(), true);	//�x�[�X
	cManager.CreateSubCollisionData(shape, CollisionMask::EnemyCollision | CollisionMask::TakeDamagePlayer, CollisionMask::PlayerCollision, K_Math::Vector3(0,0,0)); //��_��
	cManager.CreateSubCollisionData(shape2, CollisionMask::Ground, CollisionMask::Non, K_Math::Vector3(0, -30, 0)); //����
	cManager.CreateSubCollisionData(shape2, CollisionMask::Ground, CollisionMask::Non, K_Math::Vector3(0, 30, 0)); //����

	//�R���W�����ɏ�����������
	cManager.SetSubCollisionUserData(0, &object.GetStatus());
}

//---------------------------------------------------------------
//�X�V
void	Player::UpDate()
{
	motionCnt++;

	//--------------------------------------------------------
	//�v�l&���[�V�����̈ړ�
	Think();
	Move();

	//�J�����K��-----------------------
	if (object.GetState() != Status::State::Death)
	{
		ShotCameraGun();				//���߂炪�������
		ReverseCameraGun();				//�J���������߂�
	}
	cameraGun.UpDate(object.GetPos());

	//�X�L���̎g�p---------------------
	if (skillManager.CheckRegistFlag())
	{
		RegistSkill();
	}
	skillManager.UpDate(object);

	//�����蔻�蓮��-------------------
	cManager.MoveBaseCollision(object.GetMoveVec(), object.GetDirection(), false);

	//�ʒu��������---------------------
	object.SetPos(cManager.GetBaseCollisionObjectPosition());
	cManager.SetBaseCollisionObjectPosition(object.GetPos());

	//�A�j���[�V����-------------------
	object.GetImage().Animation();

	if (invicibleCnt > 0)
	{
		invicibleCnt -= 1;
	}

	//���C�t��0�ȉ��ɂȂ�
	if (object.GetLife() <= 0)
	{
		object.SetState(Status::State::Death);
	}

	//�����͂������ōs���Ă��܂�
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::A))
	{
		asset->GetSound("GOGOGO2").PlaySE();
		asset->GetEffect(static_cast<int>(EffectName::Effect2)).CreateEffect(EffectName::Effect2, object.GetPos());
	}
}

//-----------------------------------------------------------------
//�`��
//-----------------------------------------------------------------
void	Player::Render()
{
	//�J��������̕`��
	cameraGun.Render();
	//�X�L���̕`��----------------------------
	skillManager.Render();

	if (Flashing())
	{
		object.GetImage().ImageDraw3D(object.GetPos(), object.GetAngle(), object.GetScale(), object.GetDirection());
	}
}

//�_���[�W��^����
int		Player::GiveDamage()
{
	return object.GetAttackPoint();
}

//�_���[�W�̎󂯂鏈��
void	Player::ReciveDamage()
{
	std::vector<K_Physics::CollisionTag*> data = cManager.GetConflictionObjectsTag(CollisionKind::Base);

	if (data.size() > 0)
	{
		int index = data[0]->tagIndex;
		enemyData = (Status*)data[0]->userData;
		object.GetStatus().GetLife() -= enemyData->GetAttackPoint();
		KnockBack(enemyData->GetPos());
	}
}

//!@brief	�I�u�W�F�N�g�̎擾
GameObject&	Player::GetGameObject()
{
	return object;
}

//���͂ɉ����Č�����ς���
void	Player::ChangeDir()
{
	//���X�e�B�b�N�̓|��Ă���[��
	float stickDepth = INPUT::GetStickPower(VpadIndex::Pad0, K_Input::VpadStick::L);
	//�E������0�x�Ƃ�����]�x
	float stickAngle = INPUT::GetStickRotation(VpadIndex::Pad0, K_Input::VpadStick::L);

	if (stickDepth != 0 && K_Math::DegToRad(-90) != stickAngle && stickAngle != K_Math::DegToRad(90))
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

		//�J�����K��������
		cameraGunShotSource.PlaySE();
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
			if (*cameraGun.GetSkillAndCharaChip().behaviorId != 0)
			{
				skillManager.ChangeRegistFlag(true);	//�o�^���[�h��
				//�J�����K������X�L���f�[�^���󂯎��
				skillManager.ReceiveSkillAndCharaChip(cameraGun.GetSkillAndCharaChip());
				
				//���̃G�t�F�N�g*******
				//�J��������̃V���b�^�[
				//Effect::CreateEffect(EffectName::Effect1, cameraGun.object.GetPos());
				//�J�������񂩂�̔��ˌ��I�Ȃ���
				//�v���C���[�̓����ɂ��Ă��Ăق���
				//Effect::CreateEffect(EffectName::Effect1, K_Math::Vector3(cameraGun.GetDir() * 24 + object.GetPos().x, object.GetPos().y + 5, object.GetPos().z));

				//�V���b�^�[��
				shutterSource.PlaySE();
			}
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
		ChangeDamageMotion(nowMotion);
		if (controller.IsLStickInput()) { nowMotion = Walk; }
		if (cManager.CheckHitSubCollisionObejct(Foot))
		{
			if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::R1)) { nowMotion = TakeOff; }
		}
		ChangeSkillMotion(nowMotion,SkillUse);
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = CameraGunUse; }
		if (!cManager.CheckHitSubCollisionObejct(Foot)) { nowMotion = Fall; }
		break;
	case Walk:	//����
		ChangeDamageMotion(nowMotion);
		if (motionCnt >= maxFrame / (maxFrame / 2))
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
		ChangeDamageMotion(nowMotion);		
		if (!cManager.CheckHitSubCollisionObejct(Foot)) { nowMotion = Fall; }
		if (!controller.IsLStickInput()) { nowMotion = Idle; }
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::R1)) { nowMotion = TakeOff; }
		ChangeSkillMotion(nowMotion, SkillMoveUse);
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = CameraGunMoveUse; }
		break;
	case Jump:	//�㏸��
		ChangeDamageMotion(nowMotion);		
		if (cManager.CheckHitSubCollisionObejct(Foot)) { nowMotion = Fall; }
		if (object.GetMove().GetFallSpeed() <= 0.0f) { nowMotion = Fall; }
		if (cManager.CheckHitSubCollisionObejct(Head)) { nowMotion = Fall; }
		ChangeSkillMotion(nowMotion, SkillAirUse);
		if (INPUT::IsStayButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = CameraGunAirUse; }
		break;
	case Fall:	//������
		ChangeDamageMotion(nowMotion);		
		if (cManager.CheckHitSubCollisionObejct(Foot)) { nowMotion = Landing; }
		ChangeSkillMotion(nowMotion, SkillAirUse);
		if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = CameraGunAirUse; }
		break;
	case TakeOff:	//��ԏu��
		ChangeDamageMotion(nowMotion);
		if (motionCnt >= maxFrame / maxFrame)
		{
			if (INPUT::IsStayButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = CameraGunAirUse; }
			else { nowMotion = Jump; }
		}
		break;
	case Landing:	//���n�̏u��
		ChangeDamageMotion(nowMotion);
		if (motionCnt >= maxFrame / maxFrame)
		{
			if (INPUT::IsStayButton(VpadIndex::Pad0, VpadButton::L1)){ nowMotion = CameraGunUse; }
			else { nowMotion = Idle; }
		}
		break;
	case SkillUse:		//�X�L���g�p��
	case SkillMoveUse:	//�ړ����ɃX�L���g�p
		ChangeDamageMotion(nowMotion);
		if (motionCnt > maxFrame / 6)
		{
			nowMotion = Idle;
		}
		if (controller.IsLStickInput()) { nowMotion = Run; }
		if (!cManager.CheckHitSubCollisionObejct(Foot)) { nowMotion = Fall; }
		if (cManager.CheckHitSubCollisionObejct(Head)) { nowMotion = Fall; }
		if (object.GetMove().GetFallSpeed() > 0.0f) { nowMotion = Jump; }
		break;
	case SkillAirUse:	//�󒆂ɃX�L���g�p
		ChangeDamageMotion(nowMotion);
		if (cManager.CheckHitSubCollisionObejct(Head)) { nowMotion = Fall; }
		if (cManager.CheckHitSubCollisionObejct(Foot)) 
		{ 
			nowMotion = Landing;
		}
		else
		{
			if (motionCnt > maxFrame / 6)
			{
				nowMotion = Fall;
			}
		}
		if (object.GetMove().GetFallSpeed() > 0.0f) { nowMotion = Jump; }
		break;
	case CameraGunUse:		//�J�����K���\��
		ChangeDamageMotion(nowMotion);
		if (INPUT::IsReaveButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = Idle; }
		if (controller.IsLStickInput()) { nowMotion = CameraGunMoveUse; }
		if (cManager.CheckHitSubCollisionObejct(Foot))
		{
			if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::R1)) { nowMotion = TakeOff; }
		}
		break;
	case CameraGunMoveUse:	//�J�����K���ړ����\��
		ChangeDamageMotion(nowMotion);
		//�J�����K���g�p�{�^����������Ă����
		if (INPUT::IsStayButton(VpadIndex::Pad0, VpadButton::L1))
		{
			if (!controller.IsLStickInput()) { nowMotion = CameraGunUse; }
		}
		else
		{
			nowMotion = Run;
		}
		if (cManager.CheckHitSubCollisionObejct(Foot))
		{
			if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::R1)) { nowMotion = TakeOff; }
		}
		else
		{
			if (INPUT::IsStayButton(VpadIndex::Pad0, VpadButton::L1)) { nowMotion = CameraGunAirUse; }
			else { nowMotion = Fall; }
		}
		break;
	case CameraGunAirUse:	//�J�����K���󒆍\��
		ChangeDamageMotion(nowMotion);
		if (cManager.CheckHitSubCollisionObejct(Head)) { nowMotion = Fall; }
		if (cManager.CheckHitSubCollisionObejct(Foot)){	nowMotion = Landing; }
		if (INPUT::IsStayButton(VpadIndex::Pad0, VpadButton::L1))
		{
			if (cManager.CheckHitSubCollisionObejct(Foot))
			{
				nowMotion = CameraGunUse;
			}
		}
		else
		{
			if (cManager.CheckHitSubCollisionObejct(Foot))
			{
				nowMotion = Landing;
			}
			else
			{
				nowMotion = Fall;
			}
		}
		break;
	case DamageRecive:		//�_���[�W�󂯂�
		//30�t���[���o�߂������`�F�b�N
		if (motionCnt > maxFrame / 2)
		{
			if (cManager.CheckHitSubCollisionObejct(Foot))
			{
				//�{���͂����Ńp�����[�^��������Ȃ�
				object.SetMoveVec(K_Math::Vector3(0, 0, 0));
				object.GetMove().SetFallSpeed(0.0f);
				nowMotion = Landing;
			}
			else
			{
				nowMotion = Fall;
			}
		}
		//�n�ʂƏՓ˂������`�F�b�N
		if (cManager.CheckHitSubCollisionObejct(Foot))
		{
			//�{���͂����Ńp�����[�^��������Ȃ�
			object.SetMoveVec(K_Math::Vector3(0, 0, 0));
			object.GetMove().SetFallSpeed(0.0f);
			nowMotion = Landing;
		}
		break;
	}
	//����ł��邩����
	if (object.IsDead())
	{
		nowMotion = Death;
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
		object.SetMoveVec(K_Math::Vector3(0, 0, 0));
		//�㏸���������͑����ɒn�ʂ��Ȃ�
		if (object.GetMoveVec().y > 0.0f || !cManager.CheckHitSubCollisionObejct(Foot))
		{
			object.GetMove().GravityOperation(cManager.CheckHitSubCollisionObejct(Foot));
		}
		if (object.GetMoveVec().y <= -15.0f)
		{
			object.GetMoveVec().y = -15.0f;
		}
		break;
		//�d�͂𖳌��ɂ��郂�[�V����(���͂Ȃ�)
	case Non:
		break;
	}

	//�ړ��R���g���[���[
	switch (motion) {
	default:
		controller.UpDate(object.GetMove());
		break;
		//�R���g���[���[�ňړ��𖳌��ɂ���
	case Non:
	case DamageRecive:	//�_���[�W�󂯂Ă�ۂ͔������Ȃ�
	case Death:
		break;
	}

	switch (motion) {
	default:
		ChangeDir();			//���͂ɉ����Č�����ς���
		break;
	case Non:
	case DamageRecive:
	case Death:
	case TakeOff:
	case Landing:
	case CameraGunUse:
	case CameraGunMoveUse:
	case CameraGunAirUse:
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
		if (motionCnt == 0)
		{
			//RunSource.PlaySE();	//���ނ��������̗�
		}
		break;
	case Jump:		//�㏸��
		if (motionCnt == 0)
		{
			object.GetMove().JumpOperation();
			//���̃G�t�F�N�g����
			//Effect::CreateEffect(EffectName::Effect1, object.GetPos()-K_Math::Vector3(0,24,0));
	
			jumpSource.PlaySE();		//�W�����v��
		}
		//�W�����v�͂̒���
		if (INPUT::IsReaveButton(VpadIndex::Pad0, K_Input::VpadButton::R1) && (object.GetMove().GetFallSpeed() > minJumpForce))
		{
			object.GetMove().SetFallSpeed(minJumpForce);
		}
		break;
	case Fall:		//������
		if (motionCnt == 0)
		{
			if (preMotion != Motion::DamageRecive)
			{
				object.GetMove().SetFallSpeed(0);
			}
		}
		//�_���[�W�̉��ړ����c��
		if (preMotion == Motion::DamageRecive)
		{
			object.GetMove().Horizontal();
			object.GetMove().RegulationHorizon();
		}
		break;
	case TakeOff:	//��ԏu��
		break;
	case Landing:	//���n
		if (motionCnt == 0)
		{
			object.GetMove().SetFallSpeed(0);
			//���n��
			landingSource.PlaySE();
		}
		break;
	case SkillUse:		//�X�L���g�p��
	case SkillMoveUse:	//�ړ����̃X�L���g�p
		if (motionCnt == 0)
		{
			UseSkill();
		}
		break;
	case SkillAirUse:	//�󒆂̃X�L���g�p
		if (motionCnt == 0)
		{
			UseSkill();
		}
		if (preMotion == DamageRecive)
		{
			object.GetMove().Horizontal();
		}
		break;
	case CameraGunUse:		//�J�����K���\��
	case CameraGunMoveUse:	//�J�����K���ړ����\��
		break;
	case CameraGunAirUse:	//�J�����K���󒆍\��
		if (preMotion == DamageRecive)
		{
			object.GetMove().Horizontal();
		}
		if (motionCnt == 0)
		{
			if (cManager.CheckHitSubCollisionObejct(Foot))
			{
				object.GetMove().JumpOperation();
				//���̃G�t�F�N�g����
				//Effect::CreateEffect(EffectName::Effect1, object.GetPos()-K_Math::Vector3(0,24,0));
			}
		}
		//�W�����v�͂̒���
		if (INPUT::IsReaveButton(VpadIndex::Pad0, K_Input::VpadButton::R1) && (object.GetMove().GetFallSpeed() > minJumpForce))
		{
			object.GetMove().SetFallSpeed(minJumpForce);
		}
		break;
	case DamageRecive:		//�_���[�W����
		//�_�ł���t���O��On�ɂ���
		if (motionCnt == 0)
		{
			object.GetMove().SetFallSpeed(0.0f);
			ReciveDamage();
			invicibleCnt = maxInvicibleTime;
			object.GetMove().Vertical();	//�W�����v��p��^����

			damageSource.PlaySE(0.7f);		//�_���[�W��
		}
		object.GetMove().Horizontal();
		break;
	case Death:
		break;
	}

	AnimState	nowAnimState = animState;
	//------------------------------------------------
	//���[�V�����ŗL�̃A�j���[�V����
	switch (motion) {
	case Idle:
		ChangeAnimState(AnimState::Idle);
		break;
	case Walk:
		ChangeAnimState(AnimState::Walk);
		break;
	case Run:
		if (motionCnt == 0)
		{
			motionCnt = preMotionCnt;
		}
		ChangeAnimState(AnimState::Run);
		break;
	case Jump:
		ChangeAnimState(AnimState::Jump);
		break;
	case Fall:
		ChangeAnimState(AnimState::Fall);
		break;
	case Landing:
		ChangeAnimState(AnimState::Landing);
		break;
	case CameraGunUse:
		ChangeAnimState(AnimState::GunIdle);
		break;
	case CameraGunMoveUse:
		if (motionCnt == 0)
		{
			motionCnt = preMotionCnt;
		}
		CameraGunMoveAnimation();
		break;
	case CameraGunAirUse:
		if (object.GetMove().GetFallSpeed() > 0)
		{
			ChangeAnimState(AnimState::GunJump);
		}
		else
		{
			ChangeAnimState(AnimState::GunFall);
		}
		//�J�����K�������E�ǂ���ɂ��邩���f
		preTargetDir = targetDir;
		targetDir = this->IsTargetDir(cameraGun.object.GetPos());
		if (preTargetDir != targetDir)
		{
			if (motionCnt >= maxFrame / 10)
			{
				object.SetDirection(targetDir);
				motionCnt = 0;
			}
		}
		if (targetDir != object.GetDirection())
		{
			object.SetDirection(targetDir);
		}
		break;
	case SkillUse:		
		ChangeAnimState(AnimState::Idle);
		break;
	case SkillMoveUse:	
		if (motionCnt == 0)
		{
			motionCnt = preMotionCnt;
		}
		ChangeAnimState(AnimState::GunRun);
		break;
	case SkillAirUse:
		if (object.GetMove().GetFallSpeed() > 0)
		{
			ChangeAnimState(AnimState::Jump);
		}
		else
		{
			ChangeAnimState(AnimState::Fall);
		}
		break;
	case DamageRecive:
		ChangeAnimState(AnimState::Damage);
		break;
	case Death:
		ChangeAnimState(AnimState::Idle);
		break;
	}
	UpDateAnimState(nowAnimState);

}


//------------------------------------------------
//���[�V�����̍X�V
bool	Player::UpDateMotion(const Motion& nowMotion)
{
	if (motion == nowMotion) { return false; }
	//1�O�̃��[�V������ێ����A���̃��[�V������
	preMotion = motion;
	motion = nowMotion;
	//1�O�̃��[�V�������Ԃ�ێ�
	preMotionCnt = motionCnt;
	motionCnt = 0;
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


//!@brief �_���[�W���[�V�����փ`�F���W
void	Player::ChangeDamageMotion(Motion& motion)
{
	if (invicibleCnt <= 0)
	{
		if (cManager.CheckHitSubCollisionObejct(CollisionKind::Base)) { motion = DamageRecive; }
	}
}


//!@brief �m�b�N�o�b�N����
//!@param[in] ����̍��W
void	Player::KnockBack(const K_Math::Vector3& pos_)
{
	object.GetMove().SetVertical(6.0f);
	if (object.GetPos().x > pos_.x)
	{
		object.GetMove().SetHorizontal(+3.0f);
	}
	else
	{
		object.GetMove().SetHorizontal(-3.0f);
	}
}


//!@brief	�_�ŏ���
bool	Player::Flashing()
{
	if (invicibleCnt > 0)
	{
		if ((invicibleCnt / 4) % 2 == 0)
		{
			return false;
		}
	}
	return true;
}


//!@brief	�A�j���[�V������Ԃ̕ύX
//!@param[in]	animState	�A�j���[�V�������
void	Player::ChangeAnimState(const AnimState& animState)
{
	this->animState = animState;
}

//!@brief	�A�j���[�V������Ԃ̍X�V
//!@param[in]	animState	�A�j���[�V�������
void	Player::UpDateAnimState(const AnimState& animState)
{
	if (this->animState != animState)
	{
		return;
	}
	this->preAnimState = this->animState;
	this->animState = animState;
	object.GetImage().ChangeAnimationPattern(static_cast<int>(animState), true);
}


//!@brief	�A�j���[�V�����؂�ւ�
//!@brief	2�̃A�j���[�V������؂�ւ��鏈��
//!@param[in]	animState1	�A�j���[�V�������1
//!@param[in]	animState2	�A�j���[�V�������2
//!@param[in]	frameCnt	�؂�ւ���t���[����
void	Player::SwitchAnimState(const AnimState& animState1, const AnimState& animState2, const float frameCnt)
{
	if (motionCnt == 0)
	{
		motionCnt = preMotionCnt;
	}
	if ((motionCnt / frameCnt) == 0)
	{
		ChangeAnimState(animState1);
	}
	if ((motionCnt / frameCnt) == 1)
	{
		ChangeAnimState(animState2);
	}
	if ((motionCnt / frameCnt) >= 2)
	{
		motionCnt = 0;
	}
}


////////////////////////////////////////////////////////////////////////////////////
//�J�����K���֘A
////////////////////////////////////////////////////////////////////////////////////

//!@brief	�^�[�Q�b�g�ʒu�����E�ǂ���ɂ��邩���f
//!@param[in]	targetPos	�^�[�Q�b�g�ʒu
//!@return	�^�[�Q�b�g�ʒu�������̈ʒu��荶�Ȃ� Left
//!@return	�^�[�Q�b�g�ʒu�������̈ʒu���E�Ȃ� Right
const Status::Direction	Player::IsTargetDir(const K_Math::Vector3 targetPos)
{
	float offset = 0.0f;
	if (object.GetDirection() == Status::Direction::Left){	offset = -10.0f; }
	else{	offset = 10.0f; }

	if (object.GetPos().x < targetPos.x + offset)
	{
		return Status::Direction::Right;
	}
	else
	{
		return Status::Direction::Left;
	}
}

//!@brief	�J�����K����Move�A�j���[�V����
//!@brief	�v���C���[���J�����K���������đ����Ă���ۂ̌����A�j���[�V�����̐؂�ւ��Ȃ�
void	Player::CameraGunMoveAnimation()
{
	//�J�����K�������E�ǂ���ɂ��邩���f
	preTargetDir = targetDir;
	targetDir = this->IsTargetDir(cameraGun.object.GetPos());
	if (targetDir == Status::Direction::Left)
	{
		//�E����������A���Ό���
		if (controller.IsStickRight())
		{
			//std::cout << "�������]" << std::endl;
			ChangeAnimState(AnimState::GunRunBack);
		}
		else
		{
			ChangeAnimState(AnimState::GunRun);
		}
	}
	else
	{
		//������������A���Ό���
		if (controller.IsStickLeft())
		{
			//std::cout << "�������]" << std::endl;
			ChangeAnimState(AnimState::GunRunBack);
		}
		else
		{
			ChangeAnimState(AnimState::GunRun);
		}
	}
	if (preTargetDir != targetDir)
	{
		if (motionCnt >= maxFrame / 10)
		{
			object.SetDirection(targetDir);
			motionCnt = 0;
		}
	}
	if (targetDir != object.GetDirection())
	{
		object.SetDirection(targetDir);
	}
}