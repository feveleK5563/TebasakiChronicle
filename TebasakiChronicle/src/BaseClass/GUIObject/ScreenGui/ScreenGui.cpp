#include "ScreenGui.h"
#include "../src/Helper.h"

//!@brief	コンストラクタ
ScreenGui::ScreenGui()
{
	//歯車左側
	//gearLeft[0] = new GUIObject("ScreenUI/歯車1", K_Math::Vector3(145, 630, 0), K_Math::Box2D(0, 0, 80, 80));
	//gearLeft[1] = new GUIObject("ScreenUI/歯車2", K_Math::Vector3(160, 650, 0), K_Math::Box2D(0, 0, 93, 93));
	//gearLeft[2] = new GUIObject("ScreenUI/歯車3", K_Math::Vector3(180, 680, 0), K_Math::Box2D(0, 0, 121, 121));
	//gearLeft[3] = new GUIObject("ScreenUI/歯車4", K_Math::Vector3(210, 640, 0), K_Math::Box2D(0, 0, 202, 202));
	//gearLeft[4] = new GUIObject("ScreenUI", K_Math::Vector3(0, 700, 0), K_Math::Box2D(160 * 5, 0, 64, 64));
	angle = 0;

	//左下の歯車
	gearLeft[0] = new GUIObject("ScreenUI/歯車3", K_Math::Vector3(100, 620, 0), K_Math::Box2D(0, 0, 121, 121));
	gearLeft[1] = new GUIObject("ScreenUI/歯車2", K_Math::Vector3(100, 710, 0), K_Math::Box2D(0, 0, 93, 93));
	gearLeft[2] = new GUIObject("ScreenUI/歯車1", K_Math::Vector3(75, 550, 0), K_Math::Box2D(0, 0, 80, 80));
	gearLeft[3] = new GUIObject("ScreenUI/歯車2", K_Math::Vector3(18, 520, 0), K_Math::Box2D(0, 0, 93, 93));
	gearLeft[4] = new GUIObject("ScreenUI/歯車4", K_Math::Vector3(1, 640, 0), K_Math::Box2D(0, 0, 202, 202));

	//右下(スキルのところ)の歯車
	gearRight[0] = new GUIObject("ScreenUI/歯車1", K_Math::Vector3(1100, 690, 0), K_Math::Box2D(0, 0, 80, 80));
	gearRight[1] = new GUIObject("ScreenUI/歯車3", K_Math::Vector3(1070, 620, 0), K_Math::Box2D(0, 0, 121, 121));
	gearRight[2] = new GUIObject("ScreenUI/歯車2", K_Math::Vector3(1150, 700, 0), K_Math::Box2D(0, 0, 93, 93));
	gearRight[3] = new GUIObject("ScreenUI/歯車2", K_Math::Vector3(1190, 690, 0), K_Math::Box2D(0, 0, 93, 93));
	gearRight[4] = new GUIObject("ScreenUI/歯車2", K_Math::Vector3(1240, 680, 0), K_Math::Box2D(0, 0, 93, 93));
	gearRight[5] = new GUIObject("ScreenUI/歯車4", K_Math::Vector3(1279, 570, 0), K_Math::Box2D(0, 0, 202, 202));

	//Lifeの歯車
	gearLife[0] = new GUIObject("ScreenUI/歯車3", K_Math::Vector3(80, 100, 0), K_Math::Box2D(0, 0, 121, 121));
	gearLife[1] = new GUIObject("ScreenUI/歯車3", K_Math::Vector3(10, 240, 0), K_Math::Box2D(0, 0, 121, 121));
	gearLife[2] = new GUIObject("ScreenUI/歯車2", K_Math::Vector3(110, 50, 0), K_Math::Box2D(0, 0, 93, 93));
	gearLife[3] = new GUIObject("ScreenUI/歯車4", K_Math::Vector3(1, 20, 0), K_Math::Box2D(0, 0, 202, 202));

	//スキル基盤
	skillArea = new GUIObject("UI/ScreenUI", K_Math::Vector3(1150, 600, 0), K_Math::Box2D(367, 0, 256, 256));

	//Lifeの針
	lifeneedle = new GUIObject("ScreenUI/Life針", K_Math::Vector3(30, 145, 0), K_Math::Box2D(0, 0, 67, 120));
	//Lifeの基盤
	lifeBaseArea = new GUIObject("UI/ScreenUI", K_Math::Vector3(0, 140, 0), K_Math::Box2D(96, 0, 256, 256));
}

//!@brief	デストラクタ
ScreenGui::~ScreenGui()
{
	for (int i = 0; i < 5; ++i)
	{
		Memory::SafeDelete(gearLeft[i]);
	}
	for (int i = 0; i < 6; ++i)
	{
		Memory::SafeDelete(gearRight[i]);
	}
	for (int i = 0; i < 4; ++i)
	{
		Memory::SafeDelete(gearLife[i]);
	}
	Memory::SafeDelete(lifeneedle);
	Memory::SafeDelete(lifeBaseArea);
	Memory::SafeDelete(skillArea);
}


//!@brief	更新
void	ScreenGui::UpDate()
{
	for (int i = 0; i < 5; ++i)
	{
		gearLeft[i]->GetGameObject().SetAngle(K_Math::Vector3(0, 0, angle));
		gearLeft[i]->UpDate();
	}
	for (int i = 0; i < 6; ++i)
	{
		gearRight[i]->GetGameObject().SetAngle(K_Math::Vector3(0, 0, angle));
		gearRight[i]->UpDate();
	}
	for (int i = 0; i < 4; ++i)
	{
		gearLife[i]->GetGameObject().SetAngle(K_Math::Vector3(0, 0, angle));
		gearLife[i]->UpDate();
	}


	angle++;
	if (angle >= 360)
	{
		angle = 0;
	}
	float dataAngle = -180;
	lifeneedle->GetGameObject().SetAngle(K_Math::Vector3(0, 0, dataAngle));
	lifeneedle->UpDate();

}
//!@brief	描画
void	ScreenGui::Render()
{
	for (int i = 0; i < 5; ++i)
	{
		gearLeft[i]->Render();
	}
	for (int i = 0; i < 6; ++i)
	{
		gearRight[i]->Render();
	}
	for (int i = 0; i < 4; ++i)
	{
		gearLife[i]->Render();
	}

	lifeBaseArea->Render();
	//lifeneedle->Render();

	skillArea->Render();
}




