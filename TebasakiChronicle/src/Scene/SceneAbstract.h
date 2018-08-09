#pragma once

enum struct SceneName
{
	Non,
	Title,
	Game,
	GameOver,
	GameClear,
	StageSelect,
};

class SceneAbstract
{
public:
	virtual ~SceneAbstract() = default;
	virtual SceneName Update() = 0;
	virtual void Draw() = 0;
};