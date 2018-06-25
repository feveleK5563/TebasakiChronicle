#pragma once
#include "../SceneAbstract.h"
#include "../../CSTList.h"
#include "MeshModel.h"
#include "../../BaseClass/Input/Input.h"

class Scene_GameOver : public SceneAbstract
{
private:
	K_Graphics::Texture* tex;
	K_Graphics::SpriteObject* spobj;

public:
	Scene_GameOver();				//コンストラクタ
	~Scene_GameOver();				//デストラクタ
	SceneName Update() override;	//更新(次に設定したいシーン名を返す)
	void Draw() override;			//描画
};