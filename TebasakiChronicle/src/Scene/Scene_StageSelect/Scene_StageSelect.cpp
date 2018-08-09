#include "Scene_StageSelect.h"
#include "../../Helper.h"


//�R���X�g���N�^
Scene_StageSelect::Scene_StageSelect()
{
	angle = 0.0f;
	angleCnt = 0.0f;
	maxAngleCnt = 60.0f;
	selectNowNo = 0;
	rotSpeed = 3.0f;
	rotMove = false;
	//�X���C�h�p�����[�^�̐ݒ�
	upDownSpeed = 3.0f;
	rightSpeed = 5.0f;

	baseRotPos = K_Math::Vector3(CST::GetPerspectiveCamera()->GetScreenWidth() * 0.0f * 50.0f, CST::GetPerspectiveCamera()->GetScreenHeight() / 2.0f, 0);
	CST::LoadAndGetTexture("backGround", "./data/image/ScreenUI/select.png");
	CST::LoadAndGetTexture("map", "./data/image/ScreenUI/stageMap.png");
	CST::LoadAndGetTexture("fade", "./data/image/ScreenUI/fade.png");
	//�t�F�[�h
	fadeGui = new GUIObject("fade", K_Math::Vector3(640, 360, 0), K_Math::Box2D(0, 0, 1280, 720));
	alpha = 1.0f;
	state = State::FadeIn;
	nowScene = SceneName::StageSelect;

	//�X�e�[�W�}�b�v�̐���
	stageMap.emplace_back(new StageMap(new GUIObject("map",K_Math::Vector3(0,0,0),K_Math::Box2D(0,0,256,256)),new StageDetail("map1","�����}�b�v�ł�")));
	stageMap.emplace_back(new StageMap(new GUIObject("map", K_Math::Vector3(0, 0, 0), K_Math::Box2D(0, 0, 256, 256)), new StageDetail("map2", "�H��}�b�v�ł�")));
	stageMap.emplace_back(new StageMap(new GUIObject("map", K_Math::Vector3(0, 0, 0), K_Math::Box2D(0, 0, 256, 256)), new StageDetail("map3", "�ŏI�}�b�v����")));
	stageMap.emplace_back(new StageMap(new GUIObject("map", K_Math::Vector3(0, 0, 0), K_Math::Box2D(0, 0, 256, 256)), new StageDetail("map4", "����")));
	stageMap.emplace_back(new StageMap(new GUIObject("map", K_Math::Vector3(0, 0, 0), K_Math::Box2D(0, 0, 256, 256)), new StageDetail("map5", "����")));
	stageMap.emplace_back(new StageMap(new GUIObject("map", K_Math::Vector3(0, 0, 0), K_Math::Box2D(0, 0, 256, 256)), new StageDetail("map6", "����")));

	//�X�e�[�W�}�b�v�̏����ʒu
	for (auto& it : stageMap)
	{
		it->GetGuiMap().SetOutCirclePos(baseRotPos, 300);
		it->GetGuiMap().SetOutCircleAngle(K_Math::DegToRad(angle));
		angle -= 60.0f;
	}
	angle = 0.0f;
	//�ŏ��̃X�e�[�W�}�b�v�̎Q�ƃf�[�^
	detailGui = new StageDetailGUI(stageMap[0]->GetStageDetail());
}

//�f�X�g���N�^
Scene_StageSelect::~Scene_StageSelect()
{
	for (auto& it : stageMap)
	{
		Memory::SafeDelete(it);
	}
	stageMap.clear();
	Memory::SafeDelete(detailGui);
	Memory::SafeDelete(fadeGui);
}

//�X�V(���ɐݒ肵�����V�[������Ԃ�)
SceneName Scene_StageSelect::Update()
{
	SceneName nextScene = SceneName::Non;

	//��Ԃɉ���������
	this->StateCorrespond(nextScene);

	//�X�e�[�W�̃f�[�^�ڍׂ̍X�V
	detailGui->UpDate(stageMap[selectNowNo]->GetStageDetail());

	return nextScene;
}

//�`��
void Scene_StageSelect::Draw()
{
	CST::GetShaderClass(0)->UseShader();
	CST::GetShaderClass(0)->SetValue("color", K_Math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	for (auto& it : stageMap)
	{
		it->GetGuiMap().Render();
	}
	detailGui->DrawText();

	CST::GetShaderClass(0)->SetValue("color", K_Math::Vector4(1.0f, 1.0f, 1.0f, alpha));
	fadeGui->UpDate();
	fadeGui->Render();
}




/////////////////////////////////////////////////////////////////////////////
//---
//StageDetail
//!@brief	�R���X�g���N�^
Scene_StageSelect::StageDetail::StageDetail(const std::string& stageName, const std::string& overview)
	: stageName(stageName),overview(overview)
{
	
}

//---
//StageMap
//!@brief	�R���X�g���N�^
Scene_StageSelect::StageMap::StageMap(GUIObject* guiMap, StageDetail* stageDetail)
	: guiMap(guiMap),stageDetail(stageDetail)
{
}
//!@brief	�f�X�g���N�^
Scene_StageSelect::StageMap::~StageMap()
{
	Memory::SafeDelete(guiMap);
	Memory::SafeDelete(stageDetail);
}

//!@brief	GUIMap�̎擾
GUIObject&	Scene_StageSelect::StageMap::GetGuiMap() const
{
	return *guiMap;
}
//!@brief	�X�e�[�W���̏ڍׂ̎擾
Scene_StageSelect::StageDetail&	Scene_StageSelect::StageMap::GetStageDetail() const
{
	return *stageDetail;
}

//---
//StageDetailGUI
//!@brief	�R���X�g���N�^
//!@param[in]	stageDetail	���ݑI������Ă���X�e�[�W�����󂯎��
Scene_StageSelect::StageDetailGUI::StageDetailGUI(const StageDetail& stageDetail)
	: stageDetail(stageDetail)
{
	backGround = new GUIObject("backGround",K_Math::Vector3(900, 350, 0), K_Math::Box2D(0, 0, 512, 512));
	this->detailFont.emplace_back(new K_Graphics::FontRenderer());
	detailFont[0]->LoadFont("detailText", "./data/font/rounded-l-mplus-1c-light.ttf");
	detailFont[0]->SetCullentFont("detailText");
	detailFont.emplace_back(new K_Graphics::FontRenderer());
	detailFont[1]->LoadFont("frabarText", "./data/font/rounded-l-mplus-1c-light.ttf");
	detailFont[1]->SetCullentFont("frabarText");
}

//!@brief	�f�X�g���N�^
Scene_StageSelect::StageDetailGUI::~StageDetailGUI()
{
	Memory::SafeDelete(backGround);

	(*detailFont.data())->ClearAllFontTexture();
	for (auto& it : detailFont)
	{
		Memory::SafeDelete(it);
	}
}

//!@brief	�X�e�[�W���̍X�V
//!@param[in]	stageDetail	���ݑI������Ă���X�e�[�W�����󂯎��
void	Scene_StageSelect::StageDetailGUI::UpDate(const StageDetail& stageDetail)
{
	this->stageDetail = stageDetail;
}

//!@brief	�e�L�X�g�̕`��
void	Scene_StageSelect::StageDetailGUI::DrawText()
{
	backGround->UpDate();
	backGround->Render();
	float newLine = 0.0f;
	CST::GetShaderClass(0)->UseShader();
	for (auto& it : detailFont)
	{
		it->Draw2D(CST::GetOrthoCamera(), CST::GetShaderClass(0));
	}
	detailFont[0]->DrawString2D(stageDetail.stageName, 80, 750, 150);
	newLine += 120.0f;
	detailFont[1]->DrawString2D(stageDetail.overview, 30, 750, 150.0f + newLine);
}



//////////////////////////////////////////////////////////////////////////////////////

//!@brief	�X�e�[�W�}�b�v�̉�]�ړ�
void	Scene_StageSelect::StageMapRotation()
{
	if (rotMove)
	{
		if (angleCnt < maxAngleCnt)
		{
			angleCnt += rotSpeed;
			for (auto& it : stageMap)
			{
				it->GetGuiMap().OutCircleRotation(K_Math::DegToRad(angle));
			}
		}
		else
		{
			angleCnt = 0.0f;
			rotMove = false;
		}
	}
}

//!@brief	���͂ŉ�]���s��
void	Scene_StageSelect::InputMapRotation()
{
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::A))
	{
		if (!rotMove)
		{
			if (selectNowNo < stageMap.size() - 1)
			{
				rotMove = true;
				selectNowNo++;
				angle = rotSpeed;
			}
			else if (selectNowNo == stageMap.size() - 1) 
			{ 
				selectNowNo = 0;
				rotMove = true;
				angle = rotSpeed;
			}
		}
	}
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::B))
	{
		if (!rotMove)
		{
			if (selectNowNo > 0)
			{
				rotMove = true;
				selectNowNo--;
				angle = -rotSpeed;
			}
			else if (selectNowNo == 0) 
			{ 
				selectNowNo = stageMap.size() - 1;
				rotMove = true;
				angle = -rotSpeed;
			}
		}
	}
}

//!@brief	�X�e�[�W�̌��菈�����s��
//!@return	���̃V�[��
void	Scene_StageSelect::DecideStageMap()
{
	if (INPUT::IsPressButton(VpadIndex::Pad0, VpadButton::L1))
	{
		state = State::FadeOut;
		switch (selectNowNo)
		{
		case 0:
			//�X�e�[�W1
			nowScene = SceneName::Game;
			break;
		case 1:
			//�X�e�[�W2
			nowScene = SceneName::Game;
			break;
		case 2:
			//�X�e�[�W3
			nowScene = SceneName::Game;
			break;
		}
	}
}

//!@brief	��Ԃ̕ω��ɉ���������
void	Scene_StageSelect::StateCorrespond(SceneName& nextScene)
{
	switch (state)
	{
	case State::FadeIn:
		if (alpha > 0.0f)
		{
			alpha -= 0.01f;
		}
		if (alpha <= 0.0f)
		{
			state = State::Normal;
		}
		for (auto& it : stageMap)
		{
			it->GetGuiMap().SetOutCirclePos(baseRotPos, 300);
			it->GetGuiMap().UpDate();
		}
		break;
	case State::Normal:
		InputMapRotation();
		DecideStageMap();
		for (auto& it : stageMap)
		{
			it->GetGuiMap().SetOutCirclePos(baseRotPos, 300);
			it->GetGuiMap().UpDate();
		}
		StageMapRotation();
		break;
	case State::FadeOut:
		if (alpha < 1.0f)
		{
			alpha += 0.01f;
		}
		if (alpha >= 1.0f)
		{
			state = State::NextScene;
		}
		SlideStageMap(selectNowNo);
		break;
	case State::NextScene:
		nextScene = nowScene;
		break;
	}
}

//!@brief	�X�e�[�W�}�b�v���X���C�h������
//!@param[in]	nowStageNo	���݂̃X�e�[�W�ԍ�
void	Scene_StageSelect::SlideStageMap(const int nowStageNo)
{
	int slideNo = 0;
	//�����̃X���C�h
	{
		if (nowStageNo - 1 <= -1)
		{
			slideNo = stageMap.size() - 1;
		}
		else
		{
			slideNo = nowStageNo - 1;
		}
		stageMap[slideNo]->GetGuiMap().GetGameObject().GetPos().y += upDownSpeed;
	}
	//�㑤�̃X���C�h
	{
		if (nowStageNo + 1 >= stageMap.size() )
		{
			slideNo = 0;
		}
		else
		{
			slideNo = nowStageNo + 1;
		}
		stageMap[slideNo]->GetGuiMap().GetGameObject().GetPos().y -= upDownSpeed;
	}
	//�^�񒆂̃X���C�h
	stageMap[nowStageNo]->GetGuiMap().GetGameObject().GetPos().x += rightSpeed;
}