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
	object.SetImage(imageName, texture, true);
	object.GetImage().CreateCharaChip(srcBox, 1, 1, false);

	isPosOffSet = true;
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
	
	//オフセットしないなら、移動は行わない
	if (!isPosOffSet) { return; }
	object.SetPos(K_Math::Vector3(
		CST::GetPerspectiveCamera()->GetTerget().x + object.GetMoveVec().x, 
		CST::GetPerspectiveCamera()->GetTerget().y + object.GetMoveVec().y,
		CST::GetPerspectiveCamera()->GetTerget().z + object.GetMoveVec().z));
}

//描画処理
void	GUIObject::Render()
{
	object.GetImage().ImageDraw3D(object.GetPos(), object.GetAngle(), object.GetScale(), 0);
}


//!@brief 位置の移動処理
//!@param[in] pos_ 移動させる位置
void	GUIObject::SetPos(const K_Math::Vector3& pos_)
{
	object.SetPos(pos_);
}

//!@brief オフセットフラグ設定
//!@param[in] isOffSet 位置をオフセットさせるかのフラグ(true:オフセットさせる)
void	GUIObject::SetIsOffSetFlag(bool isOffSet)
{
	isPosOffSet = isOffSet;
}