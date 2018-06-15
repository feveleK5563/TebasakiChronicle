#include "GageGui.h"
#include "CameraList.h"

//!@brief	コンストラクタ
GageGui::GageGui()
	: frame("ScreenUI/lifeBar", K_Math::Vector3(0, 720, 0), K_Math::Box2D(0, 0, 1095, 270))
	, backGround("target", K_Math::Vector3(0, 0, 0), K_Math::Box2D(0, 0, 64, 64))
	, fillAreaBox("target", K_Math::Vector3(0, 0, 0), K_Math::Box2D(0, 0, 64, 64))
{
	moveMotion = 0;
}
//!@brief	デストラクタ
GageGui::~GageGui()
{

}

//!@brief	割合を算出する
void		GageGui::Raito(float maxValue, float nowValue, float raito)
{
	nowGagePos = nowValue / maxValue * raito;
}


//!@brief	位置に割合を適用する
void		GageGui::ProcessPos()
{
	frame.GetGameObject().SetPos(K_Math::Vector3(
		frame.GetGameObject().GetPos().x + nowGagePos,
		frame.GetGameObject().GetPos().y + nowGagePos,
		frame.GetGameObject().GetPos().z + nowGagePos)
	);
}

//!@brief	角度に割合を適用する
void		GageGui::ProcessRotation()
{
	frame.GetGameObject().SetAngle(K_Math::Vector3(0, 0, 0));
}

//!@brief	大きさ割合を適用する
void		GageGui::ProcessScale()
{
	frame.GetGameObject().SetScale(
		K_Math::Vector3(1, 1, 1)
	);
}

//!@brief	更新
void		GageGui::UpDate()
{
	frame.UpDate();
}

//!@brief	描画
void		GageGui::Render()
{
	frame.Render();
}


//!@brief	位置を指定した数動かす
void	GageGui::AddMove(float moveAmount)
{
	fillAreaBox.SetMoveAmount(moveAmount);
}
//!@brief	回転させる
void	GageGui::AddRotation(float angleAmount)
{
	frame.SetRotateAngle(angleAmount);
	fillAreaBox.SetRotateAngle(angleAmount);
	backGround.SetRotateAngle(angleAmount);
}

//!@brief	出現
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

//!@brief	位置の移動
void	GageGui::Move()
{
	fillAreaBox.AddVec();
	backGround.AddVec();
}

//!@brief	回転
void	GageGui::Rotate()
{
	frame.Rotation();
	fillAreaBox.Rotation();
	backGround.Rotation();
}
