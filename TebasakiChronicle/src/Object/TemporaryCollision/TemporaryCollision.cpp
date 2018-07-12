#include "TemporaryCollision.h"

//�R���X�g���N�^
//�R���W�����̌`�����delete����
TemporaryCollision::TemporaryCollision(	K_Physics::CollisionShape*	shape,
										const CollisionMask&		mmask,
										const CollisionMask&		gmask,
										const K_Math::Vector3&		setpos,
										const K_Math::Vector3&		movevec,
										const Status::Direction&	dir,
										const int					damage,
										const int					deletetime,
										const float					gravitySize,
										const bool					ishitground):
	cShape(shape),
	isHitGround(ishitground)
{
	colmanager.CreateBaseCollisionData(shape, setpos, K_Math::Vector3(0, 0, 0), false);
	colmanager.CreateSubCollisionData(shape, mmask, gmask, K_Math::Vector3(0, 0, 0));

	gameObject.GetStatus().SetStatusData(
		Status::State::Active,
		setpos,
		K_Math::Vector3(0, 0, 0),
		K_Math::Vector3(1, 1, 1),
		dir,
		damage,
		0);
	gameObject.GetMove().GetMoveVec() = movevec;
	gameObject.GetMove().SetGravity(gravitySize);

	timeCnt.SetEndTime(deletetime);
	colmanager.SetSubCollisionUserData(0, &gameObject.GetState());
}

//�f�X�g���N�^
TemporaryCollision::~TemporaryCollision()
{
	CC::RemoveCollisionShape(&cShape);
}

//-----------------------------------------------------------------------------
//�摜�Ǘ��҂𐶐����A�����ɃL�����`�b�v��ݒ肷��
void TemporaryCollision::SetImageManagerAndCharaChip(	K_Graphics::Texture*	texture,
														const K_Math::Box2D&	src,
														int						sheet,
														float					spd,
														bool					isroop)
{
	gameObject.SetImage(texture);
	gameObject.GetImage().CreateCharaChip(src, sheet, spd, isroop);
}

//-----------------------------------------------------------------------------
//�X�V(���ł���ۂ�true���Ԃ�)
bool TemporaryCollision::Update()
{
	//����
	if (Extinction())
	{
		return true;
	}

	//�R���W�����̓���
	gameObject.GetMove().GravityOperation(true);
	colmanager.MoveBaseCollision(	gameObject.GetMove().GetMoveVec(),
									gameObject.GetStatus().GetDirection(),
									true);
	gameObject.GetPos() = colmanager.GetBaseCollisionObjectPosition();

	//�A�j���[�V�����̍X�V
	if (&gameObject.GetImage() != nullptr)
	{
		gameObject.GetImage().Animation();
	}

	return false;
}

//-----------------------------------------------------------------------------
//���Ńt���O�𗧂Ă�
bool TemporaryCollision::Extinction()
{
	if ((gameObject.GetStatus().GetState() != Status::State::Active) ||		//�O���ɂ����State��Active�ȊO�ɂ���Ă��������
		timeCnt.IsTimeEnd() ||												//���Ԍo�߂ŏ���
		(isHitGround == true && colmanager.CheckHitBaseCollisionObject()))	//�n�`�ƐڐG���ď�����ꍇ�̔���
	{
		return true;
	}
	timeCnt.Run();
	
	return false;
}

//-----------------------------------------------------------------------------
//�`��
void TemporaryCollision::Render()
{
	//�A�j���[�V�����̍X�V
	if (&gameObject.GetImage() != nullptr)
	{
		gameObject.GetImage().ImageDraw3D(	gameObject.GetStatus().GetPos(),
											gameObject.GetStatus().GetAngle(),
											gameObject.GetStatus().GetScale(),
											gameObject.GetStatus().GetDirection());
	}
}