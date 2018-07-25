#pragma once
#include "../SceneAbstract.h"
#include "../../Object/Enemy/EnemyManager.h"

#include "../../Object/Player/Player.h"

#include "../../Object/Object3D/Object3D.h"
#include "../../BaseClass/GUIObject/GUIObject.h"
#include "../../BaseClass/GUIObject/GageGui/GageGui.h"
#include "../../BaseClass/GUIObject/ScreenGui/ScreenGui.h"
#include "../../BaseClass//GUIObject/DataGui/DataGui.h"
#include "../../Object/CameraMan/CameraMan.h"

#include <memory>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#include "../../BaseClass/Sound/Sound.h"

#include "../../Effect/Effect.h"
#include "../../Helper.h"

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

class Scene_Game : public SceneAbstract
{
private:
	EnemyManager * emanager;

	Player* player;

	K_Math::Vector3 scale;
	K_Math::Vector3 rotation;
	K_Math::Vector3 pos;
	Object3D*	mapCol;
	Object3D*	mapObj;

	GUIObject*	back;
	GageGui*	enemyGageGui;
	ScreenGui*	screenGui;
	DataGui*	playerLifeGui;

	CameraMan* cameraMan;

	SoundEngine soundEngine;
	Sound source;

	SceneName nextScene;

	//�C�x���g�p���Ԍo��
	TimeCount eventTimeCnt;
	//�C�x���g���
	EventState eventState;
	//��
	bool isCreateWall;
	K_Physics::CollisionShape* notReturnWallShape;
	K_Physics::CollisionData* notReturnWall;
	//�C�x���g�ɉ����������֐��|�C���^
	void(Scene_Game::*processForEvent)();

public:
	Scene_Game();		//�R���X�g���N�^
	~Scene_Game();		//�f�X�g���N�^
	SceneName Update();	//�X�V(���ɐݒ肵�����V�[������Ԃ�)
	void Draw();		//�`��

private:
	void EventChage();		//�C�x���g�̕ύX

	void ProcessForNomal();			//�C�x���g�ʏ��Ԃ̏���
	void ProcessForBossReady();		//�C�x���g�{�X������Ԃ̏���
	void ProcessForBoss();			//�C�x���g�{�X���Ԃ̏���
	void ProcessForBossEnd();		//�C�x���g�{�X�I����Ԃ̏���
	void ProcessForGameOver();		//�C�x���g�Q�[���I�[�o�[��Ԃ̏���
	void ProcessForGameClear();		//�C�x���g�Q�[���N���A��Ԃ̏���
};