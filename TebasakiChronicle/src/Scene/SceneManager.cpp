#include "SceneManager.h"

//�V�[���̕ύX
void SceneManager::ChangeScene(SceneName nextScene)
{
	if (nextScene == SceneName::Non)
		return;

	Memory::SafeDelete(scene);
	switch (nextScene)
	{
	case SceneName::Title:
		scene = new Scene_Title();
		break;

	case SceneName::Game:
		scene = new Scene_Game();
		break;

	case SceneName::GameOver:
		scene = new Scene_GameOver();
		break;

	case SceneName::GameClear:
		scene = new Scene_GameClear();
		break;
	}
}

//�R���X�g���N�^(�����Ɏw��V�[���ɐݒ�)
SceneManager::SceneManager(SceneName setScene):
	scene(nullptr)
{
	ChangeScene(setScene);
}

//�f�X�g���N�^
SceneManager::~SceneManager()
{
	Memory::SafeDelete(scene);
}

//�X�V
void SceneManager::Update()
{
	ChangeScene(scene->Update());
}

//�`��
void SceneManager::Draw()
{
	scene->Draw();
}