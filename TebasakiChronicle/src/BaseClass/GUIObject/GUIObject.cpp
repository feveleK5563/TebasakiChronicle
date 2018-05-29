#include "GUIObject.h"


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
	texture = new K_Graphics::Texture();
	texture->Initialize();
	texture->LoadImage("./data/image/Icon.png");
	object.SetImage(imageName, texture, true);
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

//�`�揈��
void	GUIObject::Render()
{
	object.GetImage().ImageDraw3D(object.GetPos(), object.GetAngle(), object.GetScale(), 0);
}


//!@brief �ʒu�̈ړ�����
//!@param[in] pos_ �ړ�������ʒu
void	GUIObject::SetPos(const K_Math::Vector3& pos_)
{
	object.SetPos(pos_);
}