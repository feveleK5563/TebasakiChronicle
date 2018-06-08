#include "GageGui.h"
#include "CameraList.h"

//!@brief	�R���X�g���N�^
GageGui::GageGui()
	: guiObject("target",K_Math::Vector3(0,0,0),K_Math::Box2D(0,0,64,64))
	, backGround("target",K_Math::Vector3(0,0,0),K_Math::Box2D(0,0,64,64))
	, fillAreaBox("target",K_Math::Vector3(0,0,0),K_Math::Box2D(0,0,64,64))
{
	result = 0.0f;
	baseAngle = -60.0f;
}
//!@brief	�f�X�g���N�^
GageGui::~GageGui()
{

}

//!@brief	�������Z�o����
void		GageGui::Raito(float maxValue,float nowValue,float raito)
{
	result = nowValue / maxValue * raito;
}


//!@brief	�ʒu�Ɋ�����K�p����
void		GageGui::ProcessPos()
{
	guiObject.GetGameObject().SetPos(K_Math::Vector3(
		guiObject.GetGameObject().GetPos().x + result,
		guiObject.GetGameObject().GetPos().y + result,
		guiObject.GetGameObject().GetPos().z + result)
	);
}

//!@brief	�p�x�Ɋ�����K�p����
void		GageGui::ProcessRotation()
{
	baseAngle++;
	guiObject.GetGameObject().SetAngle(K_Math::Vector3(
		0, 0, baseAngle
	));
}

//!@brief	�傫��������K�p����
void		GageGui::ProcessScale()
{
	guiObject.GetGameObject().SetScale(
		K_Math::Vector3(baseAngle, baseAngle, 1)
	);
}

//!@brief	�`��
void		GageGui::Render()
{
	guiObject.Render();
}