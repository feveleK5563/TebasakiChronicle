#pragma once
#include "../Scene/SceneAbstract.h"
#include "../Object/GameObject.h"
#include "../Helper.h"
#include "../BaseClass/Collision/CollisionManager.h"

//�C�x���g�̏��
enum struct EventState
{
	Nomal,			//�ʏ�
	BossReady,		//�{�X�o�g������
	BossBattle,		//�{�X�o�g����
	BossEnd,		//�{�X�o�g���I��
	GameOver,		//�Q�[���I�[�o�[
	GameClear,		//�Q�[���N���A
};

//�C�x���g�ƃV�[���J�ڂɊւ��ĊǗ����s��
class Event
{
private:
	EventState state;

public:
	Event();

	//�����̏�񂩂�A�C�x���g�̏�Ԃ�ω�������
	bool ChangeEvent(bool changeFlag, EventState nextEvent);

	//���̃V�[������Ԃ�(�����Ȃ��ꍇ��Non���Ԃ�)
	SceneName GetNextScene();

	//���݂̃C�x���g�̏�Ԃ�Ԃ�
	EventState GetEventState();
};