#include "Event.h"

Event::Event() :
	state(EventState::Nomal)
{

}

//-----------------------------------------------------------------------------
//引数の情報から、イベントの状態を変化させる
bool Event::ChangeEvent(bool changeFlag, EventState nextEvent)
{
	//遷移フラグがfalseなら遷移しない
	if (!changeFlag || state == nextEvent)
		return false;

	//イベントの状態を変更
	state = nextEvent;

	return true;
}

//-----------------------------------------------------------------------------
//シーン遷移条件を満たしたら次のシーン名を返す
SceneName Event::GetNextScene()
{
	switch (state)
	{
	case EventState::GameOver:
		return SceneName::GameOver;

	case EventState::GameClear:
		return SceneName::GameClear;

	default:
		return SceneName::Non;
	}
}

//-----------------------------------------------------------------------------
//現在のイベントの状態を返す
EventState Event::GetEventState()
{
	return state;
}