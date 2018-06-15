#include "Scene_Game.h"

//コンストラクタ
Scene_Game::Scene_Game():
	etm(new EnemyTypeManager()),
	emanager(new EnemyManager()),
	player(new Player()),
	datagui(player->object)
{
	//敵の種類を作成
	etm->CreateEnemyData(eLoader.LoadEnemyData("data/EnemyData/EnemyDataA1.txt"));
	//上記で作成した種類を基に敵を生成する
	emanager->CreateEnemy(etm->GetEnemyTypeData(0), K_Math::Vector3(-10, 20, 0), Status::Direction::Left);

	player->Initliaze();

	//地形判定付きオブジェクト
	scale =		{ 10,40,40 };
	rotation =	{ K_Math::DegToRad(0),K_Math::DegToRad(90),K_Math::DegToRad(0) };
	pos =		{ -120.0f,-50.0f,0.f };
	mapObj = new Object3D(	"./data/model/testMap2d.fbx", "./data/image/player.tga",
							pos, rotation, scale);

	//背景画像
	back = new GUIObject("back", K_Math::Vector3(0, 50, 10), K_Math::Box2D(0, 0, 1920, 720));
	back->SetScale(K_Math::Vector3(2, 2, 1));
	//画面のUI
	screenGui = new GUIObject(
		"ui",
		K_Math::Vector3(Define::ScreenWidth / 2, Define::ScreenHeight / 2, 0),
		K_Math::Box2D(0, 0, Define::ScreenWidth, Define::ScreenHeight)
	);
	//スクリーン
	gui = new ScreenGui();

	//カメラマン
	cameraMan = new CameraMan(Define::ScreenWidth, Define::ScreenHeight, 330, player->object.GetPos());

	//サウンド
	source.LoadSound("bgm", "data/sounds/遊戯_drone.ogg");
	//Engineにサウンドを登録(追加しないとアクセス違反)
	soundEngine.AddSource(source);
	//登録すれば正しく使える
	source.Play();
}

//デストラクタ
Scene_Game::~Scene_Game()
{
	delete etm;
	delete emanager;
	delete player;
	delete mapObj;
	delete back;
	delete screenGui;
	delete gui;
	delete cameraMan;
}

//更新(次に設定したいシーン名を返す)
SceneName Scene_Game::Update()
{
	SceneName nextScene = SceneName::Non;

	player->UpDate();
	emanager->UpdateAllEnemy();

	mapObj->SetDecisionParam(pos, rotation, scale);

	//背景の更新
	back->UpDate();
	//画面UIの更新
	screenGui->UpDate();

	//エフェクトの更新
	Effect::Run();

	//カメラ追尾
	cameraMan->Run(player->object.GetPos());

	return nextScene;
}

//描画
void Scene_Game::Draw()
{
	emanager->RenderAllEnemy();

	//*****************************
	//FBXモデルの描画
	CST::GetShaderClass(2)->UseShader();
	//----------------------------
	//地形判定付きオブジェクト
	mapObj->Render();

	CST::GetShaderClass(1)->UseShader();

	Effect::Render();

	//背景の描画
	back->Render3D();

	//画面UIの描画
	//screenGui->Render();

	//プレイやー
	player->Render();

	gui->UpDate();
	gui->Render();

	datagui.RaitoRaito();
	datagui.UpDate();
	datagui.Render();
}