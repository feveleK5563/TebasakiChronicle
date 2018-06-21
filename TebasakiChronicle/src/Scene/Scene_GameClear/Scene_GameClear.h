#pragma once
#include "../SceneAbstract.h"
#include "../../CSTList.h"
#include "MeshModel.h"
#include "../../BaseClass/Input/Input.h"

class Scene_GameClear : public SceneAbstract
{
private:
	K_Graphics::Texture* tex;
	K_Graphics::SpriteObject* spobj;

public:
	Scene_GameClear();				//�R���X�g���N�^
	~Scene_GameClear();				//�f�X�g���N�^
	SceneName Update() override;	//�X�V(���ɐݒ肵�����V�[������Ԃ�)
	void Draw() override;			//�`��
};