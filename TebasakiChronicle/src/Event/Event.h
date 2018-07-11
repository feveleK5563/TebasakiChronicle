#pragma once
#include "../Scene/SceneAbstract.h"
#include "../Object/GameObject.h"
#include "../Helper.h"

//�C�x���g�̏��
enum struct EventState
{
	Nomal,
	GameOver,
	GameClear,
};

//�C�x���g�N���X
class Event
{
private:
	EventState state;

public:
	Event();

	//�v���C���[��񂩂�A�C�x���g�̏�Ԃ�ω�������
	void ThinkChangeEvent(GameObject& playerData);

	//���̃V�[������Ԃ�(�����Ȃ��ꍇ��Non���Ԃ�)
	SceneName GetNextScene();
};