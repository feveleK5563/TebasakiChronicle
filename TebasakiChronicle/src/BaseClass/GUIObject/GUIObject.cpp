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
	object.SetImage(imageName, texture, true);
	object.GetImage().CreateCharaChip(srcBox, 1, 1, false);

	isPosOffSet = true;
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
	
	//�I�t�Z�b�g���Ȃ��Ȃ�A�ړ��͍s��Ȃ�
	if (!isPosOffSet) { return; }
	object.SetPos(K_Math::Vector3(
		CST::GetPerspectiveCamera()->GetTerget().x + object.GetMoveVec().x, 
		CST::GetPerspectiveCamera()->GetTerget().y + object.GetMoveVec().y,
		CST::GetPerspectiveCamera()->GetTerget().z + object.GetMoveVec().z));
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

//!@brief �I�t�Z�b�g�t���O�ݒ�
//!@param[in] isOffSet �ʒu���I�t�Z�b�g�����邩�̃t���O(true:�I�t�Z�b�g������)
void	GUIObject::SetIsOffSetFlag(bool isOffSet)
{
	isPosOffSet = isOffSet;
}