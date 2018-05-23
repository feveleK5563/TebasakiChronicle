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
										const bool					ishitground,
										const bool					doground):
	cShape(shape),
	deleteTime(deletetime),
	isHitGround(ishitground)
{
	colmanager.CreateGroundCollisionData(shape, setpos, K_Math::Vector3(0, 0, 0), doground);
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

	colmanager.SetSubCollisionUserData(0, &gameObject.GetState());
}

//�f�X�g���N�^
TemporaryCollision::~TemporaryCollision()
{
	CC::RemoveCollisionShape(&cShape);
}

//-----------------------------------------------------------------------------
//�摜�Ǘ��҂𐶐����A�����ɃL�����`�b�v��ݒ肷��
void TemporaryCollision::SetImageManagerAndCharaChip(	const std::string&			texName,
														K_Graphics::Texture*	texture,
														const K_Math::Box2D&			src,
														int						sheet,
														float					spd,
														bool					isroop)
{
	gameObject.SetImage(texName, texture);
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
		(timeCnt >= deleteTime) ||											//���Ԍo�߂ŏ���
		(isHitGround == true && colmanager.CheckHitBaseCollisionObject()))	//�n�`�ƐڐG���ď�����ꍇ�̔���
	{
		return true;
	}
	++timeCnt;
	
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