#include "GageGui.h"
#include "CameraList.h"

//!@brief	�R���X�g���N�^
GageGui::GageGui()
	: frame("ScreenUI/lifeBar", K_Math::Vector3(0, 720, 0), K_Math::Box2D(0, 0, 1095, 270))
	, backGround("target", K_Math::Vector3(0, 0, 0), K_Math::Box2D(0, 0, 64, 64))
	, fillAreaBox("target", K_Math::Vector3(0, 0, 0), K_Math::Box2D(0, 0, 64, 64))
{
	moveMotion = 0;
}
//!@brief	�f�X�g���N�^
GageGui::~GageGui()
{

}

//!@brief	�������Z�o����
void		GageGui::Raito(float maxValue, float nowValue, float raito)
{
	nowGagePos = nowValue / maxValue * raito;
}


//!@brief	�ʒu�Ɋ�����K�p����
void		GageGui::ProcessPos()
{
	frame.GetGameObject().SetPos(K_Math::Vector3(
		frame.GetGameObject().GetPos().x + nowGagePos,
		frame.GetGameObject().GetPos().y + nowGagePos,
		frame.GetGameObject().GetPos().z + nowGagePos)
	);
}

//!@brief	�p�x�Ɋ�����K�p����
void		GageGui::ProcessRotation()
{
	frame.GetGameObject().SetAngle(K_Math::Vector3(0, 0, 0));
}

//!@brief	�傫��������K�p����
void		GageGui::ProcessScale()
{
	frame.GetGameObject().SetScale(
		K_Math::Vector3(1, 1, 1)
	);
}

//!@brief	�X�V
void		GageGui::UpDate()
{
	frame.UpDate();
}

//!@brief	�`��
void		GageGui::Render()
{
	frame.Render();
}


//!@brief	�ʒu���w�肵����������
void	GageGui::AddMove(float moveAmount)
{
	fillAreaBox.SetMoveAmount(moveAmount);
}
//!@brief	��]������
void	GageGui::AddRotation(float angleAmount)
{
	frame.SetRotateAngle(angleAmount);
	fillAreaBox.SetRotateAngle(angleAmount);
	backGround.SetRotateAngle(angleAmount);
}

//!@brief	�o��
void	GageGui::Appear()
{
	switch (moveMotion) {
	case 0:
		if (!fillAreaBox.FinishRotation())
		{
			moveMotion++;
		}
		break;
	case 1:
		if (!fillAreaBox.FinishMove())
		{
			moveMotion++;
		}
		break;
	case 2:
		moveMotion = 2;
		break;
	}
}

//!@brief	�ʒu�̈ړ�
void	GageGui::Move()
{
	fillAreaBox.AddVec();
	backGround.AddVec();
}

//!@brief	��]
void	GageGui::Rotate()
{
	frame.Rotation();
	fillAreaBox.Rotation();
	backGround.Rotation();
}
