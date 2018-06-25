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
	Scene_GameClear();				//コンストラクタ
	~Scene_GameClear();				//デストラクタ
	SceneName Update() override;	//更新(次に設定したいシーン名を返す)
	void Draw() override;			//描画
};