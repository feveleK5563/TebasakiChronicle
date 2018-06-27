#include "ScreenGui.h"
#include "../../../CSTList.h"
#include "../src/Helper.h"

//!@brief	�R���X�g���N�^
ScreenGui::ScreenGui()
{
	CST::LoadAndGetTexture("����1", "data/image/ScreenUI/����1.png");
	CST::LoadAndGetTexture("����2", "data/image/ScreenUI/����2.png");
	CST::LoadAndGetTexture("����3", "data/image/ScreenUI/����3.png");
	CST::LoadAndGetTexture("����4", "data/image/ScreenUI/����4.png");

	//�����̎���
	gearLeft[0] = new GUIObject("����3", K_Math::Vector3(100, 620, 0), K_Math::Box2D(0, 0, 121, 121));
	gearLeft[1] = new GUIObject("����2", K_Math::Vector3(100, 710, 0), K_Math::Box2D(0, 0, 93, 93));
	gearLeft[2] = new GUIObject("����1", K_Math::Vector3(75, 550, 0), K_Math::Box2D(0, 0, 80, 80));
	gearLeft[3] = new GUIObject("����2", K_Math::Vector3(18, 520, 0), K_Math::Box2D(0, 0, 93, 93));
	gearLeft[4] = new GUIObject("����4", K_Math::Vector3(1, 640, 0), K_Math::Box2D(0, 0, 202, 202));

	//�E��(�X�L���̂Ƃ���)�̎���
	gearRight[0] = new GUIObject("����1", K_Math::Vector3(1100, 690, 0), K_Math::Box2D(0, 0, 80, 80));
	gearRight[1] = new GUIObject("����3", K_Math::Vector3(1070, 620, 0), K_Math::Box2D(0, 0, 121, 121));
	gearRight[2] = new GUIObject("����2", K_Math::Vector3(1150, 700, 0), K_Math::Box2D(0, 0, 93, 93));
	gearRight[3] = new GUIObject("����2", K_Math::Vector3(1190, 690, 0), K_Math::Box2D(0, 0, 93, 93));
	gearRight[4] = new GUIObject("����2", K_Math::Vector3(1240, 680, 0), K_Math::Box2D(0, 0, 93, 93));
	gearRight[5] = new GUIObject("����4", K_Math::Vector3(1279, 570, 0), K_Math::Box2D(0, 0, 202, 202));

	//Life�̎���
	gearLife[0] = new GUIObject("����3", K_Math::Vector3(80, 100, 0), K_Math::Box2D(0, 0, 121, 121));
	gearLife[1] = new GUIObject("����3", K_Math::Vector3(10, 240, 0), K_Math::Box2D(0, 0, 121, 121));
	gearLife[2] = new GUIObject("����2", K_Math::Vector3(110, 50, 0), K_Math::Box2D(0, 0, 93, 93));
	gearLife[3] = new GUIObject("����4", K_Math::Vector3(1, 20, 0), K_Math::Box2D(0, 0, 202, 202));

	//��]�X�s�[�h�A��]������ݒ�
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

	//�X�L�����
	CST::LoadAndGetTexture("skill", "data/image/ScreenUI/skill.png");
	skillArea = new GUIObject("skill", K_Math::Vector3(1170, 610, 0), K_Math::Box2D(0, 0, 256, 256));
	//Life�̊��
	CST::LoadAndGetTexture("life", "data/image/ScreenUI/life.png");
	lifeBaseArea = new GUIObject("life", K_Math::Vector3(25, 160, 0), K_Math::Box2D(0, 0, 256, 256));
}

//!@brief	�f�X�g���N�^
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

	CST::DeleteTexture("����1");
	CST::DeleteTexture("����2");
	CST::DeleteTexture("����3");
	CST::DeleteTexture("����4");
	CST::DeleteTexture("skill");
	CST::DeleteTexture("life");
}


//!@brief	�X�V
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

//!@brief	�`��
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


//!@brief	���߂ɕ`�悷��
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
}

//!@brief	�x�߂ɕ`�悷��
void	ScreenGui::LateRender()
{
	gearLeft[4]->Render();
	lifeBaseArea->Render();
	skillArea->Render();
}



