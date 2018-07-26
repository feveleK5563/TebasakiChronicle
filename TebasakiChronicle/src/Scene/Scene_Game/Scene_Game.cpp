#include "Scene_Game.h"
#include "../../BaseClass/Collision/CollisionCreator.h"

//コンストラクタ
Scene_Game::Scene_Game():
	emanager(new EnemyManager()),
	player(new Player()),
	playerLifeGui(new DataGui(player->GetGameObject())),
	isCreateWall(false),
	eventState(EventState::Nomal),
	processForEvent(&Scene_Game::ProcessForNomal)
{
	//敵の配置情報の読み込み
	emanager->LayoutEnemy("data/EnemyData/EnemyLayout/opStageEnemySettings.txt");

	player->Initliaze();

	//地形判定付きオブジェクト
	scale =		{ 30,30,30 };
	rotation =	{ K_Math::DegToRad(0),K_Math::DegToRad(0),K_Math::DegToRad(0) };
	pos =		{ -120.0f,-50.0f,0.f };
	mapCol = new Object3D("data/model/map/mapCollision.fbx", pos, rotation, scale);
	//地形判定付きオブジェクト
	scale = { 30,30,30 };
	rotation = { K_Math::DegToRad(0),K_Math::DegToRad(0),K_Math::DegToRad(0) };
	pos = { -120.0f,-50.0f,0.f };
	mapObj = new Object3D("data/model/map/map.fbx", pos, rotation, scale);

	//背景画像
	CST::LoadAndGetTexture("back", "data/image/back.png");
	back = new GUIObject("back", K_Math::Vector3(0, 50, 10), K_Math::Box2D(0, 0, 1920, 720));
	back->SetScale(K_Math::Vector3(2, 2, 1));
	
	//画面のUI
	screenGui = new ScreenGui();
	
	//敵のライフゲージ
	enemyGageGui = new GageGui(emanager->GetBossLife());

	//カメラマン
	cameraMan = new CameraMan(Define::ScreenWidth, Define::ScreenHeight, 330, player->GetGameObject().GetPos());

	//サウンド
	source.LoadSound("bgm", "data/sounds/遊戯_drone.ogg");
	//Engineにサウンドを登録(追加しないとアクセス違反)
	soundEngine.AddSource(source);
	//登録すれば正しく使える
	source.Play();

	//エフェクトを作成
	Effect::CreateEffectData(EffectName::Effect1,
		"testEffect", "data/image/testEffect.png",
		new AnimationCharaChip(K_Math::Box2D(0, 0, 32, 32), 8, 5, false));

	//エフェクト画像の読み込み(仮)
	CST::LoadAndGetTexture("Effect", "data/image/effect.png");
}

//-------------------------------------------------------------------
//デストラクタ
Scene_Game::~Scene_Game()
{
	Memory::SafeDelete(emanager);
	Memory::SafeDelete(player);
	Memory::SafeDelete(mapObj);
	Memory::SafeDelete(mapCol);
	Memory::SafeDelete(back);
	Memory::SafeDelete(playerLifeGui);
	Memory::SafeDelete(screenGui);
	Memory::SafeDelete(enemyGageGui);
	Memory::SafeDelete(cameraMan);

	soundEngine.DeleteSound(source.GetName().c_str());

	Effect::AllDeleteEffect();

	CST::DeleteTexture("back");
	CST::DeleteTexture("Effect");

	if (isCreateWall)
	{
		CC::RemoveCollisionShape(&notReturnWallShape);
		CC::RemoveCollision(&notReturnWall);
	}
}

//-------------------------------------------------------------------
//更新(次に設定したいシーン名を返す)
SceneName Scene_Game::Update()
{
	nextScene = SceneName::Non;

	player->UpDate();
	emanager->UpdateAllEnemy();

	mapObj->SetDecisionParam(pos, rotation, scale);

	//背景の更新
	back->UpDate();
	//画面UIの更新
	screenGui->UpDate();
	//敵のLife
	enemyGageGui->UpDate();
	//プレイヤーのLife
	playerLifeGui->Raito(player->GetGameObject());
	playerLifeGui->UpDate();

	//エフェクトの更新
	Effect::Run();

	//イベントに応じた処理
	(this->*processForEvent)();

	return nextScene;
}

//-------------------------------------------------------------------
//描画
void Scene_Game::Draw()
{
	//*****************************
	//FBXモデルの描画
	CST::GetShaderClass(2)->UseShader();
	//----------------------------
	//地形判定付きオブジェクト
	mapObj->Render();
	CST::GetShaderClass(1)->UseShader();

	emanager->RenderAllEnemy();

	Effect::Render();

	//背景の描画
	back->Render3D();

	//敵のlife
	enemyGageGui->Render();

	//画面UIの描画(後ろの描画するもの)
	screenGui->EarlyRender();

	//画面UIの描画(前に描画するもの)
	screenGui->LateRender();

	//プレイヤーのLife
	playerLifeGui->Render();

	//プレイヤー
	player->Render();
}


//-------------------------------------------------------------------
//イベント通常状態の処理
void Scene_Game::ProcessForNomal()
{
	//カメラがプレイヤーを追尾
	cameraMan->Run(player->GetGameObject().GetPos());

	//ゲームオーバー
	if ((player->GetGameObject().IsDead()) ||	//プレイヤーのHPが0
		(player->GetGameObject().GetPos().y < -(float)Define::ScreenHeight))	//画面下に落ちる
	{
		eventState = EventState::GameOver;
		processForEvent = &Scene_Game::ProcessForGameOver;
	}

	//ボス戦移行
	if ((eventState == EventState::Nomal) &&
		(player->GetGameObject().GetPos().x > 200/*14000/**/) &&	//一定のX座標を超える
		player->CheckEventLanding())		//プレイヤーが地面に付いているとき
	{
		//プレイヤーの動作を無効
		player->ChangeMode(Player::Mode::Event);
		player->SetDirMoveParam(40.f, Status::Direction::Right);

		//イベント状態を変更
		eventState = EventState::BossReady;
		processForEvent = &Scene_Game::ProcessForBossReady;
		isCreateWall = true;
	}
}

//-------------------------------------------------------------------
//イベントボス準備状態の処理
void Scene_Game::ProcessForBossReady()
{
	eventTimeCnt.Run();

	if (eventTimeCnt.GetNowCntTime() == 90)
	{
		//ボスを有効
		emanager->AllActiveBoss(true);

		//壁を作成
		notReturnWallShape = CC::CreateBoxShape(50.f, 1000.f, 30.f);

		notReturnWall = CC::CreateCollisionObject(
			notReturnWallShape,
			false,
			CollisionMask::Non,
			CollisionMask::Ground,
			K_Math::Vector3(player->GetGameObject().GetPos().x - 100, 0, 0),
			K_Math::Vector3(0, 0, 0));
	}

	if (eventTimeCnt.GetNowCntTime() > 90)
	{
		//カメラがボスを追尾
		cameraMan->Run(emanager->GetBossPos());

		if (eventTimeCnt.GetNowCntTime() > 180)
		{
			eventTimeCnt.ResetCntTime();

			eventState = EventState::BossBattle;
			processForEvent = &Scene_Game::ProcessForBoss;
			enemyGageGui->EventStart();

			//プレイヤーの動作を有効
			player->ChangeMode(Player::Mode::Normal);
		}
	}
	else
	{
		cameraMan->Run(player->GetGameObject().GetPos());
	}
}

//-------------------------------------------------------------------
//イベントボス戦状態の処理
void Scene_Game::ProcessForBoss()
{
	ProcessForNomal();

	if (emanager->GetIsDeadBoss())
	{
		eventState = EventState::BossEnd;
		processForEvent = &Scene_Game::ProcessForBossEnd;
		//player->ChangeMode(Player::Mode::Event);
	}
}

//-------------------------------------------------------------------
//イベントボス終了状態の処理
void Scene_Game::ProcessForBossEnd()
{
	eventTimeCnt.Run();

	if (eventTimeCnt.GetNowCntTime() > 120)
	{
		eventState = EventState::GameClear;
		processForEvent = &Scene_Game::ProcessForGameClear;
	}
}

//-------------------------------------------------------------------
//イベントゲームオーバー状態の処理
void Scene_Game::ProcessForGameOver()
{
	nextScene = SceneName::GameOver;
}

//-------------------------------------------------------------------
//イベントゲームクリア状態の処理
void Scene_Game::ProcessForGameClear()
{
	nextScene = SceneName::GameClear;
}