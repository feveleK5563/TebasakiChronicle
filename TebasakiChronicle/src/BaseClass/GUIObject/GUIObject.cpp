#include "GUIObject.h"
#include "../../CSTList.h"
//#include "CameraList.h"

//-------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------
GUIObject::GUIObject(const std::string& imageName_,
	const K_Math::Vector3& pos_,
	const K_Math::Box2D& srcBox_,
	const int animSheet,
	const float animSpeed)
	: imageName(imageName_)
	, srcBox(srcBox_)
{
	rotateSpeed = 1.0f;
	angle = 0.0f;
	maxAngle = 360.0f;

	object.SetPos(pos_);
	object.SetAngle(K_Math::Vector3(0, 0, angle));
	object.SetScale(K_Math::Vector3(1, 1, 1));
	object.SetMoveVec(object.GetPos());

	texture = CST::GetTexture(imageName);
	object.SetImage(texture, true);
	object.GetImage().CreateCharaChip(srcBox, animSheet, animSpeed, true);
}

//�f�X�g���N�^
GUIObject::~GUIObject()
{

}
//�X�V����
void	GUIObject::UpDate()
{
	object.GetImage().Animation();
}

//!@brief	2D��Ԃɕ`�悷��
void	GUIObject::Render()
{
	object.GetImage().ImageDraw2D(object.GetPos(), object.GetAngle(), object.GetScale(), 0);
}


//!@brief	3D��Ԃɕ`�悷��
void	GUIObject::Render3D()
{
	object.GetImage().ImageDraw3D(object.GetPos(), object.GetAngle(), object.GetScale(), object.GetDirection());
}

//!@brief �ʒu�̈ړ�����
//!@param[in] pos_ �ړ�������ʒu
void	GUIObject::SetPos(const K_Math::Vector3& pos_)
{
	object.SetPos(pos_);
}

//!@brief	�ʒu�̈ړ�
//!@param[in] moveVec �ړ���
void	GUIObject::AddVec(const K_Math::Vector3& moveVec)
{
	object.SetPos(object.GetPos() + moveVec);
}

//!@brief	��]�p�x�̐ݒ�
//!@param[in]	angle	�p�x��(x,y,z)
void	GUIObject::SetAngle(const K_Math::Vector3& angle)
{
	object.SetAngle(angle);
}

//!@brief	�傫���̐ݒ�
//!@param[in]	scale �傫��
void	GUIObject::SetScale(const K_Math::Vector3& scale)
{
	object.SetScale(scale);
}


//!@brief	GameObject�̎擾
//!@return	�Q�[���I�u�W�F�N�g
GameObject&	GUIObject::GetGameObject()
{
	return object;
}

//!@brief	��]���x�̐ݒ�
//!@param[in]	ratateSpeed_ ��]���x
void		GUIObject::SetRotateSpeed(const float rotateSpeed_)
{
	rotateSpeed = rotateSpeed_;
}

//!@brief	��]�p�x�̐ݒ�
//!@param[in]	rotateAngle	��]�p�x
void		GUIObject::SetRotateAngle(const float rotateAngle)
{
	angle = rotateAngle;
}

//!@brief	��]
void		GUIObject::Rotation()
{
	object.SetAngle(K_Math::Vector3(0, 0, angle));
	angle += rotateSpeed;
	if (rotateSpeed < 0.0f)
	{
		if (angle >= maxAngle)
		{
			angle = 0;
		}
	}
	else
	{
		if (angle <= -maxAngle)
		{
			angle = 0;
		}
	}
}

//!@brief	�ړ�(1�t���[�����Z)
void		GUIObject::AddVec()
{
	moveCnt++;
	object.GetMove().SetAddVec(1);
}

//!@brief	�ړ��ʂ̐ݒ�
void		GUIObject::SetMoveAmount(const float moveAmount)
{
	this->moveAmount = moveAmount;
}

//!@brief	�����摜�`���p
//!@param[in]	numStr	����������
void		GUIObject::RenderNumberImage(const char* numStr)
{
	int dx = object.GetPos().x;
	int dy = object.GetPos().y;
	for (int i = 0; i < (int)strlen(numStr); ++i)
	{
		int code = ((unsigned char)numStr[i]);
		int fx = (code - '0') * 16;
		int fy = 0;
		K_Math::Vector3 drawPos = K_Math::Vector3(dx, dy, 0);
		K_Math::Box2D src = K_Math::Box2D(fx, fy, 16, 16);
		GetGameObject().GetImage().GetNowAnimationCharaChip()->chip = src;
		GetGameObject().GetImage().ImageDraw2D(drawPos, object.GetAngle(), object.GetScale(), 0);
		dx += 8 + 3;
	}
}