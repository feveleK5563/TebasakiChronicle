#include "GUIObject.h"


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
	object.SetImage(imageName, CST::LoadAndGetTexture(imageName,"./data/image/" + imageName + ".png"), true);
	object.GetImage().CreateCharaChip(srcBox, 1, 1, false);
}


//更新処理
void	GUIObject::UpDate()
{
	object.GetImage().Animation();
}

//描画処理
void	GUIObject::Render()
{
	object.GetImage().ImageDraw3D(object.GetPos(), object.GetAngle(), object.GetScale(), 0);
}