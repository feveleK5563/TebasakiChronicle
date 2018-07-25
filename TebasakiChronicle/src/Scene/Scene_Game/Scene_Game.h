#pragma once
#include "../SceneAbstract.h"
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

//イベントの状態
enum struct EventState
{
	Nomal,			//通常
	BossReady,		//ボスバトル導入
	BossBattle,		//ボスバトル中
	BossEnd,		//ボスバトル終了
	GameOver,		//ゲームオーバー
	GameClear,		//ゲームクリア
};

class Scene_Game : public SceneAbstract
{
private:
	EnemyManager * emanager;

	Player* player;

	K_Math::Vector3 scale;
	K_Math::Vector3 rotation;
	K_Math::Vector3 pos;
	Object3D*	mapCol;
	Object3D*	mapObj;

	GUIObject*	back;
	GageGui*	enemyGageGui;
	ScreenGui*	screenGui;
	DataGui*	playerLifeGui;

	CameraMan* cameraMan;

	SoundEngine soundEngine;
	Sound source;

	SceneName nextScene;

	//イベント用時間経過
	TimeCount eventTimeCnt;
	//イベント状態
	EventState eventState;
	//壁
	bool isCreateWall;
	K_Physics::CollisionShape* notReturnWallShape;
	K_Physics::CollisionData* notReturnWall;
	//イベントに応じた処理関数ポインタ
	void(Scene_Game::*processForEvent)();

public:
	Scene_Game();		//コンストラクタ
	~Scene_Game();		//デストラクタ
	SceneName Update();	//更新(次に設定したいシーン名を返す)
	void Draw();		//描画

private:
	void EventChage();		//イベントの変更

	void ProcessForNomal();			//イベント通常状態の処理
	void ProcessForBossReady();		//イベントボス準備状態の処理
	void ProcessForBoss();			//イベントボス戦状態の処理
	void ProcessForBossEnd();		//イベントボス終了状態の処理
	void ProcessForGameOver();		//イベントゲームオーバー状態の処理
	void ProcessForGameClear();		//イベントゲームクリア状態の処理
};