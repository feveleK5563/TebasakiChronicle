#include "ScreenGui.h"
#include "../src/Helper.h"

//!@brief	RXgN^
ScreenGui::ScreenGui()
{
	
	//ΆΊΜΤ
	gearLeft[0] = new GUIObject("ScreenUI/Τ3", K_Math::Vector3(100, 620, 0), K_Math::Box2D(0, 0, 121, 121));
	gearLeft[1] = new GUIObject("ScreenUI/Τ2", K_Math::Vector3(100, 710, 0), K_Math::Box2D(0, 0, 93, 93));
	gearLeft[2] = new GUIObject("ScreenUI/Τ1", K_Math::Vector3(75, 550, 0), K_Math::Box2D(0, 0, 80, 80));
	gearLeft[3] = new GUIObject("ScreenUI/Τ2", K_Math::Vector3(18, 520, 0), K_Math::Box2D(0, 0, 93, 93));
	gearLeft[4] = new GUIObject("ScreenUI/Τ4", K_Math::Vector3(1, 640, 0), K_Math::Box2D(0, 0, 202, 202));

	//EΊ(XLΜΖ±λ)ΜΤ
	gearRight[0] = new GUIObject("ScreenUI/Τ1", K_Math::Vector3(1100, 690, 0), K_Math::Box2D(0, 0, 80, 80));
	gearRight[1] = new GUIObject("ScreenUI/Τ3", K_Math::Vector3(1070, 620, 0), K_Math::Box2D(0, 0, 121, 121));
	gearRight[2] = new GUIObject("ScreenUI/Τ2", K_Math::Vector3(1150, 700, 0), K_Math::Box2D(0, 0, 93, 93));
	gearRight[3] = new GUIObject("ScreenUI/Τ2", K_Math::Vector3(1190, 690, 0), K_Math::Box2D(0, 0, 93, 93));
	gearRight[4] = new GUIObject("ScreenUI/Τ2", K_Math::Vector3(1240, 680, 0), K_Math::Box2D(0, 0, 93, 93));
	gearRight[5] = new GUIObject("ScreenUI/Τ4", K_Math::Vector3(1279, 570, 0), K_Math::Box2D(0, 0, 202, 202));

	//LifeΜΤ
	gearLife[0] = new GUIObject("ScreenUI/Τ3", K_Math::Vector3(80, 100, 0), K_Math::Box2D(0, 0, 121, 121));
	gearLife[1] = new GUIObject("ScreenUI/Τ3", K_Math::Vector3(10, 240, 0), K_Math::Box2D(0, 0, 121, 121));
	gearLife[2] = new GUIObject("ScreenUI/Τ2", K_Math::Vector3(110, 50, 0), K_Math::Box2D(0, 0, 93, 93));
	gearLife[3] = new GUIObject("ScreenUI/Τ4", K_Math::Vector3(1, 20, 0), K_Math::Box2D(0, 0, 202, 202));

	//ρ]Xs[hAρ]ό«πέθ
	for (int i = 0; i < 5; ++i)
	{
		gearLeft[i]->SetRotateSpeed(1.0f);
	}
	for (int i = 0; i < 6; ++i)
	{
		gearLeft[i]->SetRotateSpeed(-2.0f);
	}
	for (int i = 0; i < 4; ++i)
	{
		gearLife[i]->SetRotateSpeed(3.0f);
	}

	//XLξΥ
	skillArea = new GUIObject("UI/ScreenUI", K_Math::Vector3(1150, 600, 0), K_Math::Box2D(367, 0, 256, 256));
	//LifeΜξΥ
	lifeBaseArea = new GUIObject("UI/ScreenUI", K_Math::Vector3(0, 140, 0), K_Math::Box2D(96, 0, 256, 256));

	//GΜCtQ[W
	enemyLife = new GUIObject("ScreenUI/lifeBar", K_Math::Vector3(0, 720, 0), K_Math::Box2D(0, 0, 1095, 270));
	enemyLife->SetRotateAngle(90.0f);
}

//!@brief	fXgN^
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
	Memory::SafeDelete(lifeBaseArea);
	Memory::SafeDelete(skillArea);
	Memory::SafeDelete(enemyLife);
}


//!@brief	XV
void	ScreenGui::UpDate()
{
	for (int i = 0; i < 5; ++i)
	{
		gearLeft[i]->UpDate();
		gearLeft[i]->Rotation();
	}
	for (int i = 0; i < 6; ++i)
	{
		gearRight[i]->UpDate();
		gearRight[i]->Rotation();
	}
	for (int i = 0; i < 4; ++i)
	{
		gearLife[i]->UpDate();
		gearLife[i]->Rotation();
	}
	enemyLife->UpDate();
	enemyLife->Rotation();
}
//!@brief	`ζ
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
	skillArea->Render();
	
}




