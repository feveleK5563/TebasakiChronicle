#include "GUIObject.h"
#include "CameraList.h"

//-------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------
GUIObject::GUIObject(const std::string& imageName_,
	const K_Math::Vector3& pos_,
	const K_Math::Box2D& srcBox_)
	: imageName(imageName_)
	, srcBox(srcBox_)
{
	object.SetPos(pos_);
	object.SetAngle(K_Math::Vector3(0, 0, 0));
	object.SetScale(K_Math::Vector3(1, 1, 1));
	object.SetMoveVec(object.GetPos());

	texture = new K_Graphics::Texture();
	texture->Initialize();
	texture->LoadImage("./data/image/" + imageName + ".png");
	object.SetImage(texture, true);
	object.GetImage().CreateCharaChip(srcBox, 1, 1, false);


}

//�f�X�g���N�^
GUIObject::~GUIObject()
{
	if (texture != nullptr)
	{
		delete texture;
		texture = nullptr;
	}
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

//!@brief	�傫���̐ݒ�
//!@param[in]	scale �傫��
void	GUIObject::SetScale(const K_Math::Vector3& scale)
{
	object.SetScale(scale);
}