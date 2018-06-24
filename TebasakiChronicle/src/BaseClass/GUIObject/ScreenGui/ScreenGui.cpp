#include "ScreenGui.h"
#include "../src/Helper.h"

//!@brief	コンストラクタ
ScreenGui::ScreenGui()
{
	
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

	GearData	gearData[] =
	{
		//画面左下の歯車データ(BossのLifeゲージが出るところ)
		{ 3,K_Math::Vector3(100,620,0) },
		{ 2,K_Math::Vector3(100,710,0) },
		{ 1,K_Math::Vector3(75, 550, 0) },
		{ 2,K_Math::Vector3(18,520,0) },
		{ 4,K_Math::Vector3(1, 640, 0) },

		//画面右下の歯車データ(スキルが格納されるところ)
		{ 1,K_Math::Vector3(1100, 690, 0 ) },
		{ 3,K_Math::Vector3(1070, 620, 0) },
		{ 2,K_Math::Vector3(1150, 700, 0) },
		{ 2,K_Math::Vector3(1190,690,0) },
		{ 2,K_Math::Vector3(1240, 680, 0) },
		{ 4,K_Math::Vector3(1279, 570, 0) },

		//画面左上の歯車データ(プレイヤーのLifeゲージが出るところ)
		{3,K_Math::Vector3(80, 100, 0) },
		{3,K_Math::Vector3(10, 240, 0) },
		{2,K_Math::Vector3(110, 50, 0) },
		{4,K_Math::Vector3(1, 20, 0) },
	};
	//歯車の番号に応じた、画像のソースボックス
	K_Math::Box2D	srcBox[4] =
	{
		K_Math::Box2D(0,0,80,80),
		K_Math::Box2D(0,0,93,93),
		K_Math::Box2D(0,0,121,121),
		K_Math::Box2D(0,0,202,202)
	};

	/*for (int i = 0; i < 15; ++i)
	{
		gears.emplace_back(new GUIObject("ScreenUI/歯車" + std::to_string(gearData[i].no),gearData[i].pos, srcBox[gearData[i].no + 1]));
	}

	for (auto& gear : gears)
	{
		gear->SetRotateSpeed(2.0f);
	}*/

	//回転スピード、回転向きを設定
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

	//スキル基盤
	skillArea = new GUIObject("ScreenUI/skill", K_Math::Vector3(1170, 610, 0), K_Math::Box2D(0, 0, 256, 256));
	//Lifeの基盤
	lifeBaseArea = new GUIObject("ScreenUI/life", K_Math::Vector3(25, 160, 0), K_Math::Box2D(0, 0, 256, 256));
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
	Memory::SafeDelete(lifeBaseArea);
	Memory::SafeDelete(skillArea);

	/*for (auto gear : gears)
	{
		Memory::SafeDelete(gear);
	}
	gears.clear();*/
}


//!@brief	更新
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
	skillArea->Render();
	
}


//!@brief	早めに描画する
void	ScreenGui::EarlyRender()
{
	for (int i = 0; i < 4; ++i)
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

	/*int i = 0;
	int leftGearNum = 3;
	int rightGearNum = 6;
	int	lifeGearNum = 4;
	for (; i < leftGearNum; ++i)
	{
		gears[i]->Render();
	}
	rightGearNum += leftGearNum;
	for (int j = i; j < rightGearNum; ++j)
	{
		gears[i]->Render();
	}
	lifeGearNum += rightGearNum;
	for (int k = i; k < leftGearNum; ++k)
	{
		gears[i]->Render();
	}*/
}

//!@brief	遅めに描画する
void	ScreenGui::LateRender()
{
	gearLeft[4]->Render();
	lifeBaseArea->Render();
	skillArea->Render();
}



