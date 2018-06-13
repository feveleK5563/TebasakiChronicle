#pragma once
#include "../Helper.h"
#include "SceneAbstract.h"
#include "Scene_Title/Scene_Title.h"
#include "Scene_Game/Scene_Game.h"

class SceneManager
{
private:
	SceneAbstract* scene;

	//シーンの変更
	void ChangeScene(SceneName nextScene);

public:
	SceneManager(SceneName setScene);	//コンストラクタ(同時に指定シーンに設定)
	~SceneManager();	//デストラクタ

	void Update();	//更新
	void Draw();	//描画
};