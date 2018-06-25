#pragma once
#include "../Helper.h"
#include "SceneAbstract.h"
#include "Scene_Title/Scene_Title.h"
#include "Scene_Game/Scene_Game.h"
#include "Scene_GameOver/Scene_GameOver.h"
#include "Scene_GameClear/Scene_GameClear.h"

class SceneManager
{
private:
	SceneAbstract* scene;

	//�V�[���̕ύX
	void ChangeScene(SceneName nextScene);

public:
	SceneManager(SceneName setScene);	//�R���X�g���N�^(�����Ɏw��V�[���ɐݒ�)
	~SceneManager();	//�f�X�g���N�^

	void Update();	//�X�V
	void Draw();	//�`��
};