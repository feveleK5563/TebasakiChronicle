#include "Scene_Game.h"
#include "../../BaseClass/Collision/CollisionCreator.h"

//�R���X�g���N�^
Scene_Game::Scene_Game():
	emanager(new EnemyManager()),
	player(new Player()),
	playerLifeGui(new DataGui(player->GetGameObject()))
{
	//�G�̔z�u���̓ǂݍ���
	emanager->LayoutEnemy("data/EnemyData/EnemyLayout/opStageEnemySettings.txt");

	player->Initliaze();

	//�n�`����t���I�u�W�F�N�g
	scale =		{ 30,30,30 };
	rotation =	{ K_Math::DegToRad(0),K_Math::DegToRad(0),K_Math::DegToRad(0) };
	pos =		{ -120.0f,-50.0f,0.f };
	mapObj = new Object3D("data/model/map/map.fbx", pos, rotation, scale);

	//�w�i�摜
	CST::LoadAndGetTexture("back", "data/image/back.png");
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

	//�G�t�F�N�g���쐬
	Effect::CreateEffectData(EffectName::Effect1,
		"testEffect", "data/image/testEffect.png",
		new AnimationCharaChip(K_Math::Box2D(0, 0, 32, 32), 8, 5, false));

	//�ȉ���
	CST::LoadAndGetTexture("Effect", "data/image/effect.png");
}

//�f�X�g���N�^
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

//�X�V(���ɐݒ肵�����V�[������Ԃ�)
SceneName Scene_Game::Update()
{
	SceneName nextScene = SceneName::Non;
	//�v���C���[�̃C�x���g����
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::A)) //Z�L�[
	{
		//���[�h��ύX����K�v������
		//EventStart�̓{�X�̃C�x���g�ɓ���Ƃ��ɌĂ�
		player->ChangeMode(Player::Mode::EventStart);
	}
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::B)) //X�L�[
	{
		//�v���C�������n���������f
		if (player->CheckEventLanding())
		{
			player->ChangeMode(Player::Mode::Event);
			//���̊֐���Event���Ɉڍs����ۂɌĂ�
			//frameTime�͂��̃��[�h���s���t���[������
			//frameTime�Ŏw�肵�����Ԃ��s������A�����Ō��ɖ߂�
			//dir�͈ړ������̌���
			player->SetDirMoveParam(100.0f, Status::Direction::Right);
		}
	}
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::X)) //C�L�[
	{
		//�ʏ�̏�Ԃɓ���Ƃ��ɌĂ�
		player->ChangeMode(Player::Mode::Normal);
	}
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

	event.ThinkChangeEvent(player->GetGameObject());

	return event.GetNextScene();
}

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