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
	Scene_Title();		//コンストラクタ
	~Scene_Title();		//デストラクタ
	SceneName Update();	//更新(次に設定したいシーン名を返す)
	void Draw();		//描画
};