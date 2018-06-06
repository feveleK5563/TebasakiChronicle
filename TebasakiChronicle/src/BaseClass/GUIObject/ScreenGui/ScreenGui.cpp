#include "GUIObject.h"
#include "CameraList.h"

//-------------------------------------------------
//コンストラクタ
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

//デストラクタ
GUIObject::~GUIObject()
{
	if (texture != nullptr)
	{
		delete texture;
		texture = nullptr;
	}
}
//更新処理
void	GUIObject::UpDate()
{
	object.GetImage().Animation();
}

//!@brief	2D空間に描画する
void	GUIObject::Render()
{
	object.GetImage().ImageDraw2D(object.GetPos(), object.GetAngle(), object.GetScale(), 0);
}


//!@brief	3D空間に描画する
void	GUIObject::Render3D()
{
	object.GetImage().ImageDraw3D(object.GetPos(), object.GetAngle(), object.GetScale(), object.GetDirection());
}

//!@brief 位置の移動処理
//!@param[in] pos_ 移動させる位置
void	GUIObject::SetPos(const K_Math::Vector3& pos_)
{
	object.SetPos(pos_);
}

//!@brief	位置の移動
//!@param[in] moveVec 移動量
void	GUIObject::AddVec(const K_Math::Vector3& moveVec)
{
	object.SetPos(object.GetPos() + moveVec);
}

//!@brief	大きさの設定
//!@param[in]	scale 大きさ
void	GUIObject::SetScale(const K_Math::Vector3& scale)
{
	object.SetScale(scale);
}