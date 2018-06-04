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

int main()
{
	//スクリーン
	const int ScreenWidth = 1280;
	const int ScreenHeight = 720;
	//メモリリーク検知くん
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//ウィンドウ
	K_System::SystemClass* sc = new K_System::SystemClass("TebasakiChronicle", ScreenWidth, ScreenHeight, false);

	//CollisionManagerを初期化
	CC::Initialize();

	//カメラリスト
	K_Math::Vector3 position = K_Math::Vector3(0, 0, -330);
	K_Math::Vector3 target = K_Math::Vector3(0, 0, 0);

	float clipNear = 0.1f;
	float clipFar = 1500.f;
	float fieldOfView = 45.f;
	CST::CreatePerspectiveCamera(position, target, ScreenWidth, ScreenHeight, clipNear, clipFar, fieldOfView);
	CST::CreateOrthoCamera(position, target, ScreenWidth, ScreenHeight, clipNear, clipFar);
	
	INPUT::SetInputClass(sc->GetInput());
	INPUT::Create(K_Input::VpadIndex::Pad0);

	//シェーダーリスト
	CST::CreateShader("data/shader/SpriteShader.vs", "data/shader/SpriteShader.ps");
	CST::CreateShader("data/shader/SimpleShader.vs", "data/shader/SimpleShader.ps");
	CST::CreateShader("data/shader/VertexShader.vs", "data/shader/TextureSampler.ps"); //追加

	//エフェクト
	Effect::CreateEffectData(	Effect1,
								CST::LoadAndGetTexture("testEffect", "data/image/testEffect.png"),
								new AnimationCharaChip(K_Math::Box2D(0, 0, 32, 32), 8, 3, false));

	EnemyLoader eLoader;
	//敵の種類を作成
	EnemyTypeManager* etm = new EnemyTypeManager();
	etm->CreateEnemyData(eLoader.LoadEnemyData("data/EnemyData/EnemyDataA1.txt"));
	//上記で作成した種類を基に敵を生成する
	EnemyManager* emanager = new EnemyManager();
	emanager->CreateEnemy(etm->GetEnemyTypeData(0), K_Math::Vector3(-10, 20, 0), Status::Direction::Left);
	
	//プレイヤー
	Player* player = new Player();
	player->Initliaze();

	K_Math::Vector3 scale = { 10,40,40 };
	K_Math::Vector3 rotation = { K_Math::DegToRad(0),K_Math::DegToRad(90),K_Math::DegToRad(0) };
	K_Math::Vector3 pos = { -120.0f,-50.0f,0.f };
	//地形判定付きオブジェクト
	//オブジェクト
	Object3D*	mapObj = new Object3D("./data/model/testMap2d.fbx", "./data/image/player.tga",
										pos,rotation,scale);

	//******************************************************************
	
	while (sc->IsSystemEnd() == false)
	{
		sc->ProcessSystem();
		CC::Run();

		emanager->UpdateAllEnemy();

		player->UpDate();

		Effect::Run();

		//カメラ追尾
		CST::GetPerspectiveCamera()->SetTarget(player->object.GetPos().x, player->object.GetPos().y, player->object.GetPos().z);
		CST::GetPerspectiveCamera()->SetPosition(330, K_Math::Vector3(0, 0, -1));	//330

		CST::FrameBufferBeginDraw(ScreenWidth, ScreenHeight, 0.f, 0.f, 1.f);
		CST::GetPerspectiveCamera()->Draw();
		CST::GetOrthoCamera()->Draw();

		mapObj->SetDecisionParam(pos, rotation, scale);

		emanager->RenderAllEnemy();
		player->Render();

		Effect::Render();

		//*****************************
		//FBXモデルの描画
		CST::GetShaderClass(2)->UseShader();
		//----------------------------
		//地形判定付きオブジェクト
		mapObj->Render();

		CST::GetShaderClass(1)->UseShader();

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