#pragma once
#include "../SceneAbstract.h"
#include "../../CSTList.h"
#include "MeshModel.h"
#include "../../BaseClass/Input/Input.h"

class Scene_Title : public SceneAbstract
{
private:
	K_Graphics::Texture* tex;
	K_Graphics::SpriteObject* spobj;

public:
	Scene_Title();		//�R���X�g���N�^
	~Scene_Title();		//�f�X�g���N�^
	SceneName Update();	//�X�V(���ɐݒ肵�����V�[������Ԃ�)
	void Draw();		//�`��
};