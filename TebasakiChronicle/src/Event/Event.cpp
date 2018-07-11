#include "Event.h"

Event::Event() :
	state(EventState::Nomal)
{

}


//-----------------------------------------------------------------------------
//プレイヤー情報から、イベントの状態を変化させる
void Event::ThinkChangeEvent(GameObject& playerData)
{
	//ゲームオーバー条件
	if (playerData.IsDead() ||	//死亡
		playerData.GetPos().y < -(float)Define::ScreenHeight)	//画面下に落下
	{
		state = EventState::GameOver;
	}

	//ゲームクリア条件
	if (playerData.GetPos().x > 14000)	//画面右に行ったら
	{
		state = EventState::GameClear;
	}
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