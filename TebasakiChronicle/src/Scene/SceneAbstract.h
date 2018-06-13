#pragma once

enum struct SceneName
{
	Non,
	Title,
	Game,
};

class SceneAbstract
{
public:
	virtual ~SceneAbstract() = default;
	virtual SceneName Update() = 0;
	virtual void Draw() = 0;
};