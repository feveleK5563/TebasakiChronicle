#pragma once
#include "../Scene/SceneAbstract.h"
#include "../Object/GameObject.h"
#include "../Helper.h"
#include "../BaseClass/Collision/CollisionManager.h"

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

//イベントとシーン遷移に関して管理を行う
class Event
{
private:
	EventState state;

public:
	Event();

	//引数の情報から、イベントの状態を変化させる
	bool ChangeEvent(bool changeFlag, EventState nextEvent);

	//次のシーン名を返す(何もない場合はNonが返る)
	SceneName GetNextScene();

	//現在のイベントの状態を返す
	EventState GetEventState();
};