#include "Scene_Game.h"
#include "../../BaseClass/Collision/CollisionCreator.h"

//�R���X�g���N�^
Scene_Game::Scene_Game():
	emanager(new EnemyManager()),
	player(new Player()),
	playerLifeGui(new DataGui(player->GetGameObject())),
	isCreateWall(false),
	eventState(EventState::Nomal),
	processForEvent(&Scene_Game::ProcessForNomal)
{
	//�G�̔z�u���̓ǂݍ���
	emanager->LayoutEnemy("data/EnemyData/EnemyLayout/opStageEnemySettings.txt");

	player->Initliaze();

	//�n�`����t���I�u�W�F�N�g
	scale =		{ 30,30,30 };
	rotation =	{ K_Math::DegToRad(0),K_Math::DegToRad(0),K_Math::DegToRad(0) };
	pos =		{ -120.0f,-50.0f,0.f };
	mapCol = new Object3D("data/model/map/mapCollision.fbx", pos, rotation, scale);
	//�n�`����t���I�u�W�F�N�g
	scale = { 30,30,30 };
	rotation = { K_Math::DegToRad(0),K_Math::DegToRad(0),K_Math::DegToRad(0) };
	pos = { -120.0f,-50.0f,0.f };
	mapObj = new Object3D("data/model/map/map.fbx", pos, rotation, scale);

	//�w�i�摜
	CST::LoadAndGetTexture("back", "data/image/back.png");
	back = new GUIObject("back", K_Math::Vector3(0, 50, 10), K_Math::Box2D(0, 0, 1920, 720));
	back->SetScale(K_Math::Vector3(2, 2, 1));
	
	//��ʂ�UI
	screenGui = new ScreenGui();
	
	//�G�̃��C�t�Q�[�W
	enemyGageGui = new GageGui(emanager->GetBossLife());

	//�J�����}��
	cameraMan = new CameraMan(Define::ScreenWidth, Define::ScreenHeight, 330, player->GetGameObject().GetPos());

	//�T�E���h
	source.LoadSound("bgm", "data/sounds/�V�Y_drone.ogg");
	//Engine�ɃT�E���h��o�^(�ǉ����Ȃ��ƃA�N�Z�X�ᔽ)
	soundEngine.AddSource(source);
	//�o�^����ΐ������g����
	source.Play();

	//�G�t�F�N�g���쐬
	Effect::CreateEffectData(EffectName::Effect1,
		"testEffect", "data/image/testEffect.png",
		new AnimationCharaChip(K_Math::Box2D(0, 0, 32, 32), 8, 5, false));

	//�G�t�F�N�g�摜�̓ǂݍ���(��)
	CST::LoadAndGetTexture("Effect", "data/image/effect.png");
}

//-------------------------------------------------------------------
//�f�X�g���N�^
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
//�X�V(���ɐݒ肵�����V�[������Ԃ�)
SceneName Scene_Game::Update()
{
	nextScene = SceneName::Non;

	player->UpDate();
	emanager->UpdateAllEnemy();

	mapObj->SetDecisionParam(pos, rotation, scale);

	//�w�i�̍X�V
	back->UpDate();
	//���UI�̍X�V
	screenGui->UpDate();
	//�G��Life
	enemyGageGui->UpDate();
	//�v���C���[��Life
	playerLifeGui->Raito(player->GetGameObject());
	playerLifeGui->UpDate();

	//�G�t�F�N�g�̍X�V
	Effect::Run();

	//�C�x���g�ɉ���������
	(this->*processForEvent)();

	return nextScene;
}

//-------------------------------------------------------------------
//�`��
void Scene_Game::Draw()
{
	//*****************************
	//FBX���f���̕`��
	CST::GetShaderClass(2)->UseShader();
	//----------------------------
	//�n�`����t���I�u�W�F�N�g
	mapObj->Render();
	CST::GetShaderClass(1)->UseShader();

	emanager->RenderAllEnemy();

	Effect::Render();

	//�w�i�̕`��
	back->Render3D();

	//�G��life
	enemyGageGui->Render();

	//���UI�̕`��(���̕`�悷�����)
	screenGui->EarlyRender();

	//���UI�̕`��(�O�ɕ`�悷�����)
	screenGui->LateRender();

	//�v���C���[��Life
	playerLifeGui->Render();

	//�v���C���[
	player->Render();
}


//-------------------------------------------------------------------
//�C�x���g�ʏ��Ԃ̏���
void Scene_Game::ProcessForNomal()
{
	//�J�������v���C���[��ǔ�
	cameraMan->Run(player->GetGameObject().GetPos());

	//�Q�[���I�[�o�[
	if ((player->GetGameObject().IsDead()) ||	//�v���C���[��HP��0
		(player->GetGameObject().GetPos().y < -(float)Define::ScreenHeight))	//��ʉ��ɗ�����
	{
		eventState = EventState::GameOver;
		processForEvent = &Scene_Game::ProcessForGameOver;
	}

	//�{�X��ڍs
	if ((eventState == EventState::Nomal) &&
		(player->GetGameObject().GetPos().x > 200/*14000/**/) &&	//����X���W�𒴂���
		player->CheckEventLanding())		//�v���C���[���n�ʂɕt���Ă���Ƃ�
	{
		//�v���C���[�̓���𖳌�
		player->ChangeMode(Player::Mode::Event);
		player->SetDirMoveParam(40.f, Status::Direction::Right);

		//�C�x���g��Ԃ�ύX
		eventState = EventState::BossReady;
		processForEvent = &Scene_Game::ProcessForBossReady;
		isCreateWall = true;
	}
}

//-------------------------------------------------------------------
//�C�x���g�{�X������Ԃ̏���
void Scene_Game::ProcessForBossReady()
{
	eventTimeCnt.Run();

	if (eventTimeCnt.GetNowCntTime() == 90)
	{
		//�{�X��L��
		emanager->AllActiveBoss(true);

		//�ǂ��쐬
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
		//�J�������{�X��ǔ�
		cameraMan->Run(emanager->GetBossPos());

		if (eventTimeCnt.GetNowCntTime() > 180)
		{
			eventTimeCnt.ResetCntTime();

			eventState = EventState::BossBattle;
			processForEvent = &Scene_Game::ProcessForBoss;
			enemyGageGui->EventStart();

			//�v���C���[�̓����L��
			player->ChangeMode(Player::Mode::Normal);
		}
	}
	else
	{
		cameraMan->Run(player->GetGameObject().GetPos());
	}
}

//-------------------------------------------------------------------
//�C�x���g�{�X���Ԃ̏���
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
//�C�x���g�{�X�I����Ԃ̏���
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
//�C�x���g�Q�[���I�[�o�[��Ԃ̏���
void Scene_Game::ProcessForGameOver()
{
	nextScene = SceneName::GameOver;
}

//-------------------------------------------------------------------
//�C�x���g�Q�[���N���A��Ԃ̏���
void Scene_Game::ProcessForGameClear()
{
	nextScene = SceneName::GameClear;
}