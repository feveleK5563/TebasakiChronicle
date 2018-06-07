#include "GageGui.h"
#include "CameraList.h"

//!@brief	コンストラクタ
GageGui::GageGui()
	: guiObject("target",K_Math::Vector3(0,0,0),K_Math::Box2D(0,0,64,64))
	, backGround("target",K_Math::Vector3(0,0,0),K_Math::Box2D(0,0,64,64))
	, fillAreaBox("target",K_Math::Vector3(0,0,0),K_Math::Box2D(0,0,64,64))
{
	result = 0.0f;
	baseAngle = -60.0f;
}
//!@brief	デストラクタ
GageGui::~GageGui()
{

}

//!@brief	割合を算出する
void		GageGui::Raito(float maxValue,float nowValue,float raito)
{
	result = nowValue / maxValue * raito;
}


//!@brief	位置に割合を適用する
void		GageGui::ProcessPos()
{
	guiObject.GetGameObject().SetPos(K_Math::Vector3(
		guiObject.GetGameObject().GetPos().x + result,
		guiObject.GetGameObject().GetPos().y + result,
		guiObject.GetGameObject().GetPos().z + result)
	);
}

//!@brief	角度に割合を適用する
void		GageGui::ProcessRotation()
{
	baseAngle++;
	guiObject.GetGameObject().SetAngle(K_Math::Vector3(
		0, 0, baseAngle
	));
}

//!@brief	大きさ割合を適用する
void		GageGui::ProcessScale()
{
	guiObject.GetGameObject().SetScale(
		K_Math::Vector3(baseAngle, baseAngle, 1)
	);
}

//!@brief	描画
void		GageGui::Render()
{
	guiObject.Render();
}