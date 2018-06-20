#include "Scene_Game.h"
#include "../../BaseClass/Collision/CollisionCreator.h"

//�R���X�g���N�^
Scene_Game::Scene_Game():
	etm(new EnemyTypeManager()),
	emanager(new EnemyManager()),
	player(new Player()),
	playerLifeGui(new DataGui(player->GetGameObject()))
{
	//�G�̎�ނ��쐬
	etm->CreateEnemyData(eLoader.LoadEnemyData("data/EnemyData/EnemyDataA1.txt"));
	//��L�ō쐬������ނ���ɓG�𐶐�����
	emanager->CreateEnemy(etm->GetEnemyTypeData(0), K_Math::Vector3(-10, 20, 0), Status::Direction::Left);

	player->Initliaze();

	//�n�`����t���I�u�W�F�N�g
	scale =		{ 10,40,40 };
	rotation =	{ K_Math::DegToRad(0),K_Math::DegToRad(0),K_Math::DegToRad(0) };
	pos =		{ -120.0f,-50.0f,0.f };
	mapObj = new Object3D("data/model/map/map.fbx", pos, rotation, scale);

	//�w�i�摜
	back = new GUIObject("back", K_Math::Vector3(0, 50, 10), K_Math::Box2D(0, 0, 1920, 720));
	back->SetScale(K_Math::Vector3(2, 2, 1));
	
	//��ʂ�UI
	screenGui = new ScreenGui();
	
	//�G�̃��C�t�Q�[�W(���̓v���C���[��Life�ƘA��)
	enemyGageGui = new GageGui(player->GetGameObject());

	//�J�����}��
	cameraMan = new CameraMan(Define::ScreenWidth, Define::ScreenHeight, 330, player->GetGameObject().GetPos());

	//�T�E���h
	source.LoadSound("bgm", "data/sounds/�V�Y_drone.ogg");
	//Engine�ɃT�E���h��o�^(�ǉ����Ȃ��ƃA�N�Z�X�ᔽ)
	soundEngine.AddSource(source);
	//�o�^����ΐ������g����
	source.Play();
}

//�f�X�g���N�^
Scene_Game::~Scene_Game()
{
	delete etm;
	delete emanager;
	delete player;
	delete mapObj;
	delete back;
	delete playerLifeGui;
	delete screenGui;
	delete enemyGageGui;
	delete cameraMan;
}

//�X�V(���ɐݒ肵�����V�[������Ԃ�)
SceneName Scene_Game::Update()
{
	SceneName nextScene = SceneName::Non;

	player->UpDate();
	emanager->UpdateAllEnemy();

	mapObj->SetDecisionParam(pos, rotation, scale);

	//�w�i�̍X�V
	back->UpDate();
	//���UI�̍X�V
	screenGui->UpDate();
	//�G��Life
	enemyGageGui->UpDate(player->GetGameObject());
	//�v���C���[��Life
	playerLifeGui->Raito(player->GetGameObject());
	playerLifeGui->UpDate();

	//�G�t�F�N�g�̍X�V
	Effect::Run();

	//�J�����ǔ�
	cameraMan->Run(player->GetGameObject().GetPos());

	if (player->GetGameObject().IsDead())
	{
		nextScene = SceneName::Title;
	}

	return nextScene;
}

//�`��
void Scene_Game::Draw()
{
	emanager->RenderAllEnemy();

	//*****************************
	//FBX���f���̕`��
	CST::GetShaderClass(2)->UseShader();
	//----------------------------
	//�n�`����t���I�u�W�F�N�g
	mapObj->Render();

	CST::GetShaderClass(1)->UseShader();

	Effect::Render();

	//�w�i�̕`��
	back->Render3D();

	//���UI�̕`��(���̕`�悷�����)
	screenGui->EarlyRender();

	//�G��life
	enemyGageGui->Render();

	//���UI�̕`��(�O�ɕ`�悷�����)
	screenGui->LateRender();

	//�v���C���[��Life
	playerLifeGui->Render();

	//�v���C���[
	player->Render();
}