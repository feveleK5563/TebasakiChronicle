#include "SceneManager.h"

//シーンの変更
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
	}
}

//コンストラクタ(同時に指定シーンに設定)
SceneManager::SceneManager(SceneName setScene)
{
	ChangeScene(setScene);
}

//デストラクタ
SceneManager::~SceneManager()
{
	Memory::SafeDelete(scene);
}

//更新
void SceneManager::Update()
{
	ChangeScene(scene->Update());
}

//描画
void SceneManager::Draw()
{
	scene->Draw();
}