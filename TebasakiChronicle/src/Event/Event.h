#pragma once
#include "../Scene/SceneAbstract.h"
#include "../Object/GameObject.h"
#include "../Helper.h"

//イベントの状態
enum struct EventState
{
	Nomal,
	GameOver,
	GameClear,
};

//イベントクラス
class Event
{
private:
	EventState state;

public:
	Event();

	//プレイヤー情報から、イベントの状態を変化させる
	void ThinkChangeEvent(GameObject& playerData);

	//次のシーン名を返す(何もない場合はNonが返る)
	SceneName GetNextScene();
};