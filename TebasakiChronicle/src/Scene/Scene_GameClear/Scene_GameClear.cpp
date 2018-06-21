#include "Scene_GameClear.h"

//�R���X�g���N�^
Scene_GameClear::Scene_GameClear()
{
	tex = CST::LoadAndGetTexture("clear", "data/image/���N���A.png");
	spobj = new K_Graphics::SpriteObject(tex);
}

//�f�X�g���N�^
Scene_GameClear::~Scene_GameClear()
{
	CST::DeleteTexture("clear");
	delete spobj;
}

//�X�V(���ɐݒ肵�����V�[������Ԃ�)
SceneName Scene_GameClear::Update()
{
	SceneName nextScene = SceneName::Non;
	if (INPUT::IsPressButton(VpadIndex::Pad0, K_Input::VpadButton::L1))
	{
		nextScene = SceneName::Title;
	}
	return nextScene;
}

//�`��
void Scene_GameClear::Draw()
{
	CST::GetShaderClass(0)->UseShader();
	spobj->Draw2D(
		CST::GetOrthoCamera(),
		CST::GetShaderClass(0),
		K_Math::Box2D(0, 0, 1280, 720),
		K_Math::Box2D(0, 0, 1280, 720),
		0.f);
}