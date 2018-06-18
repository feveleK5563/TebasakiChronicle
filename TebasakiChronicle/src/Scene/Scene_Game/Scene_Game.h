#pragma once
#include "../SceneAbstract.h"
#include "../../Loader/EnemyLoader.h"
#include "../../Object/Enemy/EnemyType/EnemyTypeManager.h"
#include "../../Object/Enemy/EnemyManager.h"

#include "../../Object/Player/Player.h"

#include "../../Object/Object3D/Object3D.h"
#include "../../BaseClass/GUIObject/GUIObject.h"
#include "../../BaseClass/GUIObject/GageGui/GageGui.h"
#include "../../BaseClass/GUIObject/ScreenGui/ScreenGui.h"
#include "../../BaseClass//GUIObject/DataGui/DataGui.h"
#include "../../Object/CameraMan/CameraMan.h"

#include <memory>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#include "../../BaseClass/Sound/Sound.h"

#include "../../Effect/Effect.h"
#include "../../Helper.h"

class Scene_Game : public SceneAbstract
{
private:
	EnemyLoader eLoader;
	EnemyTypeManager* etm;
	EnemyManager* emanager;

	Player* player;

	K_Math::Vector3 scale;
	K_Math::Vector3 rotation;
	K_Math::Vector3 pos;
	Object3D*	mapObj;

	GUIObject*	back;
	GageGui*	enemyGageGui;
	ScreenGui*	screenGui;
	DataGui*	playerLifeGui;

	CameraMan* cameraMan;

	SoundEngine soundEngine;
	Sound source;

public:
	Scene_Game();		//コンストラクタ
	~Scene_Game();		//デストラクタ
	SceneName Update();	//更新(次に設定したいシーン名を返す)
	void Draw();		//描画
};