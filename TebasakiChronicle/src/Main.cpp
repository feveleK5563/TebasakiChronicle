#include "CSTList.h"
#include "BaseClass/Collision/CollisionCreator.h"
#include "MeshModel.h"
#include "SystemClass.h"

#include "Loader/EnemyLoader.h"
#include "BaseClass/ImageManager/ImageManager.h"
#include "Object/Enemy/EnemyType/EnemyTypeManager.h"
#include "Object/Enemy/EnemyManager.h"

#include "Object/Player/Player.h"

int main()
{
	//���������[�N���m����
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//�E�B���h�E
	K_System::SystemClass* sc = new K_System::SystemClass("TebasakiChronicle", 720, 540, false);

	//CollisionManager��������
	CC::Initialize();

	//�J�������X�g
	K_Math::Vector3 position = K_Math::Vector3(0, 0, -150);
	K_Math::Vector3 target = K_Math::Vector3(0, 0, 0);
	int screenWidth = 720;
	int screenHeight = 540;
	float clipNear = 0.1f;
	float clipFar = 1500.f;
	float fieldOfView = 45.f;
	CST::CreatePerspectiveCamera(position, target, screenWidth, screenHeight, clipNear, clipFar, fieldOfView);
	CST::CreateOrthoCamera(position, target, screenWidth, screenHeight, clipNear, clipFar);

	INPUT::SetInputClass(sc->GetInput());
	INPUT::Create(K_Input::VpadIndex::Pad0);

	//�V�F�[�_�[���X�g
	CST::CreateShader("data/shader/SpriteShader.vs", "data/shader/SpriteShader.ps");
	CST::CreateShader("data/shader/SimpleShader.vs", "data/shader/SimpleShader.ps");
	//���\�[�X���[�_�[

	//�n�`(��)
	CC::CreateCollisionObject(CC::CreateBoxShape(1000.f, 50.f, 10.f), false, CollisionMask::Non, CollisionMask::Ground, K_Math::Vector3(0, -80, 0));

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

	while (sc->IsSystemEnd() == false)
	{
		sc->ProcessSystem();
		CC::Run();

		emanager->UpdateAllEnemy();

		player->UpDate();


		CST::FrameBufferBeginDraw(720, 540, 0.f, 0.f, 1.f);
		CST::GetPerspectiveCamera()->Draw();
		CST::GetOrthoCamera()->Draw();

		emanager->RenderAllEnemy();
		player->Render();

		//CC::DebugDraw(CST::GetShaderClass(1), CST::GetPerspectiveCamera());
		sc->SwapBuffer();
	}

	delete sc;
	delete etm;
	delete emanager;
	delete player;

	CC::Delete();
}