#include "Event.h"

Event::Event() :
	state(EventState::Nomal)
{

}


//-----------------------------------------------------------------------------
//�v���C���[��񂩂�A�C�x���g�̏�Ԃ�ω�������
void Event::ThinkChangeEvent(GameObject& playerData)
{
	//�Q�[���I�[�o�[����
	if (playerData.IsDead() ||	//���S
		playerData.GetPos().y < -(float)Define::ScreenHeight)	//��ʉ��ɗ���
	{
		state = EventState::GameOver;
	}

	//�Q�[���N���A����
	if (playerData.GetPos().x > 14000)	//��ʉE�ɍs������
	{
		state = EventState::GameClear;
	}
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