#include "CSTList.h"
#include "BaseClass/Collision/CollisionCreator.h"
#include "MeshModel.h"
#include "SystemClass.h"

#include "Effect/Effect.h"
#include "Loader/EnemyLoader.h"
#include "BaseClass/ImageManager/ImageManager.h"
#include "Object/Enemy/EnemyType/EnemyTypeManager.h"
#include "Object/Enemy/EnemyManager.h"

#include "Object/Player/Player.h"
#include "MapPolygon.h"

#include "../src/Object/Object3D/Object3D.h"
#include "../src/BaseClass/GUIObject/GUIObject.h"
#include "../src/BaseClass/GUIObject/GageGui/GageGui.h"
#include "../src/BaseClass/GUIObject/ScreenGui/ScreenGui.h"
#include "../src/BaseClass//GUIObject/DataGui/DataGui.h"


#include "Object/CameraMan/CameraMan.h"

#include <memory>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#include "BaseClass/Sound/Sound.h"
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
	CST::CreateShader("data/shader/VertexShader.vs", "data/shader/TextureSampler.ps");

	//�G�t�F�N�g
	Effect::CreateEffectData(	Effect1,
								CST::LoadAndGetTexture("testEffect", "data/image/testEffect.png"),
								new AnimationCharaChip(K_Math::Box2D(0, 0, 32, 32), 8, 5, false));

	EnemyLoader eLoader;
	//�G�̎�ނ��쐬
	EnemyTypeManager* etm = new EnemyTypeManager();
	etm->CreateEnemyData(eLoader.LoadEnemyData("data/EnemyData/EnemyDataA1.txt"));
	//��L�ō쐬������ނ���ɓG�𐶐�����
	EnemyManager* emanager = new EnemyManager();
	emanager->CreateEnemy(etm->GetEnemyTypeData(0), K_Math::Vector3(-10, 20, 0), Status::Direction::Left);
	
	//�v���C���[
	Player* player = new Player();
	player->Initliaze();

	K_Math::Vector3 scale = { 10,40,40 };
	K_Math::Vector3 rotation = { K_Math::DegToRad(0),K_Math::DegToRad(90),K_Math::DegToRad(0) };
	K_Math::Vector3 pos = { -120.0f,-50.0f,0.f };
	//�n�`����t���I�u�W�F�N�g
	//�I�u�W�F�N�g
	Object3D*	mapObj = new Object3D("./data/model/testMap2d.fbx", "./data/image/player.tga",
										pos,rotation,scale);

	//�w�i�摜
	GUIObject*	back = new GUIObject("back", K_Math::Vector3(0, 50, 10), K_Math::Box2D(0, 0, 1920, 720));
	back->SetScale(K_Math::Vector3(2, 2, 1));

	//�J�����}��
	CameraMan* cameraMan = new CameraMan(ScreenWidth, ScreenHeight, 330, player->object.GetPos());

	//��ʂ�UI
	GUIObject*	screenGui = new GUIObject(
		"ui", 
		K_Math::Vector3(ScreenWidth/2, ScreenHeight/2, 0), 
		K_Math::Box2D(0, 0, ScreenWidth, ScreenHeight)
	);

	//�Q�[�W�̕`��
	GageGui		gage;
		
	//�X�N���[��
	ScreenGui*	gui = new ScreenGui();

	DataGui		datagui(player->object);
	//******************************************************************
	
	//�T�E���h�G���W���̏�����
	SoundEngine soundEngine;
	//�|�C���^�Ŏg���ꍇ
	SoundEngine* pEngine = &soundEngine;
	//�����̃��[�h
	Sound source;
	source.LoadSound("bgm", "�V�Y_drone.ogg");
	//Engine�ɃT�E���h��o�^(�ǉ����Ȃ��ƃA�N�Z�X�ᔽ)
	pEngine->AddSource(source);
	source.Play();

	while (sc->IsSystemEnd() == false)
	{
		if (INPUT::IsPressButton(VpadIndex::Pad0, K_Input::VpadButton::R1))
		{
				soundEngine.DeleteSound("bgm");
		}
		sc->ProcessSystem();
		CC::Run();

		emanager->UpdateAllEnemy();

		player->UpDate();

		Effect::Run();

		//�J�����ǔ�
		cameraMan->Run(player->object.GetPos());

		CST::FrameBufferBeginDraw(ScreenWidth, ScreenHeight, 0.f, 0.f, 1.f);
		CST::GetPerspectiveCamera()->Draw();
		CST::GetOrthoCamera()->Draw();

		mapObj->SetDecisionParam(pos, rotation, scale);
		
		
		//�w�i�̍X�V
		back->UpDate();
		//���UI�̍X�V
		screenGui->UpDate();

		emanager->RenderAllEnemy();

		Effect::Render();

		//*****************************
		//FBX���f���̕`��
		CST::GetShaderClass(2)->UseShader();
		//----------------------------
		//�n�`����t���I�u�W�F�N�g
		mapObj->Render();

		CST::GetShaderClass(1)->UseShader();


		//�w�i�̕`��
		back->Render3D();
		
		//���UI�̕`��
		//screenGui->Render();

		//�v���C��[
		player->Render();

		gui->UpDate();
		gui->Render();

		datagui.RaitoRaito();
		datagui.UpDate();
		datagui.Render();

		//CC::DebugDraw(CST::GetShaderClass(1), CST::GetPerspectiveCamera());
	
		sc->SwapBuffer();
	}


	delete sc;
	delete etm;
	delete emanager;
	delete player;
	delete mapObj;
	delete back;
	delete cameraMan;
	delete screenGui;
	delete gui;

	CC::Delete();
}