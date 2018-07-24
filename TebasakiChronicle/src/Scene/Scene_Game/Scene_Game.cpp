#include "Scene_Game.h"
#include "../../BaseClass/Collision/CollisionCreator.h"

//コンストラクタ
Scene_Game::Scene_Game():
	emanager(new EnemyManager()),
	player(new Player()),
	playerLifeGui(new DataGui(player->GetGameObject()))
{
	//敵の配置情報の読み込み
	emanager->LayoutEnemy("data/EnemyData/EnemyLayout/opStageEnemySettings.txt");

	player->Initliaze();

	//地形判定付きオブジェクト
	scale =		{ 30,30,30 };
	rotation =	{ K_Math::DegToRad(0),K_Math::DegToRad(0),K_Math::DegToRad(0) };
	pos =		{ -120.0f,-50.0f,0.f };
	mapObj = new Object3D("data/model/map/map.fbx", pos, rotation, scale);

	//背景画像
	CST::LoadAndGetTexture("back", "data/image/back.png");
	back = new GUIObject("back", K_Math::Vector3(0, 50, 10), K_Math::Box2D(0, 0, 1920, 720));
	back->SetScale(K_Math::Vector3(2, 2, 1));
	
	//画面のUI
	screenGui = new ScreenGui();
	
	//敵のライフゲージ(今はプレイヤーのLifeと連動)
	enemyGageGui = new GageGui(player->GetGameObject());

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

	//以下仮
	CST::LoadAndGetTexture("Effect", "data/image/effect.png");
}

//デストラクタ
Scene_Game::~Scene_Game()
{
	Memory::SafeDelete(emanager);
	Memory::SafeDelete(player);
	Memory::SafeDelete(mapObj);
	Memory::SafeDelete(back);
	Memory::SafeDelete(playerLifeGui);
	Memory::SafeDelete(screenGui);
	Memory::SafeDelete(enemyGageGui);
	Memory::SafeDelete(cameraMan);

	soundEngine.DeleteSound(source.GetName().c_str());

	Effect::AllDeleteEffect();

	CST::DeleteTexture("back");
	CST::DeleteTexture("Effect");
}

//更新(次に設定したいシーン名を返す)
SceneName Scene_Game::Update()
{
	SceneName nextScene = SceneName::Non;
	//プレイヤーのイベント処理
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::A)) //Zキー
	{
		//モードを変更する必要がある
		//EventStartはボスのイベントに入るときに呼ぶ
		player->ChangeMode(Player::Mode::EventStart);
	}
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::B)) //Xキー
	{
		//プレイヤが着地したか判断
		if (player->CheckEventLanding())
		{
			player->ChangeMode(Player::Mode::Event);
			//下の関数はEvent時に移行する際に呼ぶ
			//frameTimeはそのモードを行うフレーム時間
			//frameTimeで指定した時間を行ったら、自動で元に戻る
			//dirは移動方向の向き
			player->SetDirMoveParam(100.0f, Status::Direction::Right);
		}
	}
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::X)) //Cキー
	{
		//通常の状態に入るときに呼ぶ
		player->ChangeMode(Player::Mode::Normal);
	}
	player->UpDate();
	emanager->UpdateAllEnemy();

	mapObj->SetDecisionParam(pos, rotation, scale);

	//背景の更新
	back->UpDate();
	//画面UIの更新
	screenGui->UpDate();
	//敵のLife
	enemyGageGui->UpDate(player->GetGameObject());
	//プレイヤーのLife
	playerLifeGui->Raito(player->GetGameObject());
	playerLifeGui->UpDate();

	//エフェクトの更新
	Effect::Run();

	//カメラ追尾
	cameraMan->Run(player->GetGameObject().GetPos());

	event.ThinkChangeEvent(player->GetGameObject());

	return event.GetNextScene();
}

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

	//画面UIの描画(後ろの描画するもの)
	screenGui->EarlyRender();

	//敵のlife
	enemyGageGui->Render();

	//画面UIの描画(前に描画するもの)
	screenGui->LateRender();

	//プレイヤーのLife
	playerLifeGui->Render();

	//プレイヤー
	player->Render();

}