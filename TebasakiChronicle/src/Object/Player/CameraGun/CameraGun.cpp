#include "CameraGun.h"

//---------------------------------------------------------------
//�T�v:�J�����K���̎���
//�����:�����
//---------------------------------------------------------------

//-------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------
CameraGun::CameraGun() 
{
	effectCreateFlag = true;
}

//-------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------
CameraGun::~CameraGun()
{
	CC::RemoveCollisionShape(&shape);
}

//-------------
//����������
//-------------
void	CameraGun::Initailize()
{
	//�X�e�[�^�X�̐ݒ�
	object.GetStatus().SetStatusData(
		Status::State::Non,
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(1, 1, 1),
		Status::Direction::Left,
		1,
		1);

	object.GetMove().SetAddVec(5.0f);

	//�����̏�����
	//�����̓f�t�H���g�Ő���������
	object.SetImage(CST::LoadAndGetTexture("target", "data/image/target.png"), true);
	object.GetImage().CreateCharaChip(K_Math::Box2D(0, 0, 32, 32), 1, 1, false);

	//�{�b�N�X�̌`�̐���
	shape = CC::CreateBoxShape(10, 10, 1);

	//��������[�`]�ŃR���W�����⍄�̂��쐬
	cManager.CreateBaseCollisionData(shape, object.GetPos(), object.GetAngle(), false);
	cManager.CreateSubCollisionData(shape, CollisionMask::EnemyCamCollision, CollisionMask::CameraGunCollision, object.GetPos());

	//�R���W�����ɏ�����������
	cManager.SetSubCollisionUserData(0, &object.GetState());
	targetNum = -1;
	targetData = nullptr;
}

//-----------------------------------
//�X�V����
//-----------------------------------
void	CameraGun::UpDate(const K_Math::Vector3& pPos)
{	
	//�J�����������̂Ƃ�
	if (CheckNowState(Status::State::Non))
	{ 
		//�v���C���[�ɒǏ]����
		SetPlayerPos(pPos);
	}
	else if (CheckNowState(Status::State::Active))
	{
		//�J�����K�����L���̂Ƃ�
		//�Փ˂����ۂ̋���
		if (CheckUserData())
		{
			K_Math::Vector3	tarPos = *targetData->pos;
			Chase(tarPos);
			//�G�t�F�N�g******
			//if (effectCreateFlag)
			//{
			//	//���̃G�t�F�N�g
			//	Effect::CreateEffect(EffectName::Effect1, object.GetPos());
			//	effectCreateFlag = false;
			//}
		}
		else
		{
			//�Փ˂��Ă��Ȃ��ꍇ�A�����Ă�������ɂ����ݑ�����
			object.GetPos() += object.GetMoveVec();
			float addSpeed = -GetDir() * 0.05f;
			if (CheckAddSpeed())
			{
				object.GetMoveVec().x += addSpeed;
			}
			RecieveData();

			//�G�t�F�N�g���쐬�ł���悤�ɂ���
			//effectCreateFlag = true;
		}
	}
	
	//�A�j���[�V��������
	object.GetImage().Animation();

	//�J�����K���̈ړ�
	cManager.MoveBaseCollision(object.GetMoveVec(), object.GetDirection(), true);
	//�R���W�����̈ʒu�̓���
	object.GetPos() = cManager.GetBaseCollisionObjectPosition();
	object.GetPos().z = -1.f;
}



//---------------------------------
//�`��
//---------------------------------
void	CameraGun::Render()
{
	if (object.GetStatus().GetState() == Status::Non) { return; }
	object.GetImage().ImageDraw3D(object.GetPos(), object.GetAngle(), object.GetScale(), 1);
}


//�v���C���[�̈ʒu�Ɠ���
void	CameraGun::SetPlayerPos(const K_Math::Vector3& pos)
{
	cManager.SetBaseCollisionObjectPosition(pos);
	object.SetMoveVec(K_Math::Vector3(0, 0, 0));
}


//�ǔ�����
void	CameraGun::Chase(const K_Math::Vector3& targetPos)
{
	//�G�ƃJ�����K���Ƃ̋���
	K_Math::Vector3 targetVec = targetPos - object.GetPos();
	object.GetMoveVec().x = targetVec.x / object.GetMove().GetAddVec();
	object.GetMoveVec().y = targetVec.y / object.GetMove().GetAddVec();
}

//�G�Ƃ̏Փ˂������ꍇ�A�X�L���f�[�^���擾����
void	CameraGun::RecieveData()
{
	//�����蔻�菈��
	std::vector<K_Physics::CollisionTag*> data = cManager.GetConflictionObjectsTag(0);
	if (data.size() > 0)
	{
		targetNum = data[0]->tagIndex;
		targetData = (Enemy::SkillAndCharaChip*)data[0]->userData;
	}
}


//���[�U�[�f�[�^�����邩�̃`�F�b�N
bool	CameraGun::CheckUserData()
{
	if (targetData == nullptr)
		return false;

	std::vector<K_Physics::CollisionTag*> data = cManager.GetConflictionObjectsTag(0);
	if (data.size() > 0)
	{
		for (auto it : data)
		{
			if (targetNum == it->tagIndex)
			{
				return true;
			}
		}
	}

	SetCameraGun(false);
	return false;
}


//�x�N�g���̐ݒ�
//��Ԃ̐ݒ�
void	CameraGun::SetCameraGun(bool isInjection)
{
	if (isInjection)
	{
		object.SetState(Status::State::Active);
		object.SetMoveVec(K_Math::Vector3(GetDir() * object.GetMove().GetAddVec(), 0, 0));
	}
	else
	{
		object.SetMoveVec(K_Math::Vector3(0, 0, 0));
		object.SetState(Status::State::Non);
		object.GetMove().SetAddVec(5.0f);	//���ɖ߂�
		DataReset();
	}
}

//�J�����K���̈ړ����x�̐ݒ�
void	CameraGun::SetMoveSpeed(float moveSpeed)
{
	object.GetMove().SetAddVec(moveSpeed);
}


//�����̐ݒ�
void	CameraGun::SetDirection(const Status::Direction& dir)
{
	object.SetDirection(dir);
}

//������Ԃ�
float	CameraGun::GetDir()
{
	if (object.GetDirection() == Status::Direction::Left)
	{
		return -1.0f;
	}

	return 1.0f;
}


//���݂̏�Ԃ𒲂ׂ�
bool	CameraGun::CheckNowState(const Status::State& state)
{
	if (object.GetState() == state)
	{
		return true;
	}
	return false;
}

//moveVec���߂�Ȃ��悤�ɂ���
//�i�s�����̋t�̈ړ��ʂɂȂ��Ă��Ȃ��ꍇ�A���̂܂�AddSpeed����
//�t�����ɂȂ�����Afalse��Ԃ����߁A�ړ��ʂ�0.0�ɂ���
bool	CameraGun::CheckAddSpeed()
{
	if (object.GetDirection() == Status::Direction::Left)
	{
		if (object.GetMoveVec().x >= 0.0f)
		{
			object.GetMoveVec().x = 0.0f;
			return false;
		}
	}
	if (object.GetDirection() == Status::Direction::Right)
	{
		if (object.GetMoveVec().x <= 0.0f)
		{
			object.GetMoveVec().x = 0.0f;
			return false;
		}
	}
	return true;
}

void	CameraGun::DataReset()
{
	targetNum = -1;
	targetData = nullptr;
}


//!@brief �J�����K�����󂯎�����X�L���f�[�^��n��
//!@return skillAndCharaChip �X�L���̃f�[�^
Enemy::SkillAndCharaChip& CameraGun::GetSkillAndCharaChip()
{
	return *targetData;
}