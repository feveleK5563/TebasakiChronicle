#include "CSTList.h"
#include "BaseClass/Collision/CollisionCreator.h"
#include "MeshModel.h"
#include "SystemClass.h"

#include "Loader/EnemyLoader.h"
#include "BaseClass/ImageManager/ImageManager.h"
#include "Object/Enemy/EnemyType/EnemyTypeManager.h"
#include "Object/Enemy/EnemyManager.h"

#include "Object/Player/Player.h"
#include "MapPolygon.h"

#include "../src/Object/Object3D/Object3D.h"

int main()
{
	//�X�N���[��
	const int ScreenWidth = 1280;
	const int ScreenHeight = 720;
	//���������[�N���m����
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//�E�B���h�E
	K_System::SystemClass* sc = new K_System::SystemClass("TebasakiChronicle", ScreenWidth, ScreenHeight, false);

	//CollisionManager��������
	CC::Initialize();

	//�J�������X�g
	K_Math::Vector3 position = K_Math::Vector3(0, 0, -330);
	K_Math::Vector3 target = K_Math::Vector3(0, 0, 0);

	float clipNear = 0.1f;
	float clipFar = 1500.f;
	float fieldOfView = 45.f;
	CST::CreatePerspectiveCamera(position, target, ScreenWidth, ScreenHeight, clipNear, clipFar, fieldOfView);
	CST::CreateOrthoCamera(position, target, ScreenWidth, ScreenHeight, clipNear, clipFar);
	
	INPUT::SetInputClass(sc->GetInput());
	INPUT::Create(K_Input::VpadIndex::Pad0);

	//�V�F�[�_�[���X�g
	CST::CreateShader("data/shader/SpriteShader.vs", "data/shader/SpriteShader.ps");
	CST::CreateShader("data/shader/SimpleShader.vs", "data/shader/SimpleShader.ps");
	CST::CreateShader("data/shader/VertexShader.vs", "data/shader/TextureSampler.ps"); //�ǉ�

	//�n�`(��)
	//CC::CreateCollisionObject(CC::CreateBoxShape(1000.f, 50.f, 10.f), false, CollisionMask::Non, CollisionMask::Ground, K_Math::Vector3(0, -80, 0));

	EnemyLoader eLoader;

	//�G�̎�ނ��쐬
	EnemyTypeManager* etm = new EnemyTypeManager();
	etm->CreateEnemyData(eLoader.LoadEnemyData("data/EnemyData/TestData2.txt"));
	//��L�ō쐬������ނ���ɓG�𐶐�����
	EnemyManager* emanager = new EnemyManager();
	emanager->CreateEnemy(etm->GetEnemyTypeData(0), K_Math::Vector3(-10, 0, 0), Status::Direction::Left);

	//�v���C���[
	Player* player = new Player();
	player->Initliaze();
	
	//�n�`����t���I�u�W�F�N�g
	//�I�u�W�F�N�g
	Object3D*	mapObj = new Object3D("./data/model/testMap2d.fbx", "./data/image/player.tga");

	
	K_Math::Vector3 scale = { 10,50,40 };
	K_Math::Vector3 rotation = { K_Math::DegToRad(-90),0,K_Math::DegToRad(-90) };
	K_Math::Vector3 pos = { -120.0f,-50.0f,0.f };
	//******************************************************************
	
	while (sc->IsSystemEnd() == false)
	{
		sc->ProcessSystem();
		CC::Run();

		emanager->UpdateAllEnemy();

		player->UpDate();
		//�J�����ǔ�
		CST::GetPerspectiveCamera()->SetTarget(player->object.GetPos().x(), player->object.GetPos().y(), player->object.GetPos().z());
		CST::GetPerspectiveCamera()->SetPosition(330, K_Math::Vector3(0, 0, -1));

		CST::FrameBufferBeginDraw(ScreenWidth, ScreenHeight, 0.f, 0.f, 1.f);
		CST::GetPerspectiveCamera()->Draw();
		CST::GetOrthoCamera()->Draw();

		emanager->RenderAllEnemy();
		player->Render();


		//*****************************
		//FBX���f���̕`��
		CST::GetShaderClass(2)->UseShader();
		//----------------------------
		//�n�`����t���I�u�W�F�N�g
		mapObj->SetDecisionParam(pos, rotation, scale);
		mapObj->Render();

		//CC::DebugDraw(CST::GetShaderClass(1), CST::GetPerspectiveCamera());
		sc->SwapBuffer();
	}

	delete sc;
	delete etm;
	delete emanager;
	delete player;
	
	delete mapObj;

	CC::Delete();
}