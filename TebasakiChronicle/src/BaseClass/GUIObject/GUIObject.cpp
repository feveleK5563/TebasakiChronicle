#include "GUIObject.h"
#include "../../CSTList.h"
//#include "CameraList.h"

//-------------------------------------------------
//!@brief	�R���X�g���N�^
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
	moveAmount = 0.0f;
	outCircleAngle = 0.0f;
	offsetSrcPos = K_Math::Vector2(0,0);

	object.SetPos(pos_);
	object.SetAngle(K_Math::Vector3(0, 0, angle));
	object.SetScale(K_Math::Vector3(1, 1, 1));
	object.SetMoveVec(object.GetPos());

	texture = CST::GetTexture(imageName);
	object.SetImage(texture, true);
	object.GetImage().CreateCharaChip(srcBox, animSheet, animSpeed, true);
}

GUIObject::GUIObject(
	const std::string& imageName,
	const std::string& filePath,
	const K_Math::Vector3& pos_,
	const K_Math::Box2D& srcBox_,
	const int animSheet,
	const float animSpeed 
)
	: imageName(imageName)
	, srcBox(srcBox_)
{
	rotateSpeed = 1.0f;
	angle = 0.0f;
	maxAngle = 360.0f;
	moveAmount = 0.0f;
	outCircleAngle = 0.0f;
	offsetSrcPos = K_Math::Vector2(0, 0);
	object.SetPos(pos_);
	object.SetAngle(K_Math::Vector3(0, 0, angle));
	object.SetScale(K_Math::Vector3(1, 1, 1));
	object.SetMoveVec(object.GetPos());

	CST::LoadAndGetTexture(imageName, filePath);
	texture = CST::GetTexture(imageName);
	object.SetImage(texture, true);
	object.GetImage().CreateCharaChip(srcBox, animSheet, animSpeed, true);
}
//-----------------------------------------------------------------------
//!@brief	�f�X�g���N�^
//-----------------------------------------------------------------------
GUIObject::~GUIObject()
{

}

//------------------------------------------------------------------------
//!@brief	�X�V����
//------------------------------------------------------------------------
void	GUIObject::UpDate()
{
	object.GetImage().Animation();
}

//------------------------------------------------------------------------
//!@brief	2D��Ԃɕ`�悷��
//------------------------------------------------------------------------
void	GUIObject::Render()
{
	object.GetImage().ImageDraw2D(object.GetPos(), object.GetAngle(), object.GetScale(), 0);
}

//------------------------------------------------------------------------
//!@brief	3D��Ԃɕ`�悷��
//------------------------------------------------------------------------
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
//!@brief	�摜�\�[�X�̃I�t�Z�b�g��
//!@param[in]	offsetSrcPos	�I�t�Z�b�g��(x,y)
void		GUIObject::SetOffsetSrcPos(const K_Math::Vector2& offsetSrcPos)
{
	this->offsetSrcPos = offsetSrcPos;
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
	moveCnt += 1;
	object.GetMove().SetAddVec(1);
}

//!@brief	�ړ��ʂ̐ݒ�
void		GUIObject::SetMoveAmount(const float moveAmount)
{
	this->moveAmount = moveAmount;
}

//!@brief	�O���̉�]��������
//!@param[in]	rotSpeed	��]���x(���W�A��)
void		GUIObject::OutCircleRotation(const float rotSpeed)
{
	this->outCircleAngle += rotSpeed;
}

//!@brief	�O����]�ł�GUI�ʒu�̐ݒ�
//!@param[in]	baseRotPos	��]�̊�ʒu
//!@param[in]	distance	��ʒu����̋���
void		GUIObject::SetOutCirclePos(const K_Math::Vector3& baseRotPos,const float distance)
{
	SetPos(K_Math::Vector3(baseRotPos.x + cosf(outCircleAngle) * distance, baseRotPos.y + sinf(outCircleAngle) * distance, 0));
}

//!@brief	�O���ł̊p�x�̐ݒ�
//!@param[in]	angle	�O���ł̊p�x(���W�A��)
void		GUIObject::SetOutCircleAngle(const float angle)
{
	outCircleAngle = angle;
}

//!@brief	�����摜�`���p
//!@param[in]	numStr	����������
void		GUIObject::RenderNumberImage(const char* numStr)
{
	K_Math::Vector2 distance = object.GetPos();
	for (int i = 0; i < (int)strlen(numStr); ++i)
	{
		int code = ((unsigned char)numStr[i]);
		int fx = (code - '0') * srcBox.w;
		int fy = 0 * srcBox.h;
		GetGameObject().GetImage().GetNowAnimationCharaChip()->chip = K_Math::Box2D(fx, fy, srcBox.w, srcBox.h);
		GetGameObject().GetImage().ImageDraw2D(K_Math::Vector3(distance.x, distance.y, 0), object.GetAngle(), object.GetScale(), 0);
		distance.x += offsetSrcPos.x;
		distance.y += offsetSrcPos.y;
	}
}