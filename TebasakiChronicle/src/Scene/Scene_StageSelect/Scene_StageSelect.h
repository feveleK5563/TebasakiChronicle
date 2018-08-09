#pragma once
#include "../SceneAbstract.h"
#include "../../CSTList.h"
#include "MeshModel.h"
#include "../../BaseClass/Input/Input.h"
#include "../../src/BaseClass/GUIObject/GUIObject.h"
#include <FontRenderer.h>

class Scene_StageSelect : public SceneAbstract
{
private:
	//!@brief	�X�e�[�W�̏ڍ׏��
	struct StageDetail
	{
		//!@brief	�R���X�g���N�^
		StageDetail(const std::string& stageName, const std::string& overview);
		std::string	stageName;	//�X�e�[�W��
		std::string	overview;	//�X�e�[�W�T�v
	};
	//!@brief	�X�e�[�W�}�b�v
	class StageMap
	{
	public:
		//!@brief	�R���X�g���N�^
		StageMap(GUIObject* guiMap, StageDetail* stageDetail);
		//!@brief	�f�X�g���N�^
		~StageMap();
		//!@brief	GUIMap�̎擾
		GUIObject&		GetGuiMap() const;
		//!@brief	�X�e�[�W���̏ڍׂ̎擾
		StageDetail&	GetStageDetail() const;
	private:
		GUIObject*		guiMap;				//�X�e�[�W�̃}�b�vGUI
		StageDetail*	stageDetail;		//�X�e�[�W�̏ڍ׏��
	};
	//!@brief	�X�e�[�W�̏ڍׂ��摜�ɂ���
	class StageDetailGUI
	{
	public:
		//!@brief	�R���X�g���N�^
		//!@param[in]	stageDetail	���ݑI������Ă���X�e�[�W�����󂯎��
		StageDetailGUI(const StageDetail& stageDetail);
		//!@brief	�f�X�g���N�^
		~StageDetailGUI();
	public:
		//!@brief	�X�e�[�W���̍X�V
		//!@param[in]	stageDetail	���ݑI������Ă���X�e�[�W�����󂯎��
		void	UpDate(const StageDetail& stageDetail);
		//!@brief	�e�L�X�g�̕`��
		void	DrawText();
	private:
		StageDetail		stageDetail;
		std::vector<K_Graphics::FontRenderer*>	detailFont;
		GUIObject*		backGround;
	};
	//!@brief	���
	enum class State
	{
		FadeIn,		//�t�F�[�h�C��
		Normal,		//�ʏ�
		FadeOut,	//�t�F�[�h�A�E�g
		NextScene	//���̃V�[��
	};
private:
	float	maxAngleCnt;
	float	angleCnt;
	float	angle;
	float	rotSpeed;
	bool	rotMove;
	int		selectNowNo;
	K_Math::Vector3			baseRotPos;		//�}�b�v����]�����_
	std::vector<StageMap*>	stageMap;		//�X�e�[�W�}�b�v
	StageDetailGUI*			detailGui;		//�ڍ�GUI
private:
	//�t�F�[�h
	GUIObject*				fadeGui;		//�t�F�[�h�p
	float					alpha;			//�����x
	State					state;			//���
	SceneName				nowScene;		//���̃V�[��
private:
	//�X���C�h�p�����[�^
	float	upDownSpeed;	//�㉺�̃X���C�h�X�s�[�h
	float	rightSpeed;		//�E�̃X���C�h�X�s�[�h

public:
	Scene_StageSelect();			//�R���X�g���N�^
	~Scene_StageSelect();			//�f�X�g���N�^
	SceneName Update() override;	//�X�V(���ɐݒ肵�����V�[������Ԃ�)
	void Draw() override;			//�`��

private:
	//!@brief	�X�e�[�W�}�b�v�̉�]�ړ�
	void	StageMapRotation();
	//!@brief	���͂ŉ�]���s��
	void	InputMapRotation();
	//!@brief	�X�e�[�W�̌��菈�����s��
	//!@retrurn	���̃V�[��
	void	DecideStageMap();
	//!@brief	��Ԃ̕ω��ɉ���������
	void	StateCorrespond(SceneName& nextScene);
	//!@brief	�X�e�[�W�}�b�v���X���C�h������
	//!@param[in]	nowStageNo	���݂̃X�e�[�W�ԍ�
	void	SlideStageMap(const int nowStageNo);
};