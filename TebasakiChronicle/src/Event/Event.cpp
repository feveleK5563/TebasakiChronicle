#include "Event.h"

Event::Event() :
	state(EventState::Nomal)
{

}

//-----------------------------------------------------------------------------
//�����̏�񂩂�A�C�x���g�̏�Ԃ�ω�������
bool Event::ChangeEvent(bool changeFlag, EventState nextEvent)
{
	//�J�ڃt���O��false�Ȃ�J�ڂ��Ȃ�
	if (!changeFlag || state == nextEvent)
		return false;

	//�C�x���g�̏�Ԃ�ύX
	state = nextEvent;

	return true;
}

//-----------------------------------------------------------------------------
//�V�[���J�ڏ����𖞂������玟�̃V�[������Ԃ�
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
//���݂̃C�x���g�̏�Ԃ�Ԃ�
EventState Event::GetEventState()
{
	return state;
}