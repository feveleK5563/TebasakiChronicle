#include "CSTList.h"
#include "BaseClass/Collision/CollisionCreator.h"
#include "MeshModel.h"
#include "SystemClass.h"

#include "BaseClass/ImageManager/ImageManager.h"
#include "Object/Enemy/EnemyType/EnemyTypeManager.h"
#include "Object/Enemy/EnemyManager.h"

#include "Object/Player/Player.h"
#include "MapPolygon.h"

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

	//地形(仮)
	//CC::CreateCollisionObject(CC::CreateBoxShape(1000.f, 50.f, 10.f), false, CollisionMask::Non, CollisionMask::Ground, K_Math::Vector3(0, -80, 0));

	//敵の種類を作成
	EnemyTypeManager* etm = new EnemyTypeManager();
	etm->LoadEnemyData("", 0);
	etm->LoadEnemyData("", 1);
	//敵1体に上記で作成した種類を割り当てる
	EnemyManager* emanager = new EnemyManager();
	emanager->CreateEnemy(etm->GetEnemyTypeData(0), K_Math::Vector3(-10, 0, 0), Status::Direction::Left);
	emanager->CreateEnemy(etm->GetEnemyTypeData(1), K_Math::Vector3(10, 0, 0), Status::Direction::Right);

	//プレイヤー
	Player* player = new Player();
	player->Initliaze();

	//モデルの使用例
	//***********************************************************************
	//テクスチャ
	K_Graphics::TextureList* textureList = new K_Graphics::TextureList();

	if (textureList->LoadTexture("fbxFile", "./data/image/player.tga"))
	{
		std::cout << "テクスチャGet" << std::endl;
	}

	//メッシュモデルクラス
	K_Graphics::ModelDatas*	modelData;
	//ファクトリを作成
	K_Graphics::ModelDataFactory factory;
	modelData = factory.LoadFBXModel("./data/model/testMap2d.fbx",textureList);

	//手順2、データを元にモデルクラスを初期化
	K_Graphics::MeshModel*	model = new K_Graphics::MeshModel(modelData);
	//手順3,MeshModelをより扱いやすくするMeshObjectクラスを初期化
	K_Graphics::MeshObject* object = new K_Graphics::MeshObject(model);

	//マップの処理
	K_Physics::MapPolygon* map = new K_Physics::MapPolygon("./data/model/testMap2d.fbx",CC::GetBulletPhysics(), CollisionMask::Non, CollisionMask::Ground);
	
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
		//カメラ追尾
		CST::GetPerspectiveCamera()->SetTarget(player->object.GetPos().x(), player->object.GetPos().y(), player->object.GetPos().z());
		CST::GetPerspectiveCamera()->SetPosition(330, K_Math::Vector3(0, 0, -1));

		CST::FrameBufferBeginDraw(ScreenWidth, ScreenHeight, 0.f, 0.f, 1.f);
		CST::GetPerspectiveCamera()->Draw();
		CST::GetOrthoCamera()->Draw();

		emanager->RenderAllEnemy();
		player->Render();

		//***************************
		//MapPolygonの位置調整
		map->GetRigidBody()->SetCollisionPosition(pos);
		map->GetRigidBody()->SetCollisionRotation(rotation);
		map->SetScaling(scale);
		//***************************


		//*****************************
		//FBXモデルの描画
		CST::GetShaderClass(2)->UseShader();
		object->Draw(CST::GetPerspectiveCamera(), CST::GetShaderClass(2), pos, rotation, scale);
		//*****************************

		//CC::DebugDraw(CST::GetShaderClass(1), CST::GetPerspectiveCamera());
		sc->SwapBuffer();
	}

	delete sc;
	delete etm;
	delete emanager;
	delete player;
	
	delete object;

	CC::Delete();
}